#include <cmath>
#include "Camera.h"
#include "Screen.h"
#include "../Primitives/Constants.h"
#include "../Canvas2D/Canvas2D.h"

Camera::Camera(float fieldOfView)
{
    this->fieldOfView = fieldOfView;
    position = {0, 0, 0};
}

Float3 Camera::WorldToView(Float3 worldPoint) const
{
    return worldPoint.Rotate(- rotation) - position;
}

Float2 Camera::ViewToProjection(Float3 viewPoint) const
{
    float aspectRatio = (float) Screen::Height / (float) Screen::Width;
    const float fovDistance = 1.0f / tanf(fieldOfView * 0.5f * DegToRad);
    float zDistance = viewPoint.z - position.z;
    if (zDistance <= 0)
    {
        return {NAN, NAN};
    }
    return {aspectRatio * fovDistance * viewPoint.x / zDistance, viewPoint.y * fovDistance / zDistance};
}

Float2 Camera::ProjectionToDisplay(Float2 projectionPoint)
{
    return projectionPoint.Scale(Screen::Size()) + Screen::Center();
}

Float2 Camera::WorldToDisplay(Float3 worldPoint) const
{
    return ProjectionToDisplay(ViewToProjection(WorldToView(worldPoint)));
}

void Camera::DrawTriangle(Triangle tri)
{
    Float2 a = WorldToDisplay(tri.a);
    Float2 b = WorldToDisplay(tri.b);
    Float2 c = WorldToDisplay(tri.c);

    Canvas2D::DrawTriangle(a, b, c);
}

void Camera::Draw(Object obj)
{
    for (auto tri : obj.triangles)
    {
        DrawTriangle(tri);
    }
}
