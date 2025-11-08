//
// Created by user on 08.11.2025.
//

#include "shape.h"

const std::vector<Vec3>& shape::getVertices() const
{
    return this->vertices;
}

const std::vector<edge>& shape::getEdges() const
{
    return this->edges;
}

const Mat4& shape::getModel() const
{
    return this->model;
}

const void shape::setModel(const Mat4& model)
{
    this->model = model;
}
