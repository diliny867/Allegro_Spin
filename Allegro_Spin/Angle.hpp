#pragma once
#include <cmath>
class Angle
{
private:
	const double pi = 3.14159265;
	double defaultVal;
	double value;
	double cos;
	double sin;
	
public:
	double inc;
	double x;
	double y;
	Angle();
	Angle(double v0);
	Angle(double v0, double i0);
	Angle(double x0, double y0, double v0, double i0);
	void Inc(double side);
	double GetVal() const;
	double GetCos() const;
	double GetSin() const;
	void SetValue(double n);
};