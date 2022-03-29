#pragma once
#include "Angle.hpp"
#include <vector>
class EllipseAngles
{
private:
	double rx;
	double ry;
public:
	std::vector<Angle>angles;
	double side_x;
	double side_y;
	EllipseAngles(double rx0, double ry0, double n);
	EllipseAngles(double rx0, double ry0, double n, double i0);
	void IncAll(double side);
	double GetRx() const;
	double GetRy() const;
	void SetRx(double n);
	void SetRy(double n);
};