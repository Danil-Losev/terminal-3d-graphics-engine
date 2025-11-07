#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/Mat4.h"
#include "math/Vec2.h"
#include "scene/scene.h"
#include <conio.h>

struct ProjectedVertex
{
    int x, y;
    float z;
};


bool clipLineLiangBarsky(int xMin, int xMax, int yMin, int yMax,
                         float& x0, float& y0, float& x1, float& y1)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    float p[4] = {-dx, dx, -dy, dy};
    float q[4] = {x0 - xMin, xMax - x0, y0 - yMin, yMax - y0};

    float u1 = 0.0f;
    float u2 = 1.0f;

    for (int i = 0; i < 4; ++i)
    {
        if (p[i] == 0.0f)
        {
            if (q[i] < 0.0f) return false; // линия полностью вне
        }
        else
        {
            float u = q[i] / p[i];
            if (p[i] < 0) u1 = std::max(u1, u);
            else u2 = std::min(u2, u);
        }
    }

    if (u1 > u2) return false; // линия полностью вне

    float nx0 = x0 + dx * u1;
    float ny0 = y0 + dy * u1;
    float nx1 = x0 + dx * u2;
    float ny1 = y0 + dy * u2;

    x0 = nx0;
    y0 = ny0;
    x1 = nx1;
    y1 = ny1;

    return true;
}

void drawLine(int x0, int y0, float z0,
              int x1, int y1, float z1, char c)
{
    int width = scene::getMainScene()->getWidth();
    int height = scene::getMainScene()->getHeight();

    float fx0 = static_cast<float>(x0);
    float fy0 = static_cast<float>(y0);
    float fx1 = static_cast<float>(x1);
    float fy1 = static_cast<float>(y1);

    // Обрезаем линию по экрану
    if (!clipLineLiangBarsky(0, width - 1, 0, height - 1, fx0, fy0, fx1, fy1))
        return; // полностью вне

    x0 = static_cast<int>(fx0);
    y0 = static_cast<int>(fy0);
    x1 = static_cast<int>(fx1);
    y1 = static_cast<int>(fy1);

    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    int steps = std::max(dx, -dy) + 1;
    float dz = (z1 - z0) / steps;
    float z = z0;

    for (int i = 0; i < steps; ++i)
    {
        if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
        {
            scene::getMainScene()->setPixel(x0, y0, z, c);
        }

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }

        z += dz;
    }
}


int main()
{
    Vec3 cube[8] = {
        {-1, -1, -1}, {1, -1, -1},
        {1, 1, -1}, {-1, 1, -1},
        {-1, -1, 1}, {1, -1, 1},
        {1, 1, 1}, {-1, 1, 1}
    };

    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    scene::createMainScene(720, 200);
    const Mat4 perspectiveProjection = Mat4::makePerspective(50.0f);
    Vec3 camPos = {3, 3, 3};
    Vec3 camTarget = {0, 0, 0};
    const Vec3 camUp = {0, 1, 0};
    while (true)
    {
        bool isMoving = false;
        if (_kbhit())
        {
            const char key = static_cast<char>(_getch());
            isMoving = true;
            constexpr float moveSpeed = 0.2f;
            constexpr float rotSpeed = 0.05f;

            // Вектор "вправо" через векторное произведение
            Vec3 forward = (camTarget - camPos).normalize();
            Vec3 right = forward.vectorMultiplication(camUp).normalize();

            // --- Движение камеры (WASD) ---
            if (key == 'w') camPos = camPos + forward * moveSpeed;
            if (key == 's') camPos = camPos - forward * moveSpeed;
            if (key == 'a') camPos = camPos - right * moveSpeed;
            if (key == 'd') camPos = camPos + right * moveSpeed;

            // --- Вращение направления взгляда (IJKL) ---
            if (key == 'i') forward = (forward - camUp * rotSpeed).normalize(); // вверх
            if (key == 'k') forward = (forward + camUp * rotSpeed).normalize(); // вниз
            if (key == 'j') forward = (forward - right * rotSpeed).normalize(); // влево
            if (key == 'l') forward = (forward + right * rotSpeed).normalize(); // вправо

            // --- Обновление цели ---
            camTarget = camPos + forward;

            // --- Пример выхода ---
            if (key == 27) break; // ESC
        }
        if (!isMoving)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        scene::getMainScene()->clear();
        Mat4 model = Mat4::scale(2.0f, 2.0f, 2.0f);
        Mat4 view = Mat4::lookAtMoveable(camPos, camTarget, camUp);
        Mat4 mvp = perspectiveProjection * view * model;

        std::vector<ProjectedVertex> projectedPoints;

        for (const Vec3& vertex : cube)
        {
            Vec4 camSpace = view * model * Vec4(vertex.X(), vertex.Y(), vertex.Z(), 1.0f);
            float depth = camSpace.Z(); // линейная глубина
            Vec4 transformed = perspectiveProjection * camSpace;
            if (transformed.W() == 0.0f) continue;

            Vec3 ndc(
                transformed.X() / transformed.W(),
                transformed.Y() / transformed.W(),
                transformed.Z() / transformed.W()
            );

            int sx = static_cast<int>((ndc.X() + 1.0f) * 0.5f * scene::getMainScene()->getWidth());
            int sy = static_cast<int>((1.0f - ndc.Y()) * 0.5f * scene::getMainScene()->getHeight());

            projectedPoints.push_back({sx, sy, depth});
        }

        // Рисуем рёбра
        for (const auto& edge : edges)
        {
            auto p1 = projectedPoints[edge[0]];
            auto p2 = projectedPoints[edge[1]];
            // Пропускаем если одна из точек - маркер вне экрана
            drawLine(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, '#');
        }

        scene::getMainScene()->render();
        std::cout << "Position: (" << camPos.X() << ", " << camPos.Y() << ", " << camPos.Z() << ")\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // ~33 FPS
    }
}
