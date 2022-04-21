#pragma once
#include <vector>
#include <utility>
#include "Poly2d.hpp"
class PolygonFactory {
public:
    static Poly2d NewPolygon4Points(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float t0, ALLEGRO_COLOR col);
    static Poly2d NewPolygon(std::vector<float> poly0, float t0, ALLEGRO_COLOR col);
};