//
// Created by user on 05.11.2025.
//

#include "Vec2.h"
#include <array>

Vec2::Vec2() : x(0), y(0)
{
}

Vec2::Vec2(const Vec3& vec3, const float fov, const int screenHeight, const int screenWidth, const float near,
           const float far)
{
    static Mat4 perspectiveProjectionMatrix = Mat4::makePerspective(
        fov, screenHeight, screenWidth, near, far);

    const float perspectiveX = vec3.X() * perspectiveProjectionMatrix[0][0] + vec3.Y() *
        perspectiveProjectionMatrix[0][1] + vec3.Z() * perspectiveProjectionMatrix[0][2] +
        1 * perspectiveProjectionMatrix[0][3];
    const float perspectiveY = vec3.X() * perspectiveProjectionMatrix[1][0] + vec3.Y() *
        perspectiveProjectionMatrix[1][1] + vec3.Z() * perspectiveProjectionMatrix[1][2] +
        1 * perspectiveProjectionMatrix[1][3];
    const float perspectiveW = vec3.X() * perspectiveProjectionMatrix[3][0] + vec3.Y() *
        perspectiveProjectionMatrix[3][1] + vec3.Z() * perspectiveProjectionMatrix[3][2] +
        1 * perspectiveProjectionMatrix[3][3];

    this->x = perspectiveX / perspectiveW;
    this->y = perspectiveY / perspectiveW;
}

Vec2::Vec2(const float x, const float y)
{
    this->x = x;
    this->y = y;
}

float Vec2::X() const
{
    return this->x;
}

float Vec2::Y() const
{
    return this->y;
}

void Vec2::X(const float newX)
{
    this->x = newX;
}

void Vec2::Y(const float newY)
{
    this->y = newY;
}

Vec2 Vec2::operator+(const Vec2& vec) const
{
    return {this->x + vec.x, this->y + vec.y};
}

Vec2 Vec2::operator-(const Vec2& vec) const
{
    return {this->x - vec.x, this->y - vec.y};
}

Vec2 Vec2::operator*(const float scalar) const
{
    return {this->x * scalar, this->y * scalar};
}

Vec2 Vec2::operator/(const float scalar) const
{
    return {this->x / scalar, this->y / scalar};
}

float Vec2::scalarMultiplication(const Vec2& vec) const
{
    return this->x * vec.x + this->y * vec.y;
}

Vec2 Vec2::vectorMultiplication(const Vec2& vec) const
{
    return {this->y * vec.x, this->x * vec.y,};
}

float Vec2::length() const
{
    return std::sqrt(this->x * this->x + this->y * this->y);
}

Vec2 Vec2::normalize() const
{
    const float length = this->length();
    return length > 0 ? *this / length : Vec2();
}

float Vec2::getAngle(const Vec2& vec1, const Vec2& vec2)
{
    return std::acos(vec1.scalarMultiplication(vec2) / (vec1.length() * vec2.length()));
}

Vec2 Vec2::lerp(const Vec2& vec1, const Vec2& vec2, const float alpha)
{
    return {vec1.x + (vec2.x - vec1.x) * alpha, vec1.y + (vec2.y - vec1.y) * alpha};
}

Vec2 Vec2::reflect(const Vec2& incident, const Vec2& normal)
{
    return incident - normal * 2 * normal.scalarMultiplication(incident);
}
