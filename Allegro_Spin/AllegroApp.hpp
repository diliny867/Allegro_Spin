#include "AllegroBase.hpp"
#include "PolygonFactory.hpp"
#include "Angle.hpp"
#include "EllipseAngles.hpp"
#include "Poly2d.hpp"
#include "Poly3d.hpp"
#include <cmath>
#include <iostream>
#include <vector>

#pragma once
class AllegroApp :public AllegroBase{
private:
    bool inFunc;
public:
	std::vector<Poly3d>poly3ds;
    int p3dsSize;//need to change it every time, we add/remove figure. can remove it and use poly3ds.size() everywhere, but i dont want to
    AllegroApp();
    void AddFigure();
    void RemoveFigure();
    void EditFigure();
    virtual void Run();
    virtual void Fps();
    virtual void Draw();

    virtual void OnKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard);
};