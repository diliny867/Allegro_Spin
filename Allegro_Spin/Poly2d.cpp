#include "Poly2d.hpp"

Poly2d::Poly2d():
	color(al_map_rgb(255,255,255)),
	thickness(0)
{
}
Poly2d::Poly2d(std::vector<float> poly, int t0, ALLEGRO_COLOR col):
	color(col),
	thickness(t0),
	Polygon(std::move(poly))
{
}

void Poly2d::Draw()
{
	al_draw_polygon(Polygon.data(), Polygon.size()/2, ALLEGRO_LINE_JOIN_BEVEL, color, thickness, 1);
}

