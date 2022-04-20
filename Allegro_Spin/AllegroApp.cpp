#include "AllegroApp.hpp"
using namespace std;
AllegroApp::AllegroApp(){}

const float pi = 3.14159265;

float delta = 1;


void AllegroApp::OnKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard) {
    if (keyboard.keycode == ALLEGRO_KEY_LEFT || keyboard.keycode == ALLEGRO_KEY_A) {
        //cube.ellipse.IncAll(-1);
    }else if (keyboard.keycode == ALLEGRO_KEY_RIGHT || keyboard.keycode == ALLEGRO_KEY_D) {
        //cube.ellipse.IncAll(1);
    }
}


void AllegroApp::Run() {

    Poly3d cube(200, 200, 80, 120, 10, 10, 4, delta, delta);
    cube.Poly2ds.reserve(4);
    for (int i = 0; i < 4; i++)
    {
        cube.Poly2ds.push_back(Poly2d());
    }

    float height = 80;//distance between ellipses
    float d_1 = 200;//distance from left side
    float d_2 = 200+height;//distance from top side

    bool spin = false;
    int spinDirection=1;

    int mouseZ=0;
    int mouseWheelCooldown = 30;//frames
    bool mWCooldown = false;
    int mouseLastX = 0;

    ALLEGRO_EVENT ev;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    //ALLEGRO_TIMER* timer = al_create_timer(1.0);
    //al_register_event_source(alEventQueue_, al_get_timer_event_source(timer));
    //al_start_timer(timer);

    cout << "Press Space to spin\nPress C to change spin direction\nHold Left/A to spin left\nHold Right/D to spin right\nSpin mouse wheel to scale cube\n";

	//ALLEGRO_BITMAP* bmp = al_load_bitmap("pic1.png");
    //al_draw_bitmap(bmp, 0, 0, NULL);
    //al_flip_display();
    //al_grab_mouse(alDisplay_);
    //ALLEGRO_MOUSE_CURSOR* cursor = al_create_mouse_cursor(bmp, 0, 0);
    //al_set_mouse_cursor(alDisplay_, cursor);


    al_start_timer(alTimer_);
    bool redraw = false;
    while (true){
        al_wait_for_event(alEventQueue_, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (ev.timer.source == alTimer_) {
                //printf("a: %f b: %f c: %f d: %f \n", a, b, c, d);
                if(spin){
                    cube.ellipse.IncAll(spinDirection);
                }
                if (pressedKeys_[ALLEGRO_KEY_LEFT] || pressedKeys_[ALLEGRO_KEY_A]) {
                    cube.ellipse.IncAll(-1);
                }
                if (pressedKeys_[ALLEGRO_KEY_RIGHT] || pressedKeys_[ALLEGRO_KEY_D]) {
                    cube.ellipse.IncAll(1);
                }
                /*
                if (pressedKeys_[ALLEGRO_KEY_UP] || pressedKeys_[ALLEGRO_KEY_W]) {
                    cube.ellipse2.IncAll(1);
                }
                if (pressedKeys_[ALLEGRO_KEY_DOWN] || pressedKeys_[ALLEGRO_KEY_S]) {
                    cube.ellipse2.IncAll(-1);
                }
                */
                if(mWCooldown){
                    mouseWheelCooldown--;
                    if (mouseWheelCooldown <= 0){
                        al_set_mouse_z(0);
                        mouseWheelCooldown = 10;
                        mWCooldown = false;
                    }
                }
                
                redraw = true;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            OnKeyDown(ev.keyboard);
            pressedKeys_[ev.keyboard.keycode] = true;
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                spin = !spin;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_C) {
                spinDirection *= -1;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            OnKeyUp(ev.keyboard);
            pressedKeys_[ev.keyboard.keycode] = false;
        }
    	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            mouseZ = ev.mouse.z;

            //mouseLastX = ev.mouse.x;
            //mWCooldown = true;//activate cooldown
            
        }
        if (redraw && al_is_event_queue_empty(alEventQueue_)){
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            cube.Scale(mouseZ);
            //cube.Scale(cube.ellipse.angles[0].GetCos()*50);
            cube.Move();
            cube.Draw();
            al_flip_display();
        }

        if (exit_)
        {
            break;
        }
    }
}

void AllegroApp::Draw() {

}

void AllegroApp::Fps()
{
}