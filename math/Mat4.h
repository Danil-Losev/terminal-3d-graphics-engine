//
// Created by user on 05.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_MAT4_H
#define TERMINAL_3D_GRAPHICS_ENGINE_MAT4_H
#include <array>

#include "Vec3.h"
#include "Vec4.h"
#include "../scene/scene.h"

class Mat4
{
private:
    float matrix[4][4];

public:
    Mat4();
    explicit Mat4(float matrix[4][4]);
    Mat4(const Mat4& mat);
    Mat4& operator=(const Mat4& mat) = default;

    Mat4 operator*(const Mat4& mat) const;
    Mat4 operator*(float scalar) const;
    Mat4 operator/(float scalar) const;

    Vec4 operator*(const Vec4& vec) const;

    float* operator[](size_t index);

    static Mat4 makePerspective(float fov, int screenHeight = scene::getMainScene()->getHeight(),
                                int screenWidth = scene::getMainScene()->getWidth(),
                                float near = scene::getMainScene()->getNearPlane(),
                                float far = scene::getMainScene()->getFarPlane());
    static Mat4 makeEye();
    static Mat4 scale(float x, float y, float z);
    static Mat4 rotationX(float angle);
    static Mat4 rotationY(float angle);
    static Mat4 rotationZ(float angle);
    static Mat4 translation(float x, float y, float z);
    static Mat4 lookAt(const Vec3& cameraPosition, const Vec3& target, const Vec3& up = Vec3(0, 1, 0));
    static Mat4 lookAtMoveable(const Vec3& cameraPosition, const Vec3& direction, const Vec3& up = Vec3(0, 1, 0));
};


#endif //TERMINAL_3D_GRAPHICS_ENGINE_MAT4_H
