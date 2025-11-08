//
// Created by user on 08.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_SPHERE_H
#define TERMINAL_3D_GRAPHICS_ENGINE_SPHERE_H

#include <vector>
#include "shape.h"
#include "../math/Vec3.h"

struct Face
{
    int v1, v2, v3;
};

class sphere final : public shape
{
private:
    float radius = 0.0f;
    std::vector<Face> faces;

public:
    sphere();
    sphere(const Vec3& center, float radius, int latitudeSegments = 24, int longitudeSegments = 24);


    float getPerimeter() const override;
    float getSquare() const override;
    ~sphere() override = default;
};


#endif //TERMINAL_3D_GRAPHICS_ENGINE_SPHERE_H
