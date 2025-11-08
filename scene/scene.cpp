//
// Created by user on 05.11.2025.
//

#include "scene.h"

#include <algorithm>
#include <iostream>
#include <cmath>
#include <ostream>
#include <windows.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#define NEAR_PLATE 0.01f
#define FAR_PLATE 100.0f

scene* scene::mainScene = nullptr;


void drawLine(int x1, int y1, const float z1,
              const int x2, const int y2, const float z2, const char c)
{
    const int width = scene::getMainScene()->getWidth();
    const int height = scene::getMainScene()->getHeight();

    const int dx = abs(x2 - x1);
    const int dy = -abs(y2 - y1);
    const int sx = x1 < x2 ? 1 : -1;
    const int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;

    const int steps = max(dx, -dy) + 1;
    const float dz = (z2 - z1) / steps;
    float z = z1;

    for (int i = 0; i < steps; ++i)
    {
        // Ограничиваем координаты экраном
        const int px = std::clamp(x1, 0, width - 1);
        const int py = std::clamp(y1, 0, height - 1);

        // Ставим пиксель только если внутри экрана
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
        {
            scene::getMainScene()->setPixel(px, py, z, c);
        }
        if (x1 == x2 && y1 == y2) break;

        const int e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y1 += sy;
        }
        z += dz;
    }
}


scene::scene() : width(300), height(300)
{
    this->buffer = new char*[this->height];
    this->zBuffer = new float*[this->height];
    this->nearPlane = NEAR_PLATE;
    this->farPlane = FAR_PLATE;
    for (int i = 0; i < this->height; ++i)
    {
        this->buffer[i] = new char[this->width];
        this->zBuffer[i] = new float[this->width];
        for (int j = 0; j < this->width; ++j)
        {
            this->buffer[i][j] = ' ';
            this->zBuffer[i][j] = 1e9f;
        }
    }
}

scene::scene(const int width, const int height)
{
    this->width = width;
    this->height = height;
    this->buffer = new char*[height];
    this->zBuffer = new float*[height];
    this->nearPlane = NEAR_PLATE;
    this->farPlane = FAR_PLATE;
    for (int i = 0; i < height; ++i)
    {
        this->buffer[i] = new char[width];
        this->zBuffer[i] = new float[width];
        for (int j = 0; j < width; ++j)
        {
            this->buffer[i][j] = ' ';
            this->zBuffer[i][j] = 1e9f;
        }
    }
}

scene::~scene()
{
    for (int i = 0; i < this->height; ++i)
    {
        delete[] this->buffer[i];
        delete[] this->zBuffer[i];
    }
    delete[] this->buffer;
    delete[] this->zBuffer;
}

scene* scene::getMainScene()
{
    if (mainScene == nullptr)
    {
        mainScene = new scene();
    }
    return mainScene;
}

void scene::createMainScene(const int width, const int height)
{
    mainScene = new scene(width, height);
}

void scene::destroyMainScene()
{
    delete mainScene;
    mainScene = nullptr;
}

void scene::addShape(shape* shp)
{
    this->shapes.push_back(shp);
}

void scene::removeShape(shape* shp)
{
    std::erase(this->shapes, shp);
}

void scene::setCamera(camera* cam)
{
    this->cam = cam;
}

camera* scene::getCamera() const
{
    return this->cam;
}

int scene::getWidth() const
{
    return this->width;
}

int scene::getHeight() const
{
    return this->height;
}

float scene::getNearPlane() const
{
    return nearPlane;
}

float scene::getFarPlane() const
{
    return farPlane;
}

void scene::setNearPlane(const float nearPlane)
{
    this->nearPlane = nearPlane;
}

void scene::setFarPlane(const float farPlane)
{
    this->farPlane = farPlane;
}

char** scene::getBuffer() const
{
    return this->buffer;
}

