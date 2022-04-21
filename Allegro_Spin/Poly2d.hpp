#pragma once
#include <vector>
#include <utility>
#include "AllegroBase.hpp"

class Poly2d
{
public:
	ALLEGRO_COLOR color;
	float thickness;
	std::vector<float>Polygon;
	Poly2d();
	Poly2d(float t0);
	Poly2d(float t0, ALLEGRO_COLOR col);
	Poly2d(std::vector<float> poly, float t0, ALLEGRO_COLOR col);
	void Draw() const;
};