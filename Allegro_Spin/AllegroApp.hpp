#include "AllegroBase.hpp"
#include "PolygonFactory.hpp"
#include "Angle.hpp"
#include "EllipseAngles.hpp"
#include <cmath>
#include <iostream>
#include <vector>

#pragma once
class AllegroApp :public AllegroBase{
public:
    AllegroApp();
    virtual void Fps();
    virtual void Draw();
    virtual void Run();

    virtual void OnKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard);
};