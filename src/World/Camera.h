#pragma once

#include "../Primitives/Float2.h"
#include "../Primitives/Float3.h"
#include "../Objects/Triangle.h"
#include "../Objects/Object.h"

class Camera
{
    public:

    explicit Camera(float fieldOfView);
    Float3 position;
    Float3 rotation;
    Float2 WorldToDisplay(Float3 worldPoint) const;
    void DrawFace(const Face& face) const;
    void Draw(const Object& obj) const;
    private:


    float fieldOfView;
    Float3 WorldToView(Float3 worldPoint) const;
    Float2 ViewToProjection(Float3 viewPoint) const;
    static Float2 ProjectionToDisplay(Float2 projectionPoint);
};