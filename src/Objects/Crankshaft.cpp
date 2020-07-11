#include "Crankshaft.h"
#include "../Primitives/Constants.h"
#include "../Canvas2D/Canvas2D.h"
#include "../World/Screen.h"

Crankshaft::Crankshaft(float rpm, float radius, float rodLength)
{
	angularVelocity = 2 * PI * rpm / 60;
	halfStroke = radius;
	this->rodLength = rodLength;
}

void Crankshaft::Update(float deltaTime)
{
	angle += deltaTime * angularVelocity;
}

Float2 Bhaskara(float a, float b, float c)
{
	auto delta = b * b - 4 * a * c;
	if (delta < 0)
	{
		return {NAN, NAN};
	}
	auto sq = sqrtf(delta);
	return Float2(-b - sq, -b + sq) * (1 / (2 * a));
}


void Crankshaft::Draw()
{
	const Float2 pos = Float2(cosf(angle), sinf(angle)) * halfStroke + Screen::Center();
	auto bhaskara = Bhaskara(1, -2 * halfStroke * cosf(angle) , -rodLength * rodLength + halfStroke * halfStroke);
	auto solver = (bhaskara.x > 0) ? bhaskara.x : bhaskara.y;

	const Float2 pin = Float2((float) Screen::Width / 2.0f, solver + (float) Screen::Height / 2);

	const Float2 pin2 = Float2((float) Screen::Width / 2.0f, solver + (float) Screen::Height / 2);

	Canvas2D::SetColor({1, 1, 1});
	Canvas2D::DrawCircle(Screen::Center(), halfStroke, 32);
	Canvas2D::DrawCircle(pos, halfStroke/4, 32);
	Canvas2D::DrawLine(pos, pin);

}
