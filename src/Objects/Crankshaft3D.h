#pragma once

#include "Crankshaft.h"
#include "../World/Camera.h"

class Crankshaft3D : public Crankshaft
{
	public:

	struct Mask
	{
		static const byte Piston = 1U;
		static const byte Crank = Piston << 1U;
		static const byte Rod = Crank << 1U;
		static const byte Cylinder = Rod << 1U;
		static const byte CounterWeight = Cylinder << 1U;
		static const byte Normals = CounterWeight << 1U;
	};
	Crankshaft3D(float rpm, float radius, float rodLength, float pistonSize, Camera& camera, float pos, float initialRotation);

	byte drawingMask;

	protected:
	void Draw(Float2 pistonPin, Float2 crankPosition) override;

	private:
	Camera& camera;
	Object rod;
	Object crankCounterWeight;
	Object piston;
	Object crank;
	Object cylinder;
	float pistonSize;

	void DrawNormals(const Object& object);
	static Float3 FaceCenter(const Face& face);

	static void AlignWithVector(Float2 a, Float2 b, Object& object);

	void DrawObject(Object &obj, byte mask) const;
};