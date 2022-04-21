#include "AllegroApp.hpp"
using namespace std;
AllegroApp::AllegroApp():
    p3dsSize(0)
{}

float delta = 1;

void AllegroApp::OnKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard) {
    if (keyboard.keycode == ALLEGRO_KEY_LEFT || keyboard.keycode == ALLEGRO_KEY_A) {

    }else if (keyboard.keycode == ALLEGRO_KEY_RIGHT || keyboard.keycode == ALLEGRO_KEY_D) {

    }
}

void AllegroApp::AddFigure()
{
    int size = 10;//number of args, user inputs
    float* args = new float[size]();
    cout << "Please input spinning objects:\nx,y,height,width,e1 ry,e1 rx,pointCount\n";//,e1 increase,e2 increase,spin direction(vertical/sideways(1/0))
    for(int i=0;i<size-3;i++)//for(int i=0;i<size;i++)
    {
        cin >> args[i];
    }
    //poly3ds.emplace_back(x,y,height,width,e1ry,e2rx,pointCount,e1increase,e2increase,spinDirection);
    poly3ds.emplace_back(args[0], args[1], args[2], args[3], args[4], args[5], args[6], 1, 1, 0);//args[7], args[8], args[9]
    p3dsSize++;
    poly3ds[p3dsSize - 1].Poly2ds.reserve(args[6]);//args[6]==pointCount
    poly3ds[p3dsSize - 1].Poly2ds.emplace_back(3);
    cout << "Successfully created new figure!\n";
}
void AllegroApp::RemoveFigure(int n)
{
    /*
    poly3ds.erase(poly3ds.begin() + n);
    p3dsSize--;
    cout << "Successfully removed figure "<< n <<"!\n";
    */
}

void AllegroApp::Run() {
    cout << "Welcome!\nIn this app you can simulate spinning 3d figures!\n\n";
    //cout << "To add object press 1\n";

    //poly3ds.emplace_back(x, y, height, width, e1ry, e2rx, pointCount, e1 increase, e2 increase, spin direction);
    poly3ds.emplace_back(200, 200, 80, 120, 10, 10, 5, delta, delta, false);
    poly3ds.emplace_back(300, 200, 80, 120, 10, 10, 5, delta, delta, true);
    p3dsSize = poly3ds.size();
    for (int j = 0; j < p3dsSize; j++) {
        poly3ds[j].Poly2ds.reserve(poly3ds[j].pointCount);
        for (int i = 0; i < poly3ds[j].pointCount; i++)
        {
            poly3ds[j].Poly2ds.emplace_back(3);//poly3ds[j].Poly2ds.push_back(Poly2d(3));
        }
    }

    bool spin = false;
    float spinDirection=1;

    int mouseZ=0;
    int mouseWheelCooldown = 30;//frames
    bool mWCooldown = false;

    ALLEGRO_EVENT ev;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    //ALLEGRO_TIMER* timer = al_create_timer(1.0);
    //al_register_event_source(alEventQueue_, al_get_timer_event_source(timer));
    //al_start_timer(timer);

    cout << "Press Space to spin\nPress C to change spin direction\nHold Left/A to spin left\nHold Right/D to spin right\nHold Up/W to spin up\nHold Down/S to spin down\nSpin mouse wheel to scale cube\n";

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
                    for(int i=0;i<p3dsSize;i++)
                    {
	                    poly3ds[i].ellipse.IncAll(spinDirection * poly3ds[i].ellipse.angles[0].inc);
                        poly3ds[i].ellipse2.IncAll(spinDirection * poly3ds[i].ellipse.angles[0].inc);
                    }
                }
                if (pressedKeys_[ALLEGRO_KEY_LEFT] || pressedKeys_[ALLEGRO_KEY_A]) {
                    for (int i = 0; i < p3dsSize; i++)
                    {
                        poly3ds[i].ellipse.IncAll(-poly3ds[i].ellipse.angles[0].inc);
                    }
                }
                if (pressedKeys_[ALLEGRO_KEY_RIGHT] || pressedKeys_[ALLEGRO_KEY_D]) {
                    for (int i = 0; i < p3dsSize; i++)
                    {
                        poly3ds[i].ellipse.IncAll(poly3ds[i].ellipse.angles[0].inc);
                    }
                }
                
                if (pressedKeys_[ALLEGRO_KEY_UP] || pressedKeys_[ALLEGRO_KEY_W]) {
                    for (int i = 0; i < p3dsSize; i++)
                    {
                        poly3ds[i].ellipse2.IncAll(poly3ds[i].ellipse.angles[0].inc);
                    }
                }
                if (pressedKeys_[ALLEGRO_KEY_DOWN] || pressedKeys_[ALLEGRO_KEY_S]) {
                    for (int i = 0; i < p3dsSize; i++)
                    {
                        poly3ds[i].ellipse2.IncAll(-poly3ds[i].ellipse.angles[0].inc);
                    }
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
                spinDirection *= -1;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_1) {
                //AddFigure();
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

            for (int i = 0; i < p3dsSize; i++)
            {
                poly3ds[i].Scale(mouseZ);
            }
            Fps();
            Draw();
            al_flip_display();
        }

        if (exit_)
        {
            break;
        }
    }
}
void AllegroApp::Fps()
{
    for (int i = 0; i < p3dsSize; i++)
    {
        poly3ds[i].Move();
    }
}
void AllegroApp::Draw()
{
    for (int i = 0; i < p3dsSize; i++)
    {
        poly3ds[i].Draw();
    }
}