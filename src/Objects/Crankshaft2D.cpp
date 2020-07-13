#include "Crankshaft2D.h"
#include "../Primitives/Constants.h"
#include "../Canvas2D/Canvas2D.h"
#include "../World/Screen.h"

Crankshaft2D::Crankshaft2D(float rpm, float radius, float rodLength) : Crankshaft(rpm, radius, rodLength) {}

void Crankshaft2D::Draw(Float2 pin, Float2 pos)
{
	Canvas2D::SetColor({1, 1, 1});
	Canvas2D::DrawCircle(Screen::Center(), 64, 32);
	Canvas2D::DrawCircle(pos, 16, 32);
	Canvas2D::DrawLine(pos, pin);
}