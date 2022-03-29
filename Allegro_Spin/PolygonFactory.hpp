#pragma once
#include <vector>
class PolygonFactory {
public:
    static std::vector<float> NewPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
};