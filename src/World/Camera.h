#pragma once

#include "../Primitives/Float2.h"
#include "../Primitives/Float3.h"

class Camera
{
    public:

    Camera(float fieldOfView);
    Float3 position;
    Float3 rotation;
    Float2 WorldToDisplay(Float3 worldPoint) const;

    private:

    float fieldOfView;
    Float3 WorldToView(Float3 worldPoint) const;
    Float2 ViewToProjection(Float3 viewPoint) const;
    static Float2 ProjectionToDisplay(Float2 projectionPoint);
};