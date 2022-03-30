#pragma once
#include "PolygonFactory.hpp"
#include "EllipseAngles.hpp"
#include <iostream>
class Poly3d
{
private:
	double defaultHeight;
	const double pi = 3.14159265;
public:
	double x;
	double y;
	double height;
	double width;
	EllipseAngles ellipse;
	EllipseAngles ellipse2;
	std::vector<Poly2d>Poly2ds;
	Poly3d(double x0, double y0, double h0, double w0, double e1ry0, double e2rx0, double n);
	Poly3d(double x0, double y0, double h0, double w0, double e1ry0, double e2rx0, double n, double e1i0, double e2i0);
	void Scale(double n);
	/*
	void SetX(double n);
	void SetY(double n);
	void IncX(double n);
	void IncY(double n);
	double GetX() const;
	double GetY() const;
	*/
	void Move();
	void Draw();
};