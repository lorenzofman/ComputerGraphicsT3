#include "Crankshaft3D.h"
#include "../World/Screen.h"
#include "ObjectCreator.h"

Crankshaft3D::Crankshaft3D(float rpm, float radius, float rodLength, float pistonSize, Camera& camera, float pos, float initialRotation) : Crankshaft(rpm, radius, rodLength, initialRotation), camera(camera)
{
	rod = ObjectCreator::BuildBox(0.1f, rodLength, 0.1f);
	crankCounterWeight = ObjectCreator::BuildFlatRoundedRectangle(radius * 2, 0.1f, 0.1f, 32);
	crank = ObjectCreator::BuildFlatRoundedRectangle(radius, 0.1f, 0.1f, 32);
	piston = ObjectCreator::BuildCylinder(32, 0.141f, pistonSize);

	piston.position = Float3(0, 0, pos);
	rod.position = Float3(0, 0, pos);
	crank.position = Float3(0, 0, pos - 0.1f);
	crankCounterWeight.position = Float3(0, 0, pos + 0.1f);

	piston.rotation = {0, 0, PI / 2};
	this->pistonSize = pistonSize;
}

void Crankshaft3D::Draw(Float2 pistonPin, Float2 crankPosition)
{
	piston.position.y = pistonPin.y + pistonSize / 2;
	AlignWithVector(pistonPin, crankPosition, rod);
	AlignWithVector({0,0}, crankPosition, crank);
	AlignWithVector(crankPosition, - crankPosition, crankCounterWeight);

	camera.Draw(rod);
	camera.Draw(crank);
	camera.Draw(piston);
	camera.Draw(crankCounterWeight);
}

void Crankshaft3D::AlignWithVector(Float2 a, Float2 b, Object& object)
{
	Float2 mid = (a + b) * 0.5f;
	object.position = {mid.x, mid.y, object.position.z};
	Float2 vec = a - b;
	float ang = atan2f(vec.y, vec.x);
	object.rotation = {PI / 2 - ang, 0, 0};
}

