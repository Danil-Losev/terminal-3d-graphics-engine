
//
// Created by user on 08.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_CAMERA_H
#define TERMINAL_3D_GRAPHICS_ENGINE_CAMERA_H

#include "../math/Mat4.h"
#include "../math/Vec3.h"


class camera
{
public:
    Vec3 camPos;
    Vec3 camTarget;
    Vec3 camUp;

    Mat4 perspectiveProjectionMatrix;
    camera();
    camera(const Vec3& position, const Vec3& target, const Vec3& up);
    void setPerspectiveProjectionMatrix(const Mat4& projMatrix);
    [[nodiscard]] Mat4 getPerspectiveProjectionMatrix() const;
    ~camera() = default;
};


#endif //TERMINAL_3D_GRAPHICS_ENGINE_CAMERA_H
