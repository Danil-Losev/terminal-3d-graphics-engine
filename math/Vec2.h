//
// Created by user on 05.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_VEC2_H
#define TERMINAL_3D_GRAPHICS_ENGINE_VEC2_H

#include "Vec3.h"
#include "Mat4.h"
#include "../scene/scene.h"


class Vec2
{
private:
    float x, y;

public:
    Vec2();
    explicit Vec2(const Vec3& vec3, float fov = 50, int screenHeight = scene::getMainScene()->getHeight(),
                  int screenWidth = scene::getMainScene()->getWidth(),
                  float near = 0.1f, float far = 1000.0f);
    Vec2(float x, float y);

    [[nodiscard]] float X() const;
    [[nodiscard]] float Y() const;
    void X(float newX);
    void Y(float newY);

    Vec2 operator+(const Vec2& vec) const;
    Vec2 operator-(const Vec2& vec) const;

    Vec2 operator*(float scalar) const;
    Vec2 operator/(float scalar) const;

    [[nodiscard]] float scalarMultiplication(const Vec2& vec) const; //
    [[nodiscard]] Vec2 vectorMultiplication(const Vec2& vec) const; //

    [[nodiscard]] float length() const;
    [[nodiscard]] Vec2 normalize() const;

    static float getAngle(const Vec2& vec1, const Vec2& vec2);
    static Vec2 lerp(const Vec2& vec1, const Vec2& vec2, float alpha);
    static Vec2 reflect(const Vec2& incident, const Vec2& normal);
};


#endif //TERMINAL_3D_GRAPHICS_ENGINE_VEC2_H
