//
// Created by user on 06.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_VEC4_H
#define TERMINAL_3D_GRAPHICS_ENGINE_VEC4_H


class Vec4
{
private:
    float x, y, z, w;

public:
    Vec4();
    Vec4(float x, float y, float z, float w);
    [[nodiscard]] float X() const;
    [[nodiscard]] float Y() const;
    [[nodiscard]] float Z() const;
    [[nodiscard]] float W() const;
    void X(float newX);
    void Y(float newY);
    void Z(float newZ);
    void W(float newW);

    Vec4 operator+(const Vec4& vec) const;
    Vec4 operator-(const Vec4& vec) const;

    Vec4 operator*(float scalar) const;
    Vec4 operator/(float scalar) const;
};


#endif //TERMINAL_3D_GRAPHICS_ENGINE_VEC4_H
