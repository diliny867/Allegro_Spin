#pragma once
#include <vector>
#include "Poly2d.hpp"
class PolygonFactory {
public:
    static Poly2d NewPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int t0, ALLEGRO_COLOR col);
};