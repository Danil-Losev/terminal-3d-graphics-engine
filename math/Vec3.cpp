//
// Created by user on 05.11.2025.
//

#include "Vec3.h"

#include <cmath>
#include <fstream>
#include "quickSQRT.h"

Vec3::Vec3() : x(0), y(0), z(0)
{
}

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vec3::X(const float newX)
{
    this->x = newX;
}

void Vec3::Y(const float newY)
{
    this->y = newY;
}

void Vec3::Z(const float newZ)
{
    this->z = newZ;
}

float Vec3::X() const
{
    return this->x;
}

float Vec3::Y() const
{
    return this->y;
}

float Vec3::Z() const
{
    return this->z;
}

Vec3 Vec3::operator+(const Vec3& vec) const
{
    return {this->x + vec.x, this->y + vec.y, this->z + vec.z};
}

Vec3 Vec3::operator-(const Vec3& vec) const
{
    return {this->x - vec.x, this->y - vec.y, this->z - vec.z};
}

Vec3 Vec3::operator*(const float scalar) const
{
    return {this->x * scalar, this->y * scalar, this->z * scalar};
}

Vec3 Vec3::operator/(const float scalar) const
{
    return {this->x / scalar, this->y / scalar, this->z / scalar};
}

bool Vec3::operator==(const Vec3& vec) const
{
    return this->x == vec.x && this->y == vec.y && this->z == vec.z;
}

bool Vec3::operator!=(const Vec3& vec) const
{
    return this->x != vec.x || this->y != vec.y || this->z != vec.z;
}

float Vec3::scalarMultiplication(const Vec3& vec) const
{
    return this->x * vec.x + this->y * vec.y + this->z * vec.z;
}

Vec3 Vec3::vectorMultiplication(const Vec3& vec) const
{
    return {this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x};
}

float Vec3::length() const
{
    return quickSQRT::Q_rsqrt(1.0f / (this->x * this->x + this->y * this->y + this->z * this->z));
}

Vec3 Vec3::normalize() const
{
    return (*this) * quickSQRT::Q_rsqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vec3::getAngle(const Vec3& vec1, const Vec3& vec2)
{
    return std::acos(vec1.scalarMultiplication(vec2) / (vec1.length() * vec2.length()));
}

Vec3 Vec3::lerp(const Vec3& vec1, const Vec3& vec2, const float alpha)
{
    if (alpha < 0.0f) return vec1;
    if (alpha > 1.0f) return vec2;
    return vec1 + (vec2 - vec1) * alpha;
}

Vec3 Vec3::reflect(const Vec3& incident, const Vec3& normal)
{
    return incident - normal * 2 * normal.scalarMultiplication(incident);
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec)
{
    os << "Vec3(" << vec.X() << "," << vec.Y() << "," << vec.Z() << ")";
    return os;
}
