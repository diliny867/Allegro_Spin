#pragma once

//namespace AllegroBase;

#ifndef ALLEGROBASE_HPP_INCLUDED
#define ALLEGROBASE_HPP_INCLUDED

#include <iostream>
#include "windows.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_windows.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const int FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

class AllegroBase
{
public:
    AllegroBase();
    virtual ~AllegroBase();

    virtual bool Init( int screenWidth, int screenHeight, int fps );
    virtual void Destroy();
    virtual void Run();
    virtual void Exit();

    // See help for ALLEGRO_KEYBOARD_STATE
    bool IsPressed( int keycode );

    void FocusGraphicWin();//focuses on this window

    virtual void Fps() = 0;
    virtual void Draw() = 0;
    virtual void OnKeyDown( const ALLEGRO_KEYBOARD_EVENT &keyboard ) {};
    virtual void OnKeyUp( const ALLEGRO_KEYBOARD_EVENT &keyboard ) {};

protected:
    ALLEGRO_DISPLAY *alDisplay_;
    ALLEGRO_EVENT_QUEUE *alEventQueue_;
    ALLEGRO_TIMER *alTimer_;
    bool pressedKeys_[ALLEGRO_KEY_MAX];

public: //if private, appears error, which says, this field is inaccessible, so changed to public
    bool exit_;
};

#endif