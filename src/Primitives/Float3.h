#pragma once
#include <cmath>
struct Float3
{
    float x, y, z;

    Float3()
    {
        x = y = z = 0;
    }

    Float3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Float3 operator+(Float3 const& obj) const
    {
        return {x + obj.x, y + obj.y, z + obj.z};
    }

    void operator+=(Float3 const& obj)
    {
        x += obj.x;
        y += obj.y;
        z += obj.z;
    }

    Float3 operator-() const
    {
        return {-x, -y, -z};
    }

    Float3 operator-(Float3 const& obj) const
    {
        return {x - obj.x, y - obj.y, z - obj.z};
    }

    void operator-=(Float3 const& obj)
    {
        x -= obj.x;
        y -= obj.y;
    }

    Float3 operator*(float const &constant) const
    {
        return {x * constant, y * constant, z * constant};
    }

    void operator*=(float const& constant)
    {
        x *= constant;
        y *= constant;
        z *= constant;
    }

    Float3 Rotate(Float3 euler) const
    {
        float alpha = euler.x;
        float beta = euler.y;
        float gamma = euler.z;

        float rx =
                this->x * cosf(alpha) * cosf(beta) +
                this->y * sinf(alpha) * cosf(beta) -
                this->z * sinf(beta);

        float ry =
                this->x * (cosf(alpha) * sinf(beta) * sinf(gamma) - sinf(alpha) * cosf(gamma)) +
                this->y * (sinf(alpha) * sinf(beta) * sinf(gamma) + cosf(alpha) * cosf(gamma)) +
                this->z * cosf(beta) * sinf(gamma);

        float rz =
                this->x * (cosf(alpha) * sinf(beta) * cosf(gamma) + sinf(alpha) * sinf(gamma)) +
                this->y * (sinf(alpha) * sinf(beta) * cosf(gamma) - cosf(alpha) * sinf(gamma)) +
                this->z * cosf(beta) * cosf(gamma);

        return {rx, ry, rz};
    }
};