//
// Created by user on 09.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_ELLIPSOID_H
#define TERMINAL_3D_GRAPHICS_ENGINE_ELLIPSOID_H
#include <vector>
#include "shape.h"
#include "../math/Vec3.h"

class ellipsoid : public shape
{
    float radiusX = 0.0f;
    float radiusY = 0.0f;
    float radiusZ = 0.0f;

public:
    ellipsoid();
    ellipsoid(const Vec3& center, float radiusX, float radiusY, float radiusZ, int latitudeSegments = 24,
              int longitudeSegments = 24);
    float getPerimeter() const override;
    float getSquare() const override;
    ~ellipsoid() override = default;
};


#endif //TERMINAL_3D_GRAPHICS_ENGINE_ELLIPSOID_H
