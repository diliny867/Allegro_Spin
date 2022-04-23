#pragma once
#include "PolygonFactory.hpp"
#include "EllipseAngles.hpp"
#include <iostream>
class Poly3d
{
private:
	const float defaultHeight;
	const float defaultWidth;
	const float pi = 3.14159265;
	void FillPolys();
	void FillPolys2();
	void DrawTestE2() const;
public:
	float x;
	float y;
	float height;
	float width;
	const int pointCount;
	bool drctn;
	EllipseAngles ellipse;
	EllipseAngles ellipse2;
	std::vector<Poly2d>Poly2ds;
	Poly3d(float x0, float y0, float h0, float w0, float e1ry0, float e2rx0, float n);
	Poly3d(float x0, float y0, float h0, float w0, float e1ry0, float e2rx0, float n, float e1i0, float e2i0, bool d0);
	void Scale(float n);
	/*
	void SetX(float n);
	void SetY(float n);
	void IncX(float n);
	void IncY(float n);
	float GetX() const;
	float GetY() const;
	*/
	Poly3d& operator=(Poly3d other) noexcept;//TODO: overload = operator
	void Move();
	void Draw() const;
};
