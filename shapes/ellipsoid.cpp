//
// Created by user on 09.11.2025.
//

#include "ellipsoid.h"

ellipsoid::ellipsoid()
{
    this->radiusX = 1.0f;
    this->radiusY = 1.0f;
    this->radiusZ = 1.0f;

    int latitudeSegments = 24;
    int longitudeSegments = 24;
    const Vec3 center(0, 0, 0);

    const float PI = 3.1415926535f;
    for (int i = 0; i <= longitudeSegments; ++i)
    {
        float v = static_cast<float>(i) / longitudeSegments;
        float phi = v * PI;

        for (int j = 0; j <= latitudeSegments; ++j)
        {
            float u = static_cast<float>(j) / latitudeSegments;
            float theta = u * 2.0f * PI;

            float x = radiusX * sin(phi) * cos(theta);
            float y = radiusY * cos(phi);
            float z = radiusZ * sin(phi) * sin(theta);
            vertices.emplace_back(center + Vec3(x, y, z));
        }
    }

    // Рёбра (соединяем соседние точки, как сетку широт/долгот)
    for (int i = 0; i < longitudeSegments; ++i)
    {
        for (int j = 0; j < latitudeSegments; ++j)
        {
            int first = i * (latitudeSegments + 1) + j;
            int second = first + latitudeSegments + 1;
            edges.push_back({first, second});
            edges.push_back({first, first + 1});
        }
    }
}

ellipsoid::ellipsoid(const Vec3& center, float radiusX, float radiusY, float radiusZ, int latitudeSegments,
                     int longitudeSegments)
{
    this->radiusX = radiusX;
    this->radiusY = radiusY;
    this->radiusZ = radiusZ;
    const float PI = 3.1415926535f;
    for (int i = 0; i <= longitudeSegments; ++i)
    {
        float v = static_cast<float>(i) / longitudeSegments;
        float phi = v * PI;

        for (int j = 0; j <= latitudeSegments; ++j)
        {
            float u = static_cast<float>(j) / latitudeSegments;
            float theta = u * 2.0f * PI;

            float x = radiusX * sin(phi) * cos(theta);
            float y = radiusY * cos(phi);
            float z = radiusZ * sin(phi) * sin(theta);
            vertices.emplace_back(center + Vec3(x, y, z));
        }
    }

    // Рёбра (соединяем соседние точки, как сетку широт/долгот)
    for (int i = 0; i < longitudeSegments; ++i)
    {
        for (int j = 0; j < latitudeSegments; ++j)
        {
            int first = i * (latitudeSegments + 1) + j;
            int second = first + latitudeSegments + 1;
            edges.push_back({first, second});
            edges.push_back({first, first + 1});
        }
    }
}

float ellipsoid::getPerimeter() const
{
    return 0.0f; // Периметр эллипсоида не определён
}

float ellipsoid::getSquare() const
{
    return 4.0f * 3.1415926535f *
        ((pow(radiusX * radiusY, 1.6f) + pow(radiusX * radiusZ, 1.6f) + pow(radiusY * radiusZ, 1.6f)) / 3.0f);
    // Приблизительная площадь поверхности эллипсоида
}
