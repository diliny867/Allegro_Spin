#pragma once
#include "PolygonFactory.hpp"
#include "EllipseAngles.hpp"
#include <iostream>
class Poly3d
{
private:
	float defaultHeight;
	const float pi = 3.14159265;
	void FillPolys();
public:
	float x;
	float y;
	float height;
	float width;
	EllipseAngles ellipse;
	EllipseAngles ellipse2;
	std::vector<Poly2d>Poly2ds;
	Poly3d(float x0, float y0, float h0, float w0, float e1ry0, float e2rx0, float n);
	Poly3d(float x0, float y0, float h0, float w0, float e1ry0, float e2rx0, float n, float e1i0, float e2i0);
	void Scale(float n);
	/*
	void SetX(float n);
	void SetY(float n);
	void IncX(float n);
	void IncY(float n);
	float GetX() const;
	float GetY() const;
	*/
	void Move();
	void Draw();
};