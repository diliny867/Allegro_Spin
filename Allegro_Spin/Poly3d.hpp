#pragma once
#include "PolygonFactory.hpp"
#include "EllipseAngles.hpp"
#include <iostream>
class Poly3d
{
private:
	double defaultHeight;
public:
	double x;
	double y;
	double height;
	double width;
	EllipseAngles ellipse;
	std::vector<Poly2d>Poly2ds;
	Poly3d(double x0, double y0, double h0, double w0, double ry0, double n);
	Poly3d(double x0, double y0, double h0, double w0, double ry0, double n, double i0);
	void Scale(double n);
	void Move();
	void Draw();
};