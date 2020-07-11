#include <cmath>
#include "Camera.h"
#include "Screen.h"
#include "../Primitives/Constants.h"

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
        return {0, 0};
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