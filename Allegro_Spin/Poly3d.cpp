#include "Poly3d.hpp"

#define NewPoly PolygonFactory::NewPolygon(std::vector<float>

Poly3d::Poly3d(float x0, float y0, float h0, float w0, float e1ry0, float e2rx0,  float n):
	defaultHeight(h0),
	x(x0),
	y(y0),
	height(h0),
	width(w0),
	ellipse(w0 / 2, e1ry0, n),
	ellipse2(e2rx0, h0 / n, n)
{
}

Poly3d::Poly3d(float x0, float y0, float h0, float w0, float e1ry0, float e2rx0, float n, float e1i0, float e2i0) :
	defaultHeight(h0),
	x(x0),
	y(y0),
	height(h0),
	width(w0),
	ellipse(w0/2, e1ry0, n, e1i0),
	ellipse2(e2rx0, h0 / 2, n, e2i0)
{
}
void Poly3d::Scale(float n)
{
	height = defaultHeight * (1 + (n / 100));
	ellipse.side_x = ellipse.GetRx() * (1 + (n / 100));
	ellipse.side_y = ellipse.GetRy() * (1 + (n / 100));
}
/*
void Poly3d::SetX(float n){
	x = n;
}
void Poly3d::SetY(float n){
	y = n;
}
void Poly3d::IncX(float n){
	x += n;
}
void Poly3d::IncY(float n){
	y += n;
}
float Poly3d::GetX() const{
	return x;
}
float Poly3d::GetY() const{
	return y;
}

*/
void Poly3d::Move()
{

	//calculate new point positions
	//*(1 - ellipse.angles[i].GetSin() / 10) to add perspective
	for (int i = 0; i < ellipse.angles.size();i++) {
		ellipse.angles[i].x = ellipse.side_x * ellipse.angles[i].GetCos() * (1 - ellipse.angles[i].GetSin() / 10);
		ellipse.angles[i].y = ellipse.side_y * ellipse.angles[i].GetSin() * (1 - ellipse.angles[i].GetSin() / 10);
	}

	const float ax = ellipse.angles[0].x;
	const float ay = ellipse.angles[0].y;
	const float bx = ellipse.angles[1].x;
	const float by = ellipse.angles[1].y;
	const float cx = ellipse.angles[2].x;
	const float cy = ellipse.angles[2].y;
	const float dx = ellipse.angles[3].x;
	const float dy = ellipse.angles[3].y;

	

	Poly2ds[0] = (NewPoly{ax + x, ay + y, bx + x, by + y, bx + x, -by + y + height, ax + x, -ay + y + height}, 3, al_map_rgb(255, 0, 0)));//front
	Poly2ds[1] = (NewPoly{cx + x, cy + y, dx + x, dy + y, dx + x, -dy + y + height, cx + x, -cy + y + height}, 3, al_map_rgb(255, 0, 0)));//back
	Poly2ds[2] = (NewPoly{ax + x, ay + y, bx + x, by + y, cx + x, cy + y, dx + x, dy + y}, 3, al_map_rgb(255, 0, 0)));//top
	Poly2ds[3] = (NewPoly{ax + x, -ay + y + height, bx + x, -by + y + height, cx + x, -cy + y + height, dx + x, -dy + y + height}, 3, al_map_rgb(255, 0, 0)));//bottom



	/*
	Poly2ds[0] = (PolygonFactory::NewPolygon4Points(ax + x, ay + y, bx + x, by + y, bx + x, -1 * by + y + height, ax + x, -1 * ay + y + height, 3, al_map_rgb(255, 0, 0)));//front
	Poly2ds[1] = (PolygonFactory::NewPolygon4Points(cx + x, cy + y, dx + x, dy + y, dx + x, -1 * dy + y + height, cx + x, -1 * cy + y + height, 3, al_map_rgb(255, 0, 0)));//back
	Poly2ds[2] = (PolygonFactory::NewPolygon4Points(ax + x, ay + y, bx + x, by + y, cx + x, cy + y, dx + x, dy + y, 3, al_map_rgb(255, 0, 0)));//top
	Poly2ds[3] = (PolygonFactory::NewPolygon4Points(ax + x, -1 * ay + y + height, bx + x, -1 * by + y + height, cx + x, -1 * cy + y + height, dx + x, -1 * dy + y + height, 3, al_map_rgb(255, 0, 0)));//bottom
	*/

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
	
	const float ax2 = ellipse2.angles[0].x;
	const float ay2 = ellipse2.angles[0].y;
	const float bx2 = ellipse2.angles[1].x;
	const float by2 = ellipse2.angles[1].y;
	const float cx2 = ellipse2.angles[2].x;
	const float cy2 = ellipse2.angles[2].y;
	const float dx2 = ellipse2.angles[3].x;
	const float dy2 = ellipse2.angles[3].y;
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