void scene::redrawBuffer() const
{
    Mat4 perspectiveProjection = this->cam->getPerspectiveProjectionMatrix();
    for (const shape* shp : this->shapes)
    {
        if (shp == nullptr) { continue; }

        Mat4 model = shp->getModel();
        Mat4 view = Mat4::lookAtMoveable(this->cam->camPos, this->cam->camTarget, this->cam->camUp);


        for (const auto& [v1, v2] : shp->getEdges())
        {
            // исходные вершины
            const Vec3& vA = shp->getVertices()[v1];
            const Vec3& vB = shp->getVertices()[v2];

            // переводим в пространство камеры (model -> view)
            Vec4 camA = view * model * Vec4(vA.X(), vA.Y(), vA.Z(), 1.0f);
            Vec4 camB = view * model * Vec4(vB.X(), vB.Y(), vB.Z(), 1.0f);

            float za = camA.Z();
            float zb = camB.Z();

            // если оба за камерой/позади плоскости near -> пропускаем ребро
            // (за камерой считаем za <= 0, либо за near — za < nearPlane)
            if ((za <= 0.0f || za < nearPlane) && (zb <= 0.0f || zb < nearPlane))
                continue;

            // сделаем локальные копии cam-space точек, чтобы при необходимости подменить одну из них
            Vec4 pA = camA;
            Vec4 pB = camB;

            // если одна из точек позади near (или за камерой), вычислим пересечение ребра с плоскостью z = nearPlane
            // parametric: P(t) = A + t*(B - A); ищем t где P.z == nearPlane (в cam-space)
            if (za < nearPlane && zb >= nearPlane)
            {
                float t = (nearPlane - za) / (zb - za); // zb - za != 0, потому что zb >= nearPlane и za < nearPlane
                // интерполируем позицию в cam-space
                float ix = pA.X() + t * (pB.X() - pA.X());
                float iy = pA.Y() + t * (pB.Y() - pA.Y());
                float iz = nearPlane; // pA.Z() + t*(pB.Z()-pA.Z()) == nearPlane по формуле
                pA = Vec4(ix, iy, iz, 1.0f); // ставим новую A на плоскости near
                za = iz;
            }
            else if (zb < nearPlane && za >= nearPlane)
            {
                float t = (nearPlane - za) / (zb - za);
                float ix = pA.X() + t * (pB.X() - pA.X());
                float iy = pA.Y() + t * (pB.Y() - pA.Y());
                float iz = nearPlane;
                pB = Vec4(ix, iy, iz, 1.0f);
                zb = iz;
            }
            else if (za <= 0.0f && zb > 0.0f) // дополнительный случай: одна точка позади камеры (za<=0), другая спереди
            {
                // считаем пересечение с плоскостью z = EPS (или nearPlane)
                float t = (nearPlane - za) / (zb - za);
                float ix = pA.X() + t * (pB.X() - pA.X());
                float iy = pA.Y() + t * (pB.Y() - pA.Y());
                float iz = nearPlane;
                pA = Vec4(ix, iy, iz, 1.0f);
                za = iz;
            }
            else if (zb <= 0.0f && za > 0.0f)
            {
                float t = (nearPlane - za) / (zb - za);
                float ix = pA.X() + t * (pB.X() - pA.X());
                float iy = pA.Y() + t * (pB.Y() - pA.Y());
                float iz = nearPlane;
                pB = Vec4(ix, iy, iz, 1.0f);
                zb = iz;
            }

            // теперь оба конца (pA, pB) находятся перед плоскостью near (или один/оба уже были перед ней)
            // можно их проектировать через перспективную матрицу
            Vec4 clipA = perspectiveProjection * pA;
            Vec4 clipB = perspectiveProjection * pB;

            // если w == 0 — не проецируем
            if (clipA.W() == 0.0f || clipB.W() == 0.0f) continue;

            // дополнительно можно отбросить если за farPlane (в cam-space)
            if ((pA.Z() > farPlane && pB.Z() > farPlane)) continue;

            // деление на W -> NDC
            Vec3 ndcA(clipA.X() / clipA.W(), clipA.Y() / clipA.W(), clipA.Z() / clipA.W());
            Vec3 ndcB(clipB.X() / clipB.W(), clipB.Y() / clipB.W(), clipB.Z() / clipB.W());

            // экранные координаты
            int sxA = static_cast<int>((ndcA.X() + 1.0f) * 0.5f * static_cast<float>(scene::getMainScene()->
                getWidth()));
            int syA = static_cast<int>((1.0f - ndcA.Y()) * 0.5f * static_cast<float>(scene::getMainScene()->
                getHeight()));
            int sxB = static_cast<int>((ndcB.X() + 1.0f) * 0.5f * static_cast<float>(scene::getMainScene()->
                getWidth()));
            int syB = static_cast<int>((1.0f - ndcB.Y()) * 0.5f * static_cast<float>(scene::getMainScene()->
                getHeight()));

            // глубины для z-буфера берем из cam-space (линейная)
            float depthA = pA.Z();
            float depthB = pB.Z();

            // если оба точки полностью вне NDC по одной из осей и находятся по одну сторону — можно пропустить (мелкая оптимизация)
            // но drawLine с Liang-Barsky всё аккуратно обрежет по экрану, так что это не строго необходимо.

            // рисуем ребро (drawLine уже умеет обрезать по экрану и писать в z-буфер)
            drawLine(sxA, syA, depthA, sxB, syB, depthB, '#');
        }
    }
}

void scene::render() const
{
    const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    constexpr COORD origin{0, 0};
    SetConsoleCursorPosition(hConsole, origin);

    std::string out;
    out.reserve(static_cast<size_t>(this->height) * (this->width + 2)); // +2 для "\r\n"

    for (int i = 0; i < this->height; ++i)
    {
        out.append(this->buffer[i], this->width);
        out.append("\r\n");
    }

    DWORD written = 0;
    WriteConsoleA(hConsole, out.data(), static_cast<DWORD>(out.size()), &written, nullptr);
}

void scene::clear() const
{
    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            this->buffer[i][j] = ' ';
            this->zBuffer[i][j] = 1e9f;
        }
    }
}

void scene::setPixel(const int x, const int y, const float depth, const char pixel) const
{
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) return;
    if (depth < nearPlane || depth > farPlane) return;
    if (depth < this->zBuffer[y][x])
    {
        this->zBuffer[y][x] = depth;
        this->buffer[y][x] = pixel;
    }
}
