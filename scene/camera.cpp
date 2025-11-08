//
// Created by user on 08.11.2025.
//

#include "camera.h"

camera::camera()
{
    this->camPos = Vec3(1.0f, 1.0f, 1.0f);
    this->camTarget = Vec3(0.0f, 0.0f, 0.0f);
    this->camUp = Vec3(0.0f, 1.0f, 0.0f);
}

camera::camera(const Vec3& position, const Vec3& target, const Vec3& up)
{
    this->camPos = position;
    this->camTarget = target;
    this->camUp = up;
}

void camera::setPerspectiveProjectionMatrix(const Mat4& projMatrix)
{
    this->perspectiveProjectionMatrix = projMatrix;
}

Mat4 camera::getPerspectiveProjectionMatrix() const
{
    return this->perspectiveProjectionMatrix;
}
