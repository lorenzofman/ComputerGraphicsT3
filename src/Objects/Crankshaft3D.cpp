#include "Crankshaft3D.h"
#include "../Primitives/Constants.h"
#include "../Canvas2D/Canvas2D.h"
#include "../World/Screen.h"
#include "../Helpers/Utils.h"

Crankshaft3D::Crankshaft3D(float rpm, float radius, float rodLength)
{
	angularVelocity = 2 * PI * rpm / 60;
	halfStroke = radius;
	this->rodLength = rodLength;
}

void Crankshaft3D::Update(float deltaTime)
{
	angle += deltaTime * angularVelocity;
}


void Crankshaft3D::Draw() const
{
	const Float2 pos = Float2(cosf(angle), sinf(angle)) * halfStroke + Screen::Center();
	auto bhaskara = Utils::Bhaskara(1, -2 * halfStroke * cosf(angle), -rodLength * rodLength + halfStroke * halfStroke);
	auto solver = (bhaskara.x > 0) ? bhaskara.x : bhaskara.y;

	const Float2 pin = Float2((float) Screen::Width / 2.0f, solver + (float) Screen::Height / 2);

	const Float2 pin2 = Float2((float) Screen::Width / 2.0f, solver + (float) Screen::Height / 2);
}
