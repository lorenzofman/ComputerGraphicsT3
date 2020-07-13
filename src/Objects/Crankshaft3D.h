#pragma once

#include "Crankshaft.h"

class Crankshaft3D : public Crankshaft
{
	public:
	Crankshaft3D(float rpm, float radius, float rodLength);

	void Draw(Float2 pin, Float2 pos) override;
};