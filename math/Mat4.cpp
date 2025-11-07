//
// Created by user on 05.11.2025.
//

#include "Mat4.h"
#include <cmath>

Mat4::Mat4()
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
}

Mat4::Mat4(float matrix[4][4])
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            this->matrix[i][j] = matrix[i][j];
        }
    }
}


Mat4::Mat4(const Mat4& mat)
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            this->matrix[i][j] = mat.matrix[i][j];
        }
    }
}

Mat4 Mat4::operator*(const Mat4& mat) const
{
    Mat4 result{};
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i][j] = 0;
            for (size_t k = 0; k < 4; k++)
            {
                result[i][j] += this->matrix[i][k] * mat.matrix[k][j];
            }
        }
    }
    return result;
}

Mat4 Mat4::operator*(const float scalar) const
{
    Mat4 result{};
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i][j] = this->matrix[i][j] * scalar;
        }
    }
    return result;
}

Mat4 Mat4::operator/(const float scalar) const
{
    Mat4 result{};
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i][j] = this->matrix[i][j] / scalar;
        }
    }
    return result;
}

Vec4 Mat4::operator*(const Vec4& vec) const
{
    Vec4 result{};
    result.X(this->matrix[0][0] * vec.X() + this->matrix[0][1] * vec.Y() +
        this->matrix[0][2] * vec.Z() + this->matrix[0][3] * vec.W());
    result.Y(this->matrix[1][0] * vec.X() + this->matrix[1][1] * vec.Y() +
        this->matrix[1][2] * vec.Z() + this->matrix[1][3] * vec.W());
    result.Z(this->matrix[2][0] * vec.X() + this->matrix[2][1] * vec.Y() +
        this->matrix[2][2] * vec.Z() + this->matrix[2][3] * vec.W());
    result.W(this->matrix[3][0] * vec.X() + this->matrix[3][1] * vec.Y() +
        this->matrix[3][2] * vec.Z() + this->matrix[3][3] * vec.W());
    return result;
}

float* Mat4::operator[](const size_t index)
{
    return this->matrix[index];
}

Mat4 Mat4::makePerspective(float fov, const int screenHeight, const int screenWidth,
                           const float near, const float far)
{
    Mat4 perspectiveProjectionMatrix{};
    const float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
    fov *= 0.01745329251; // 3.14159265358979323846 / 180
    const float f = 1.0f / std::tan(fov / 2.0f);
    const float nearMinusFar = near - far;
    perspectiveProjectionMatrix[0][0] = f / aspectRatio;
    perspectiveProjectionMatrix[1][1] = f;
    perspectiveProjectionMatrix[2][2] = (far + near) / (nearMinusFar);
    perspectiveProjectionMatrix[2][3] = (2.0f * far * near) / (nearMinusFar);
    perspectiveProjectionMatrix[3][2] = -1.0f;
    perspectiveProjectionMatrix[3][3] = 0.0f;
    return perspectiveProjectionMatrix;
}

Mat4 Mat4::makeEye()
{
    Mat4 eyeMatrix{};
    eyeMatrix[0][0] = 1.0f;
    eyeMatrix[1][1] = 1.0f;
    eyeMatrix[2][2] = 1.0f;
    eyeMatrix[3][3] = 1.0f;
    return eyeMatrix;
}

Mat4 Mat4::scale(const float x, const float y, const float z)
{
    Mat4 scaleMatrix = Mat4::makeEye();
    scaleMatrix[0][0] = x;
    scaleMatrix[1][1] = y;
    scaleMatrix[2][2] = z;
    return scaleMatrix;
}

Mat4 Mat4::rotationX(const float angle)
{
    Mat4 rotationMatrix = Mat4::makeEye();
    const float angleCos = std::cos(angle);
    const float angleSin = std::sin(angle);
    rotationMatrix[1][1] = angleCos;
    rotationMatrix[1][2] = -angleSin;
    rotationMatrix[2][1] = angleSin;
    rotationMatrix[2][2] = angleCos;
    return rotationMatrix;
}

Mat4 Mat4::rotationY(const float angle)
{
    Mat4 rotationMatrix = Mat4::makeEye();
    const float angleCos = std::cos(angle);
    const float angleSin = std::sin(angle);
    rotationMatrix[0][0] = angleCos;
    rotationMatrix[0][2] = angleSin;
    rotationMatrix[2][0] = -angleSin;
    rotationMatrix[2][2] = angleCos;
    return rotationMatrix;
}

Mat4 Mat4::rotationZ(const float angle)
{
    Mat4 rotationMatrix = Mat4::makeEye();
    const float angleCos = std::cos(angle);
    const float angleSin = std::sin(angle);
    rotationMatrix[0][0] = angleCos;
    rotationMatrix[0][1] = -angleSin;
    rotationMatrix[1][0] = angleSin;
    rotationMatrix[1][1] = angleCos;
    return rotationMatrix;
}

Mat4 Mat4::translation(const float x, const float y, const float z)
{
    Mat4 translationMatrix = Mat4::makeEye();
    translationMatrix[0][3] = x;
    translationMatrix[1][3] = y;
    translationMatrix[2][3] = z;
    return translationMatrix;
}

Mat4 Mat4::lookAt(const Vec3& cameraPosition, const Vec3& target, const Vec3& up)
{
    const Vec3 zAxis = (cameraPosition - target).normalize();
    const Vec3 xAxis = (up.vectorMultiplication(zAxis)).normalize();
    const Vec3 yAxis = zAxis.vectorMultiplication(xAxis);
    Mat4 viewMatrix{};
    viewMatrix[0][0] = xAxis.X();
    viewMatrix[0][1] = xAxis.Y();
    viewMatrix[0][2] = xAxis.Z();
    viewMatrix[0][3] = -xAxis.scalarMultiplication(cameraPosition);
    viewMatrix[1][0] = yAxis.X();
    viewMatrix[1][1] = yAxis.Y();
    viewMatrix[1][2] = yAxis.Z();
    viewMatrix[1][3] = -yAxis.scalarMultiplication(cameraPosition);
    viewMatrix[2][0] = zAxis.X();
    viewMatrix[2][1] = zAxis.Y();
    viewMatrix[2][2] = zAxis.Z();
    viewMatrix[2][3] = -zAxis.scalarMultiplication(cameraPosition);
    viewMatrix[3][0] = 0.0f;
    viewMatrix[3][1] = 0.0f;
    viewMatrix[3][2] = 0.0f;
    viewMatrix[3][3] = 1.0f;
    return viewMatrix;
}

Mat4 Mat4::lookAtMoveable(const Vec3& cameraPosition, const Vec3& direction, const Vec3& up)
{
    const Vec3 z = (direction - cameraPosition).normalize();
    const Vec3 x = (up.vectorMultiplication(z)).normalize();
    const Vec3 y = z.vectorMultiplication(x);
    Mat4 viewMatrix{};
    viewMatrix[0][0] = x.X();
    viewMatrix[0][1] = x.Y();
    viewMatrix[0][2] = x.Z();
    viewMatrix[0][3] = -x.scalarMultiplication(cameraPosition);
    viewMatrix[1][0] = y.X();
    viewMatrix[1][1] = y.Y();
    viewMatrix[1][2] = y.Z();
    viewMatrix[1][3] = -y.scalarMultiplication(cameraPosition);
    viewMatrix[2][0] = z.X();
    viewMatrix[2][1] = z.Y();
    viewMatrix[2][2] = z.Z();
    viewMatrix[2][3] = -z.scalarMultiplication(cameraPosition);
    return viewMatrix;
}
