//
// Created by user on 06.11.2025.
//

#include "Vec4.h"

Vec4::Vec4() : x(0), y(0), z(0), w(0)
{
}

Vec4::Vec4(const float x, const float y, const float z, const float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

float Vec4::X() const
{
    return this->x;
}

float Vec4::Y() const
{
    return this->y;
}

float Vec4::Z() const
{
    return this->z;
}

float Vec4::W() const
{
    return this->w;
}

void Vec4::X(const float newX)
{
    this->x = newX;
}

void Vec4::Y(const float newY)
{
    this->y = newY;
}

void Vec4::Z(const float newZ)
{
    this->z = newZ;
}

void Vec4::W(const float newW)
{
    this->w = newW;
}

Vec4 Vec4::operator+(const Vec4& vec) const
{
    return {this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w};
}

Vec4 Vec4::operator-(const Vec4& vec) const
{
    return {this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w};
}

Vec4 Vec4::operator*(const float scalar) const
{
    return {this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar};
}

Vec4 Vec4::operator/(const float scalar) const
{
    return {this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar};
}
