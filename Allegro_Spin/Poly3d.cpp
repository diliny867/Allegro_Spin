#include "Poly3d.hpp"

Poly3d::Poly3d(double x0, double y0, double h0, double w0, double e1ry0, double e2rx0,  double n):
	defaultHeight(h0),
	x(x0),
	y(y0),
	height(h0),
	width(w0),
	ellipse(w0 / 2, e1ry0, n),
	ellipse2(e2rx0, h0 / n, n)
{
}

Poly3d::Poly3d(double x0, double y0, double h0, double w0, double e1ry0, double e2rx0, double n, double e1i0, double e2i0) :
	defaultHeight(h0),
	x(x0),
	y(y0),
	height(h0),
	width(w0),
	ellipse(w0/2, e1ry0, n, e1i0),
	ellipse2(e2rx0, h0 / 2, n, e2i0)
{
}
void Poly3d::Scale(double n)
{
	height = defaultHeight * (1 + (n / 100));
	ellipse.side_x = ellipse.GetRx() * (1 + (n / 100));
	ellipse.side_y = ellipse.GetRy() * (1 + (n / 100));
}
/*
void Poly3d::SetX(double n){
	x = n;
}
void Poly3d::SetY(double n){
	y = n;
}
void Poly3d::IncX(double n){
	x += n;
}
void Poly3d::IncY(double n){
	y += n;
}
double Poly3d::GetX() const{
	return x;
}
double Poly3d::GetY() const{
	return y;
}

*/
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

	Poly2ds[0] = (PolygonFactory::NewPolygon4Points(ax + x, ay + y, bx + x, by + y, bx + x, -1 * by + y + height, ax + x, -1 * ay + y + height, 3, al_map_rgb(255, 0, 0)));//front
	Poly2ds[1] = (PolygonFactory::NewPolygon4Points(cx + x, cy + y, dx + x, dy + y, dx + x, -1 * dy + y + height, cx + x, -1 * cy + y + height, 3, al_map_rgb(255, 0, 0)));//back
	Poly2ds[2] = (PolygonFactory::NewPolygon4Points(ax + x, ay + y, bx + x, by + y, cx + x, cy + y, dx + x, dy + y, 3, al_map_rgb(255, 0, 0)));//top
	Poly2ds[3] = (PolygonFactory::NewPolygon4Points(ax + x, -1 * ay + y + height, bx + x, -1 * by + y + height, cx + x, -1 * cy + y + height, dx + x, -1 * dy + y + height, 3, al_map_rgb(255, 0, 0)));//bottom


	/* attempt to add spinning on y axis
	for (int i = 0; i < ellipse.angles.size(); i++) {
		ellipse2.angles[i].x = ellipse2.side_x * ellipse2.angles[i].GetCos() * (1 - ellipse2.angles[i].GetCos() / 10);
		ellipse2.angles[i].y = ellipse2.side_y * ellipse2.angles[i].GetSin() * (1 - ellipse2.angles[i].GetCos() / 10);
	}

	//some old code from AllegroApp
	al_draw_pixel(ellipse2.angles[0].x + 200, ellipse2.angles[0].y + 100, al_map_rgb(255, 255, 255));
	al_draw_pixel(ellipse2.angles[1].x + 200, ellipse2.angles[1].y + 100, al_map_rgb(255, 255, 255));
	al_draw_pixel(ellipse2.angles[2].x + 200, ellipse2.angles[2].y + 100, al_map_rgb(255, 255, 255));
	al_draw_pixel(ellipse2.angles[3].x + 200, ellipse2.angles[3].y + 100, al_map_rgb(255, 255, 255));
	
	const double ax2 = ellipse2.angles[0].x;
	const double ay2 = ellipse2.angles[0].y;
	const double bx2 = ellipse2.angles[1].x;
	const double by2 = ellipse2.angles[1].y;
	const double cx2 = ellipse2.angles[2].x;
	const double cy2 = ellipse2.angles[2].y;
	const double dx2 = ellipse2.angles[3].x;
	const double dy2 = ellipse2.angles[3].y;
	Poly2ds[0] = (PolygonFactory::NewPolygon4Points(x + cx2,y + cy2 * -1, x + dx2, y + dy2 * -1,x + ax2,y + height + ay2,x + bx2,y + height + by2, 3, al_map_rgb(255, 0, 0)));//front
	Poly2ds[1] = (PolygonFactory::NewPolygon4Points(x + cx2,y + cy2,  x + dx2, y + dy2, x + ax2,y + height + ay2 * -1,x + bx2, y + height + by2 * -1, 3, al_map_rgb(255, 0, 0)));//back
	Poly2ds[2] = (PolygonFactory::NewPolygon4Points(x + cx2,y + cy2 * -1,x + dx2,y + dy2 * -1,x + cx2,y + cy2,x + dx2,y + dy2, 3, al_map_rgb(255, 0, 0)));//top
	Poly2ds[3] = (PolygonFactory::NewPolygon4Points(x + bx2,y + height + by2,x + ax2,y + height + ay2,x + bx2,y + height + by2 * -1,x + ax2,y + height + ay2 * -1, 3, al_map_rgb(255, 0, 0)));//bottom
	
	Poly2ds[0] = (PolygonFactory::NewPolygon4Points(ax + x + cx2, ay + y + cy2*-1, bx + x + dx2, by + y + dy2 * -1, bx + x + ax2, -1 * by + y+height+ay2, ax + x+bx2, -1 * ay + y + height + by2, 3, al_map_rgb(255, 0, 0)));//front
	Poly2ds[1] = (PolygonFactory::NewPolygon4Points(cx + x + cx2, cy + y + cy2, dx + x +dx2, dy + y + dy2, dx + x+ax2, -1 * dy + y + height+ay2*-1, cx + x + bx2, -1 * cy + y + height+by2*-1, 3, al_map_rgb(255, 0, 0)));//back
	Poly2ds[2] = (PolygonFactory::NewPolygon4Points(ax + x + cx2, ay + y + cy2 * -1, bx + x + dx2, by + y + dy2 * -1, cx + x+cx2, cy + y+cy2, dx + x+dx2, dy + y + dy2, 3, al_map_rgb(255, 0, 0)));//top
	Poly2ds[3] = (PolygonFactory::NewPolygon4Points(ax + x+bx2, -1 * ay + y + height + by2, bx + x+ax2, -1 * by + y + height + ay2, cx + x+bx2, -1 * cy + y + height + by2*-1, dx + x+ax2, -1 * dy + y + height + ay2*-1, 3, al_map_rgb(255, 0, 0)));//bottom
	*/
}

void Poly3d::Draw()
{
	for (int i = 0; i < Poly2ds.size(); i++)
	{
		Poly2ds[i].Draw();
	}
}