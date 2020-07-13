//
// Created by Lorenzofman on 7/13/2020.
//

#include <cmath>
#include "Crankshaft.h"
#include "../World/Screen.h"
#include "../Helpers/Utils.h"
#include "../Primitives/Constants.h"

Crankshaft::Crankshaft(float rpm, float radius, float rodLength)
{
	angularVelocity = 2 * PI * rpm / 60;
	halfStroke = radius;
	this->rodLength = rodLength;
}

void Crankshaft::Update(float deltaTime)
{
	angle += deltaTime * angularVelocity;
	const Float2 pos = Float2(cosf(angle), sinf(angle)) * halfStroke + Screen::Center();
	auto bhaskara = Utils::Bhaskara(1, -2 * halfStroke * cosf(angle), -rodLength * rodLength + halfStroke * halfStroke);
	auto solver = (bhaskara.x > 0) ? bhaskara.x : bhaskara.y;
	const Float2 pin = Float2((float) Screen::Width / 2.0f, solver + (float) Screen::Height / 2);

}
