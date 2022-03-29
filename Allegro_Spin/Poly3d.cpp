#include "Poly3d.hpp"

Poly3d::Poly3d(double x0, double y0, double h0, double w0, double ry0, double n):
	x(x0),
	y(y0),
	height(h0),
	width(w0),
	ellipse(w0/2,ry0,n),
	defaultHeight(h0)
{
}

Poly3d::Poly3d(double x0, double y0, double h0, double w0, double ry0, double n, double i0) :
	x(x0),
	y(y0),
	height(h0),
	width(w0),
	ellipse(w0/2, ry0, n, i0),
	defaultHeight(h0)
{
}
void Poly3d::Scale(double n)
{
	height = defaultHeight * (1 + (n / 100));
	ellipse.side_x = ellipse.GetRx() * (1 + (n / 100));
	ellipse.side_y = ellipse.GetRy() * (1 + (n / 100));
}

void Poly3d::Move()
{
	//*(1 - ellipse.angles[i].GetSin() / 10) to add perspective

	for (int i = 0; i < ellipse.angles.size();i++) {
		ellipse.angles[i].x = ellipse.side_x * ellipse.angles[i].GetCos() * (1 - ellipse.angles[i].GetSin() / 10);
		ellipse.angles[i].y = ellipse.side_y * ellipse.angles[i].GetSin() * (1 - ellipse.angles[i].GetSin() / 10);
	}

	const double ax = ellipse.angles[0].x;
	const double ay = ellipse.angles[0].y;
	const double bx = ellipse.angles[1].x;
	const double by = ellipse.angles[1].y;
	const double cx = ellipse.angles[2].x;
	const double cy = ellipse.angles[2].y;
	const double dx = ellipse.angles[3].x;
	const double dy = ellipse.angles[3].y;

	//currently only cubes work
	Poly2ds[0] = (PolygonFactory::NewPolygon(ax + x, ay + x, bx + x, by + x, bx + x, -1 * by + y+height, ax + x, -1 * ay + y + height, 3, al_map_rgb(255, 0, 0)));//front
	Poly2ds[1] = (PolygonFactory::NewPolygon(cx + x, cy + x, dx + x, dy + x, dx + x, -1 * dy + y + height, cx + x, -1 * cy + y + height, 3, al_map_rgb(255, 0, 0)));//back
	Poly2ds[2] = (PolygonFactory::NewPolygon(ax + x, ay + x, bx + x, by + x, cx + x, cy + x, dx + x, dy + x, 3, al_map_rgb(255, 0, 0)));//top
	Poly2ds[3] = (PolygonFactory::NewPolygon(ax + x, -1 * ay + y + height, bx + x, -1 * by + y + height, cx + x, -1 * cy + y + height, dx + x, -1 * dy + y + height, 3, al_map_rgb(255, 0, 0)));//bottom
}

void Poly3d::Draw()
{
	for (int i = 0; i < Poly2ds.size(); i++)
	{
		Poly2ds[i].Draw();
	}
}