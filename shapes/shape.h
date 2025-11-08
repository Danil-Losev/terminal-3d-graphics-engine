//
// Created by user on 08.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_SHAPE_H
#define TERMINAL_3D_GRAPHICS_ENGINE_SHAPE_H

#include "../math/Vec3.h"
#include <vector>
#include "../math/Mat4.h"

struct edge
{
    int v1;
    int v2;
};

class shape
{
protected:
    std::vector<Vec3> vertices;
    std::vector<edge> edges;
    Mat4 model;

public:
    virtual const std::vector<Vec3>& getVertices() const =0;
    virtual const std::vector<edge>& getEdges() const = 0;
    virtual const Mat4& getModel() const = 0;
    virtual float getPerimeter() const = 0;
    virtual float getSquare() const = 0;

    virtual ~shape() = default;
};


#endif //TERMINAL_3D_GRAPHICS_ENGINE_SHAPE_H
