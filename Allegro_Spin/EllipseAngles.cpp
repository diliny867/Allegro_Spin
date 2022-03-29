#include "EllipseAngles.hpp"
EllipseAngles::EllipseAngles(double rx0, double ry0, double n):
	rx(rx0),
	ry(ry0)
{
	for(int i=0;i<n;i++)
	{
		angles.push_back(*new Angle((360/n)*(i+1)));
	}
}
EllipseAngles::EllipseAngles(double rx0, double ry0, double n, double i0):
	rx(rx0),
	ry(ry0)
{
	for (int i = 0; i < n; i++)
	{
		angles.push_back(*new Angle((360 / n) * (i + 1),i0));
	}
}
void EllipseAngles::IncAll(double side)
{
	for(int i=0;i<angles.size();i++)
	{
		angles[i].Inc(side);
	}
}
double EllipseAngles::GetRx() const
{
	return rx;
}
double EllipseAngles::GetRy() const
{
	return ry;
}
void EllipseAngles::SetRx(double n)
{
	rx = n;
}
void EllipseAngles::SetRy(double n)
{
	ry = n;
}

