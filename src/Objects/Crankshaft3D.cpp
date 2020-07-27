#include "Crankshaft3D.h"
#include "../World/Screen.h"
#include "ObjectCreator.h"
#include "../Canvas2D/Canvas2D.h"

Crankshaft3D::Crankshaft3D(float rpm, float radius, float rodLength, float pistonSize, Camera& camera, float pos, float initialRotation) : Crankshaft(rpm, radius, rodLength, initialRotation), camera(camera)
{
	rod = ObjectCreator::BuildBox(0.1f, rodLength, 0.1f);
	crankCounterWeight = ObjectCreator::BuildFlatRoundedRectangle(radius * 2, 0.1f, 0.1f, 32);
	crank = ObjectCreator::BuildFlatRoundedRectangle(radius, 0.1f, 0.1f, 32);
	piston = ObjectCreator::BuildCylinder(32, 0.131f, pistonSize);
	cylinder = ObjectCreator::BuildMotorCylinder(32, 0.141f, pistonSize + rodLength - radius);

	piston.position = Float3(0, 0, pos);
	cylinder.position = Float3(0, rodLength + pistonSize / 2, pos);

	rod.position = Float3(0, 0, pos);
	crank.position = Float3(	0, 0, pos - 0.1f);
	crankCounterWeight.position = Float3(0, 0, pos + 0.1f);

	piston.rotation = {0, 0, PI / 2};
	cylinder.rotation ={-PI / 2, 0, PI / 2};
	this->pistonSize = pistonSize;

	drawingMask = Mask::Piston | Mask::Crank | Mask::Rod | Mask::Cylinder | Mask::CounterWeight;
}

void Crankshaft3D::Draw(Float2 pistonPin, Float2 crankPosition)
{
	piston.position.y = pistonPin.y + pistonSize / 2;
	AlignWithVector(pistonPin, crankPosition, rod);
	AlignWithVector({0,0}, crankPosition, crank);
	AlignWithVector(crankPosition, - crankPosition, crankCounterWeight);
	Canvas2D::SetColor({0.8f, 0.8f, 0.8f});

	DrawObject(piston, Mask::Piston);
	DrawObject(rod, Mask::Rod);
	DrawObject(crank, Mask::Crank);
	DrawObject(cylinder, Mask::Cylinder);
	DrawObject(crankCounterWeight, Mask::CounterWeight);
	Canvas2D::SetColor({0, 1, 1});
	if ((drawingMask & Mask::Normals) > 0)
	{
		DrawNormals(piston, Mask::Piston);
		DrawNormals(rod, Mask::Rod);
		DrawNormals(crank, Mask::Crank);
		DrawNormals(cylinder, Mask::Cylinder);
		DrawNormals(crankCounterWeight, Mask::CounterWeight);
	}
}

void Crankshaft3D::DrawNormals(const Object& object, byte mask)
{
    if ((mask & drawingMask) == 0)
    {
        return;
    }
	// Faces are always planar and their normal are defined by 3 points
	for (auto face : object.faces)
	{
		face.Rotate(object.rotation);
		face.Translate(object.position);
		Float3 p1 = face.points[0];
		Float3 p2 = face.points[1];
		Float3 p3 = face.points[2];

		Float3 u = p2 - p1;
		Float3 v = p3 - p1;

		Float3 n = Float3(
				u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x).GetNormalized();
		Float3 center = FaceCenter(face);
		Canvas2D::DrawLine(camera.WorldToDisplay(center), camera.WorldToDisplay(center + n * 0.1f));
	}
}

Float3 Crankshaft3D::FaceCenter(const Face& face)
{
	Float3 center = {0, 0, 0};
	for (auto& point : face.points)
	{
		center += point;
	}
	return center / (float) face.points.size();
}

void Crankshaft3D::DrawObject(Object& obj, byte mask) const
{
	if ((mask & drawingMask) > 0)
	{
		camera.Draw(obj);
	}
}

void Crankshaft3D::AlignWithVector(Float2 a, Float2 b, Object& object)
{
	Float2 mid = (a + b) * 0.5f;
	object.position = {mid.x, mid.y, object.position.z};
	Float2 vec = a - b;
	float ang = atan2f(vec.y, vec.x);
	object.rotation = {PI / 2 - ang, 0, 0};
}