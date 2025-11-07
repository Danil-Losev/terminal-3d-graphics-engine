//
// Created by user on 05.11.2025.
//

#include "scene.h"

#include <iostream>
#include <ostream>
#include <windows.h>

#define NEAR_PLATE 0.01f
#define FAR_PLATE 100.0f

scene* scene::mainScene = nullptr;

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
