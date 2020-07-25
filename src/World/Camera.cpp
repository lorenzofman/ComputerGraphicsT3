#include <cmath>
#include <iostream>
#include "Camera.h"
#include "Screen.h"
#include "../Primitives/Constants.h"
#include "../Canvas2D/Canvas2D.h"

Camera::Camera(float fieldOfView)
{
    this->fieldOfView = fieldOfView;
    position = {0, 0, 0};
	projection = ProjectionType::Perspective;
	shader = ShaderType::Wireframe;
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
    if (projection == ProjectionType::Orthographic)
	{
		return {aspectRatio * fovDistance * viewPoint.x, viewPoint.y * fovDistance};
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

void Camera::DrawFace(const Face& face) const
{
	std::vector<Float2> points;
	points.reserve(face.points.size());
	for (auto & point : face.points)
	{
		points.push_back(WorldToDisplay(point));
	}

	switch (shader)
	{
		case ShaderType::Wireframe:
			Canvas2D::DrawPolygon(points.data(), points.size());
			break;
		case ShaderType::Unlit:
			Canvas2D::DrawFilledPolygon(points.data(), points.size());
			break;
		case ShaderType::Lit:
			break;
	}
}

void Camera::Draw(const Object& obj) const
{
	for (auto face : obj.faces)
    {
    	face.Rotate(obj.rotation);
    	face.Translate(obj.position);
		DrawFace(face);
    }
}
