#include "AllegroApp.hpp"
using namespace std;
AllegroApp::AllegroApp()
{
}

const double pi = 3.14159265;

double delta = 1;

EllipseAngles ellipse(60, 10, 4, delta);//n - how much dots we need on ellipse, i0 - their increase value

//because for this specific task it is nicer this way
#define a ellipse.angles[0]
#define b ellipse.angles[1]
#define c ellipse.angles[2]
#define d ellipse.angles[3]

void AllegroApp::OnKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard) {
    if (keyboard.keycode == ALLEGRO_KEY_LEFT || keyboard.keycode == ALLEGRO_KEY_A) {
        ellipse.IncAll(-1);
    }else if (keyboard.keycode == ALLEGRO_KEY_RIGHT || keyboard.keycode == ALLEGRO_KEY_D) {
        ellipse.IncAll(1);
    }
}

void DrawFigure(vector<Poly2d>Figure){
	for(int i=0; i <Figure.size(); i++)
	{
        Figure[i].Draw();
        //al_draw_polygon(Figure[i].Polygon.data(), 4, ALLEGRO_LINE_JOIN_BEVEL, Figure[i].color, 3, 1);
	}
}

void AllegroApp::Run() {
    vector<Poly2d>Polygons;
    Polygons.reserve(4);
    for(int i=0;i<4;i++)
    {
        Polygons.push_back(Poly2d());
    }

	double ax, ay, bx, by, cx, cy, dx, dy;

    double side_x = ellipse.GetRx();//ellispe rx
    double side_y = ellipse.GetRy();//ellipse ry
    double height = 80;//distance between ellipses
    double d_1 = 200;//distance from sides
    double d_2 = 200+height;//distance from sides

    bool spin = false;
    int spinDirection=1;

    int mouseZ=0;
    int mouseWheelCooldown = 30;//frames
    bool mWCooldown = false;

    ALLEGRO_EVENT ev;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    //ALLEGRO_TIMER* timer = al_create_timer(1.0);
    //al_register_event_source(alEventQueue_, al_get_timer_event_source(timer));
    //al_start_timer(timer);

    cout << "Press Space to spin\nPress C to change spin direction\nHold Left/A to spin left\nHold Right/D to spin right\nSpin mouse wheel to scale cube\n";
    
    al_start_timer(alTimer_);
    bool redraw = false;
    while (true){
        al_wait_for_event(alEventQueue_, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (ev.timer.source == alTimer_) {
                //printf("a: %f b: %f c: %f d: %f \n", a, b, c, d);
                if(spin){
                    ellipse.IncAll(spinDirection);
                }
                if (pressedKeys_[ALLEGRO_KEY_LEFT] || pressedKeys_[ALLEGRO_KEY_A]) {
                    ellipse.IncAll(-1);
                }
                if (pressedKeys_[ALLEGRO_KEY_RIGHT] || pressedKeys_[ALLEGRO_KEY_D]) {
                    ellipse.IncAll(1);
                }
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
                spinDirection = spinDirection == 1 ? -1 : 1;
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
            //mWCooldown = true;//activate cooldown
        }
        if (redraw && al_is_event_queue_empty(alEventQueue_)){
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            //al_draw_pixel(side_x * cos(a * pi / 180) + 100, side_y * sin(a * pi / 180) + 100, al_map_rgb(255, 255, 255));
            //al_draw_pixel(side_x * cos(b * pi / 180) + 100, side_y * sin(b * pi / 180) + 100, al_map_rgb(255, 255, 255));
            //al_draw_pixel(side_x * cos(c * pi / 180) + 100, side_y * sin(c * pi / 180) + 100, al_map_rgb(255, 255, 255));
            //al_draw_pixel(side_x * cos(d * pi / 180) + 100, side_y * sin(d * pi / 180) + 100, al_map_rgb(255, 255, 255));
            //al_draw_rectangle(side_x * cos(a * pi / 180) + 100, side_y * sin(a * pi / 180) + 100, side_x * cos(a * pi / 180) + 100, -1*side_y * sin(a * pi / 180) + 160, al_map_rgb(255, 255, 255),3);

            //*(1 - a.GetSin() / 10) to add perspective

            d_2 = 200 + height* (1 + ((double)mouseZ) / 100);//scale by mouse wheel
            side_x = ellipse.GetRx() * (1 + ((double)mouseZ) / 100);
            side_y = ellipse.GetRy() * (1 + ((double)mouseZ) / 100);


            ax = side_x * a.GetCos() * (1 - a.GetSin() / 10);
            ay = side_y * a.GetSin() * (1 - a.GetSin() / 10);
            bx = side_x * b.GetCos() * (1 - b.GetSin() / 10);
            by = side_y * b.GetSin() * (1 - b.GetSin() / 10);
            cx = side_x * c.GetCos() * (1 - c.GetSin() / 10);
            cy = side_y * c.GetSin() * (1 - c.GetSin() / 10);
            dx = side_x * d.GetCos() * (1 - d.GetSin() / 10);
            dy = side_y * d.GetSin() * (1 - d.GetSin() / 10);

            
            //printf("ax: %f ay: %f bx: %f by: %f cx: %f cy: %f dx: %f dy: %f \n", ax, ay, bx, by, cx, cy, dx, dy);
            //al_draw_pixel(ax + 100, ay + 100, al_map_rgb(255, 255, 255));
            //al_draw_pixel(bx + 100, by + 100, al_map_rgb(255, 255, 255));
            //al_draw_pixel(ax + 100, -1 * ay + 160, al_map_rgb(255, 255, 255));
            //al_draw_pixel(bx + 100, -1 * by + 160, al_map_rgb(255, 255, 255));

            Polygons[0] = (PolygonFactory::NewPolygon(ax + d_1, ay + d_1, bx + d_1, by + d_1, bx + d_1, -1 * by + d_2, ax + d_1, -1 * ay + d_2, 3, al_map_rgb(255, 0, 0)));//front
            Polygons[1] = (PolygonFactory::NewPolygon(cx + d_1, cy + d_1, dx + d_1, dy + d_1, dx + d_1, -1 * dy + d_2, cx + d_1, -1 * cy + d_2, 3, al_map_rgb(255, 0, 0)));//back
            Polygons[2] = (PolygonFactory::NewPolygon(ax + d_1, ay + d_1, bx + d_1, by + d_1, cx + d_1, cy + d_1, dx + d_1, dy + d_1, 3, al_map_rgb(255, 0, 0)));//top
            Polygons[3] = (PolygonFactory::NewPolygon(ax + d_1, -1 * ay + d_2, bx + d_1, -1 * by + d_2, cx + d_1, -1 * cy + d_2, dx + d_1, -1 * dy + d_2, 3, al_map_rgb(255, 0, 0)));//bottom

            DrawFigure(Polygons);
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