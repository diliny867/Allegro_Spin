#include "EllipseAngles.hpp"
EllipseAngles::EllipseAngles(float rx0, float ry0, float n):
	rx(rx0),
	ry(ry0),
	side_x(rx0),
	side_y(ry0)
{
	for(int i=0;i<n;i++)
	{
		angles.push_back(*new Angle((360/n)*(i)));
	}
}
EllipseAngles::EllipseAngles(float rx0, float ry0, float n, float i0):
	rx(rx0),
	ry(ry0),
	side_x(rx0),
	side_y(ry0)
{
	for (int i = 0; i < n; i++)
	{
		angles.push_back(*new Angle((360 / n) * (i),i0));
	}
}
void EllipseAngles::IncAll(float d)
{
	for(int i=0;i<angles.size();i++)
	{
		angles[i].Inc(d);
	}
}
float EllipseAngles::GetRx() const
{
	return rx;
}
float EllipseAngles::GetRy() const
{
	return ry;
}
void EllipseAngles::SetRx(float n)
{
	rx = n;
}
void EllipseAngles::SetRy(float n)
{
	ry = n;
}

