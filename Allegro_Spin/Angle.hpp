#pragma once
#include <cmath>
class Angle
{
private:
	const float pi = 3.14159265;
	float defaultVal;
	float value;
	float cos;
	float sin;
	
public:
	float inc;
	float x;
	float y;
	Angle();
	Angle(float v0);
	Angle(float v0, float i0);
	Angle(float x0, float y0, float v0, float i0);
	void Inc(float side);
	float GetVal() const;
	float GetCos() const;
	float GetSin() const;
	void SetValue(float n);
};