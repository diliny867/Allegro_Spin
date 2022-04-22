#pragma once
#include "Angle.hpp"
#include <vector>
class EllipseAngles
{
private:
	float rx;
	float ry;
public:
	std::vector<Angle>angles;
	float side_x;
	float side_y;
	EllipseAngles(float rx0, float ry0, float n);
	EllipseAngles(float rx0, float ry0, float n, float i0);
	void IncAll(float d);
	void SetInc(float inc);
	float GetRx() const;
	float GetRy() const;
	void SetRx(float n);
	void SetRy(float n);
};