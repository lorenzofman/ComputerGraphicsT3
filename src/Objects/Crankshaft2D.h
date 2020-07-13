#pragma once

#include "Crankshaft.h"

class Crankshaft2D : public Crankshaft
{
	public:
    Crankshaft2D(float rpm, float radius, float rodLength);
	void Draw(Float2 pin, Float2 pos) override;
};