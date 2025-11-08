//
// Created by user on 08.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_PARALLELEPIPED_H
#define TERMINAL_3D_GRAPHICS_ENGINE_PARALLELEPIPED_H

#include "shape.h"

class parallelepiped final : public shape
{
public:
    parallelepiped();
    parallelepiped(const Vec3& corner, float width, float height, float depth);
    parallelepiped(const parallelepiped& other);
    parallelepiped(const std::vector<Vec3>& vertices, const std::vector<edge>& edges);


    float getPerimeter() const override;
    float getSquare() const override;

    ~parallelepiped() override = default;
};


#endif //TERMINAL_3D_GRAPHICS_ENGINE_PARALLELEPIPED_H
