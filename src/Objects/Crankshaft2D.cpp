#include "Crankshaft2D.h"
#include "../Primitives/Constants.h"
#include "../Canvas2D/Canvas2D.h"
#include "../World/Screen.h"

Crankshaft2D::Crankshaft2D(float rpm, float radius, float rodLength) : Crankshaft(rpm, radius, rodLength) {}

void Crankshaft2D::Draw(Float2 pistonPin, Float2 crankPosition)
{
	Canvas2D::SetColor({1, 1, 1});
	Canvas2D::DrawCircle(crankPosition + Screen::Center(), 16, 32);
	Canvas2D::DrawLine(crankPosition + Screen::Center(), pistonPin + Screen::Center());
}