//
// Created by user on 08.11.2025.
//

#include "sphere.h"

sphere::sphere()
{
    const Vec3 center(0, 0, 0);
    this->radius = 1.0f;
    constexpr int latitudeSegments = 24;
    constexpr int longitudeSegments = 24;

    // Вершины
    for (int i = 0; i <= longitudeSegments; ++i)
    {
        const float theta = static_cast<float>(i) * 3.1415926535f / static_cast<float>(longitudeSegments);
        for (int j = 0; j <= latitudeSegments; ++j)
        {
            const float phi = static_cast<float>(j) * 2.0f * 3.1415926535f / static_cast<float>(latitudeSegments);
            float x = center.X() + radius * sinf(theta) * cosf(phi);
            float y = center.Y() + radius * sinf(theta) * sinf(phi);
            float z = center.Z() + radius * cosf(theta);
            vertices.emplace_back(x, y, z);
        }
    }

    // Грани и рёбра
    for (int i = 0; i < longitudeSegments; ++i)
    {
        for (int j = 0; j < latitudeSegments; ++j)
        {
            const int first = i * (latitudeSegments + 1) + j;
            const int second = first + latitudeSegments + 1;

            faces.push_back({first, second, first + 1});
            faces.push_back({second, second + 1, first + 1});

            edges.push_back({first, second});
            edges.push_back({first, first + 1});
        }
    }
}

sphere::sphere(const Vec3& center, const float radius, const int latitudeSegments, const int longitudeSegments)
{
    this->radius = radius;
    for (int i = 0; i <= longitudeSegments; ++i)
    {
        const float theta = static_cast<float>(i) * 3.1415926535f / static_cast<float>(longitudeSegments);
        for (int j = 0; j <= latitudeSegments; ++j)
        {
            const float phi = static_cast<float>(j) * 2.0f * 3.1415926535f / static_cast<float>(latitudeSegments);
            float x = center.X() + radius * sinf(theta) * cosf(phi);
            float y = center.Y() + radius * sinf(theta) * sinf(phi);
            float z = center.Z() + radius * cosf(theta);
            vertices.emplace_back(x, y, z);
        }
    }

    // Грани и рёбра
    for (int i = 0; i < longitudeSegments; ++i)
    {
        for (int j = 0; j < latitudeSegments; ++j)
        {
            const int first = i * (latitudeSegments + 1) + j;
            const int second = first + latitudeSegments + 1;

            faces.push_back({first, second, first + 1});
            faces.push_back({second, second + 1, first + 1});

            edges.push_back({first, second});
            edges.push_back({first, first + 1});
        }
    }
}

float sphere::getPerimeter() const
{
    return 2.0f * 3.1415926535f * radius;
}

float sphere::getSquare() const
{
    return 4.0f * 3.1415926535f * radius * radius;
}
