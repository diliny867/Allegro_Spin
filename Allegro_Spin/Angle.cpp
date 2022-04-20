#include "Angle.hpp"

Angle::Angle():
	x(0),
	y(0),
	value(0),
	cos(1),
	sin(0),
	inc(0),
	defaultVal(0)
{}
Angle::Angle(float v0) :
	x(0),
	y(0),
	value(v0),
	cos(std::cos(v0* pi / 180)),
	sin(std::sin(v0* pi / 180)),
	inc(0),
	defaultVal(v0)
{}
Angle::Angle(float v0, float i0):
	x(0),
	y(0),
	value(v0),
	cos(std::cos(v0 * pi / 180)),
	sin(std::sin(v0 * pi / 180)),
	inc(i0),
	defaultVal(v0)
{}
Angle::Angle(float x0, float y0, float v0, float i0) :
	x(x0),
	y(y0),
	value(v0),
	cos(std::cos(v0* pi / 180)),
	sin(std::sin(v0* pi / 180)),
	inc(i0),
	defaultVal(v0)
{}

void Angle::Inc(float side)//side == 1 or -1; -1 to left, 1 to right
{
	if (value >= 360 + defaultVal) {
		value -= 360;
	}
	if (value <= defaultVal) {
		value += 360;
	}
	value += inc * side;
	cos = std::cos(value * pi / 180);
	sin = std::sin(value * pi / 180);
}
float Angle::GetVal() const
{
	return value;
}
float Angle::GetCos() const
{
	return cos;
}
float Angle::GetSin() const
{
	return sin;
}
void Angle::SetValue(float n){
	value = n;
	cos = std::cos(value * pi / 180);
	sin = std::sin(value * pi / 180);
}
