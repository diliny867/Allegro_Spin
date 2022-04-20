#include "PolygonFactory.hpp"

Poly2d PolygonFactory::NewPolygon4Points(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int t0, ALLEGRO_COLOR col) {
    return *new Poly2d(std::vector<float>{x1, y1, x2, y2, x3, y3, x4, y4}, t0, col);
}
Poly2d PolygonFactory::NewPolygon(std::vector<float> poly0, int t0, ALLEGRO_COLOR col)
{
    return *new Poly2d(poly0, t0, col);
}