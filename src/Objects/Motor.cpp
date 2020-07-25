#include "Motor.h"

Motor::Motor(float rpm, float radius, float rodLength, float pistonSize, Camera& camera)
{
	for (int i = 0; i < 4; i++)
	{
		crankshafts.emplace_back(rpm, radius, rodLength, 0.5f, camera, PI * 0.1f * (float)i, (i == 0 || i == 3) ? 0 : PI);
	}
}

void Motor::UpdateRpm(float rpm)
{
	for (auto& crankshaft : crankshafts)
	{
		crankshaft.UpdateRpm(rpm);
	}
}

void Motor::Update(float tick)
{
	for (auto& crankshaft : crankshafts)
	{
		crankshaft.Update(tick);
	}
}

void Motor::InvertBitFlag(uint i)
{
	for (auto& crankshaft : crankshafts)
	{
		crankshaft.drawingMask ^= 1UL << i;
	}
}