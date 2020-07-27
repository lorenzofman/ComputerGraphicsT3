#pragma once

#include "../Primitives/Float2.h"
#include "../Primitives/Float3.h"
#include "../Objects/Triangle.h"
#include "../Objects/Object.h"
#include "../Primitives/Types.h"

class Camera
{
    public:

	enum class ProjectionType
	{
		Perspective, Orthographic
	};

	enum class ShaderType
	{
		Wireframe, Unlit
	};

	Float3 position;
	Float3 rotation;
	float fieldOfView;
	ProjectionType projection;
	ShaderType shader;

	explicit Camera(float fieldOfView);


	Float2 WorldToDisplay(Float3 worldPoint) const;

    void DrawFace(const Face& face) const;
    void Draw(const Object& obj) const;

    private:

    Float3 WorldToView(Float3 worldPoint) const;
    Float2 ViewToProjection(Float3 viewPoint) const;
    static Float2 ProjectionToDisplay(Float2 projectionPoint);
};