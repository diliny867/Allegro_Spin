#pragma once
#include <vector>
#include <utility>
#include "AllegroBase.hpp"

class Poly2d
{
public:
	ALLEGRO_COLOR color;
	int thickness;
	std::vector<float>Polygon;
	Poly2d();
	Poly2d(std::vector<float> poly,int t0,  ALLEGRO_COLOR col);
	void Draw();
};