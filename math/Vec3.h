//
// Created by user on 05.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_VEC3_H
#define TERMINAL_3D_GRAPHICS_ENGINE_VEC3_H

#include <iostream>

class Vec3
{
private:
    float x, y, z;
public:
    Vec3();
    Vec3(float x, float y, float z);

    void X(float newX);
    void Y(float newY);
    void Z(float newZ);
    [[nodiscard]] float X() const;
    [[nodiscard]] float Y() const;
    [[nodiscard]] float Z() const;

    Vec3 operator+(const Vec3 &vec) const;
    Vec3 operator-(const Vec3 &vec) const;

    Vec3 operator*(float scalar) const;
    Vec3 operator/(float scalar) const;

    bool operator==(const Vec3 &vec) const;
    bool operator!=(const Vec3 &vec) const;

    [[nodiscard]] float scalarMultiplication(const Vec3 &vec) const; //
    [[nodiscard]] Vec3 vectorMultiplication(const Vec3 &vec) const; //

    [[nodiscard]] float length() const;
    [[nodiscard]] Vec3 normalize() const;

    static float getAngle(const Vec3 &vec1, const Vec3 &vec2);
    static Vec3 lerp(const Vec3 &vec1, const Vec3 &vec2, float alpha);
    static Vec3 reflect(const Vec3 &incident, const Vec3 &normal);
};

std::ostream& operator<<(std::ostream &os, const Vec3 &vec);


#endif //TERMINAL_3D_GRAPHICS_ENGINE_VEC3_H