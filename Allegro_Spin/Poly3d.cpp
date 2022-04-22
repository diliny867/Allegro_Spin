#include "Poly3d.hpp"

#define NewPoly PolygonFactory::NewPolygon

Poly3d::Poly3d(float x0, float y0, float h0, float w0, float e1ry0, float e2rx0,  float n):
	defaultHeight(h0),
	defaultWidth(w0),
	drctn(false),
	x(x0),
	y(y0),
	height(h0),
	width(w0),
	pointCount(n),
	ellipse(w0 / 2, e1ry0, n),
	ellipse2(e2rx0, h0 / 2, n)
{
}

Poly3d::Poly3d(float x0, float y0, float h0, float w0, float e1ry0, float e2rx0, float n, float e1i0, float e2i0, bool d0) :
	defaultHeight(h0),
	defaultWidth(w0),
	drctn(d0),
	x(x0),
	y(y0),
	height(h0),
	width(w0),
	pointCount(n),
	ellipse(w0 / 2, e1ry0, n, e1i0),
	ellipse2(e2rx0, h0 / 2, n, e2i0)
{
}
void Poly3d::Scale(float n)
{
	height = defaultHeight * (1 + (n / 100));
	width = defaultWidth * (1 + (n / 100));
	ellipse.side_x = ellipse.GetRx() * (1 + (n / 100));
	ellipse.side_y = ellipse.GetRy() * (1 + (n / 100));
	ellipse2.side_x = ellipse2.GetRx() * (1 + (n / 100));
	ellipse2.side_y = ellipse2.GetRy() * (1 + (n / 100));
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
	for (int i = 0; i < ellipse.angles.size();i++) {
		ellipse.angles[i].x = ellipse.side_x * ellipse.angles[i].GetCos() * (1 - ellipse.angles[i].GetSin() / 10);
		ellipse.angles[i].y = ellipse.side_y * ellipse.angles[i].GetSin() * (1 - ellipse.angles[i].GetSin() / 10);
	}

	for (int i = 0; i < ellipse.angles.size(); i++) {
		ellipse2.angles[i].x = ellipse2.side_x * ellipse2.angles[i].GetCos() * (1 - ellipse2.angles[i].GetCos() / 10);
		ellipse2.angles[i].y = ellipse2.side_y * ellipse2.angles[i].GetSin() * (1 - ellipse2.angles[i].GetCos() / 10);
	}

	if (drctn) {
		FillPolys2();
	}else {
		FillPolys();
	}

	/*
	Poly2ds[0] = (PolygonFactory::NewPolygon4Points(ax + x, ay + y, bx + x, by + y, bx + x, -1 * by + y + height, ax + x, -1 * ay + y + height, 3, al_map_rgb(255, 0, 0)));//front
	Poly2ds[1] = (PolygonFactory::NewPolygon4Points(cx + x, cy + y, dx + x, dy + y, dx + x, -1 * dy + y + height, cx + x, -1 * cy + y + height, 3, al_map_rgb(255, 0, 0)));//back
	Poly2ds[2] = (PolygonFactory::NewPolygon4Points(ax + x, ay + y, bx + x, by + y, cx + x, cy + y, dx + x, dy + y, 3, al_map_rgb(255, 0, 0)));//top
	Poly2ds[3] = (PolygonFactory::NewPolygon4Points(ax + x, -1 * ay + y + height, bx + x, -1 * by + y + height, cx + x, -1 * cy + y + height, dx + x, -1 * dy + y + height, 3, al_map_rgb(255, 0, 0)));//bottom
	*/

	/* old attempt to add spinning on y axis
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
void Poly3d::DrawTestE2() const
{
	float dx = 400;
	for (int i = 0; i < ellipse2.angles.size(); i++) {
		if (i == 0)
		{
			al_draw_pixel(ellipse2.angles[i].x + dx, ellipse2.angles[i].y + 100, al_map_rgb(0, 0, 255));
		}
		else if (i == 1)
		{
			al_draw_pixel(ellipse2.angles[i].x + dx, ellipse2.angles[i].y + 100, al_map_rgb(0, 255, 0));
		}
		else if (i == 2)
		{
			al_draw_pixel(ellipse2.angles[i].x + dx, ellipse2.angles[i].y + 100, al_map_rgb(255, 0, 0));
		}
		else {
			al_draw_pixel(ellipse2.angles[i].x + dx, ellipse2.angles[i].y + 100, al_map_rgb(255, 255, 255));
		}
	}
	for (int i = 0; i < ellipse2.angles.size(); i++) {
		if (i == 0)
		{
			al_draw_pixel(-ellipse2.angles[i].x + dx + width, ellipse2.angles[i].y + 100, al_map_rgb(0, 0, 255));
		}
		else if(i==1)
		{
			al_draw_pixel(-ellipse2.angles[i].x + dx + width, ellipse2.angles[i].y + 100, al_map_rgb(0, 255, 0));
		}
		else if (i == 2)
		{
			al_draw_pixel(-ellipse2.angles[i].x + dx + width, ellipse2.angles[i].y + 100, al_map_rgb(255, 0, 0));
		}
		else {
			al_draw_pixel(-ellipse2.angles[i].x + dx + width, ellipse2.angles[i].y + 100, al_map_rgb(255, 255, 255));
		}
	}
	/*this will crash if point count is too low
	al_draw_pixel(ellipse2.angles[0].x + dx, ellipse2.angles[0].y + 100, al_map_rgb(0, 0, 255));
	al_draw_pixel(ellipse2.angles[1].x + dx, ellipse2.angles[1].y + 100, al_map_rgb(0, 255, 0));
	al_draw_pixel(ellipse2.angles[2].x + dx, ellipse2.angles[2].y + 100, al_map_rgb(255, 0, 0));
	for (int i = 3; i < ellipse2.angles.size(); i++) {

		al_draw_pixel(ellipse2.angles[i].x + dx, ellipse2.angles[i].y + 100, al_map_rgb(255, 255, 255));
	}
	al_draw_pixel(-ellipse2.angles[0].x + dx + width, ellipse2.angles[0].y + 100, al_map_rgb(0, 0, 255));
	al_draw_pixel(-ellipse2.angles[1].x + dx + width, ellipse2.angles[1].y + 100, al_map_rgb(0, 255, 0));
	al_draw_pixel(-ellipse2.angles[2].x + dx + width, ellipse2.angles[2].y + 100, al_map_rgb(255, 0, 0));
	for (int i = 3; i < ellipse2.angles.size(); i++) {
		al_draw_pixel(-ellipse2.angles[i].x + dx + width, ellipse2.angles[i].y + 100, al_map_rgb(255, 255, 255));
	}
	*/
}
void Poly3d::FillPolys2()
{
	std::vector<float>polygon(pointCount * 2);
	for (int i = 0; i < pointCount; i++) {
		polygon[i * 2] = ellipse2.angles[i].x + x;
		polygon[i * 2 + 1] = ellipse2.angles[i].y + y;
	}
	Poly2ds[0] = (NewPoly(polygon, Poly2ds[0].thickness, al_map_rgb(255, 0, 0)));//left
	for (int i = 0; i < pointCount; i++) {
		polygon[i * 2] = -ellipse2.angles[i].x + x+width;
	}
	Poly2ds[Poly2ds.size() - 1] = (NewPoly(polygon, Poly2ds[Poly2ds.size() - 1].thickness, al_map_rgb(255, 0, 0)));//right
	
	//middle
	polygon.resize(8);
	for (int j = 0; j < (pointCount + 1) / 2; j++) {
		polygon[0] = ellipse2.angles[j * 2 < pointCount ? j * 2 : j * 2 - pointCount].x + x;
		polygon[1] = ellipse2.angles[j * 2 < pointCount ? j * 2 : j * 2 - pointCount].y + y;
		polygon[2] = ellipse2.angles[j * 2 + 1 < pointCount ? j * 2 + 1 : j * 2 + 1 - pointCount].x + x;
		polygon[3] = ellipse2.angles[j * 2 + 1 < pointCount ? j * 2 + 1 : j * 2 + 1 - pointCount].y + y;
		polygon[4] = -ellipse2.angles[j * 2 + 1 < pointCount ? j * 2 + 1 : j * 2 + 1 - pointCount].x + x+width;
		polygon[5] = ellipse2.angles[j * 2 + 1 < pointCount ? j * 2 + 1 : j * 2 + 1 - pointCount].y + y;
		polygon[6] = -ellipse2.angles[j * 2 < pointCount ? j * 2 : j * 2 - pointCount].x + x + width;
		polygon[7] = ellipse2.angles[j * 2 < pointCount ? j * 2 : j * 2 - pointCount].y + y;
		Poly2ds[j + 1] = (NewPoly(polygon, Poly2ds[j + 1].thickness, al_map_rgb(255, 0, 0)));//middle
	}
	
}
void Poly3d::FillPolys()
{
	std::vector<float>polygon(pointCount *2);
	for (int i = 0; i < pointCount;i++) {
		polygon[i*2]=ellipse.angles[i].x+x;
		polygon[i*2+1]=ellipse.angles[i].y+y;
	}
	Poly2ds[0] = (NewPoly(polygon, Poly2ds[0].thickness, al_map_rgb(255, 0, 0)));//top
	for (int i = 0; i < pointCount; i++) {
		polygon[i * 2 + 1] = -ellipse.angles[i].y + y + height;
	}
	Poly2ds[Poly2ds.size() - 1] = (NewPoly(polygon, Poly2ds[Poly2ds.size() - 1].thickness, al_map_rgb(255, 0, 0)));//bottom
	//middle
	polygon.resize(8);
	for (int j = 0; j < (pointCount +1) / 2;j++) {
		polygon[0] = ellipse.angles[j * 2 <		pointCount ? j*2	: j*2-pointCount].x + x;
		polygon[1] = ellipse.angles[j * 2 <		pointCount ? j*2	: j*2-pointCount].y + y;
		polygon[2] = ellipse.angles[j * 2 + 1 < pointCount ? j*2+1	: j*2+1-pointCount].x + x;
		polygon[3] = ellipse.angles[j * 2 + 1 < pointCount ? j*2+1	: j*2+1-pointCount].y + y;
		polygon[4] = ellipse.angles[j * 2 + 1 < pointCount ? j*2+1	: j*2+1-pointCount].x + x;
		polygon[5] = -ellipse.angles[j* 2 + 1 < pointCount ? j*2+1	: j*2+1-pointCount].y + y + height;
		polygon[6] = ellipse.angles[j * 2 <		pointCount ? j*2	: j*2-pointCount].x + x;
		polygon[7] = -ellipse.angles[j * 2 <	pointCount ? j*2	: j*2-pointCount].y + y + height;
		Poly2ds[j+1] = (NewPoly(polygon, Poly2ds[j+1].thickness, al_map_rgb(255, 0, 0)));//middle
	}

	//al_draw_pixel(ellipse.angles[0].x + x, ellipse.angles[0].y + y-30, al_map_rgb(255, 255, 255));
	/*
	Poly2ds[0] = (NewPoly(std::vector<float>{ ax + x, ay + y, bx + x, by + y, bx + x, -by + y + height, ax + x, -ay + y + height }, 3, al_map_rgb(255, 0, 0)));//front
	Poly2ds[1] = (NewPoly(std::vector<float>{ cx + x, cy + y, dx + x, dy + y, dx + x, -dy + y + height, cx + x, -cy + y + height }, 3, al_map_rgb(255, 0, 0)));//back
	Poly2ds[2] = (NewPoly(std::vector<float>{ ax + x, ay + y, bx + x, by + y, cx + x, cy + y, dx + x, dy + y }, 3, al_map_rgb(255, 0, 0)));//top
	Poly2ds[3] = (NewPoly(std::vector<float>{ ax + x, -ay + y + height, bx + x, -by + y + height, cx + x, -cy + y + height, dx + x, -dy + y + height }, 3, al_map_rgb(255, 0, 0)));//bottom
	*/
}
void Poly3d::Draw() const
{
	//al_draw_line(x-width/2,y-ellipse.GetRy()-10,x+width/2,y-ellipse.GetRy()-10,al_map_rgb(255,255,255),3);
	//al_draw_line(x-width/2-10,y,x-width/2-10,y+height, al_map_rgb(255, 255, 255), 3);
	for (int i = 0; i < Poly2ds.size(); i++)
	{
		Poly2ds[i].Draw();
	}
}
