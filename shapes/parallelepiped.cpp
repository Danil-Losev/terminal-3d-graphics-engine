//
// Created by user on 08.11.2025.
//

#include "parallelepiped.h"

parallelepiped::parallelepiped()
{
    this->vertices = {
        {-1, -1, -1}, {1, -1, -1},
        {1, 1, -1}, {-1, 1, -1},
        {-1, -1, 1}, {1, -1, 1},
        {1, 1, 1}, {-1, 1, 1}
    };

    this->edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };
    this->model = Mat4::makeEye();
}

parallelepiped::parallelepiped(const Vec3& corner, const float width, const float height, const float depth)
{
    this->vertices = {
        corner,
        Vec3(corner.X() + width, corner.Y(), corner.Z()),
        Vec3(corner.X() + width, corner.Y() + height, corner.Z()),
        Vec3(corner.X(), corner.Y() + height, corner.Z()),
        Vec3(corner.X(), corner.Y(), corner.Z() + depth),
        Vec3(corner.X() + width, corner.Y(), corner.Z() + depth),
        Vec3(corner.X() + width, corner.Y() + height, corner.Z() + depth),
        Vec3(corner.X(), corner.Y() + height, corner.Z() + depth)
    };
    this->edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };
    this->model = Mat4::makeEye();
}

parallelepiped::parallelepiped(const parallelepiped& other)
{
    this->vertices = other.vertices;
    this->edges = other.edges;
    this->model = other.model;
}

parallelepiped::parallelepiped(const std::vector<Vec3>& vertices, const std::vector<edge>& edges)
{
    this->vertices = vertices;
    this->edges = edges;
    this->model = Mat4::makeEye();
}

float parallelepiped::getPerimeter() const
{
    float perimeter = 0.0f;
    for (const auto& e : this->edges)
    {
        Vec3 v1 = this->vertices[e.v1];
        Vec3 v2 = this->vertices[e.v2];
        perimeter += (v2 - v1).length();
    }
    return perimeter;
}

float parallelepiped::getSquare() const
{
    return 0.0f; // Площадь поверхности параллелепипеда можно реализовать при необходимости
}
