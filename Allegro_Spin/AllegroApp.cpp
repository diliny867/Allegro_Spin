#include "AllegroApp.hpp"
using namespace std;
AllegroApp::AllegroApp():
    p3dsSize(0),
    inFunc(false)
{}

void AllegroApp::OnKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard) {
    if (keyboard.keycode == ALLEGRO_KEY_LEFT || keyboard.keycode == ALLEGRO_KEY_A) {

    }else if (keyboard.keycode == ALLEGRO_KEY_RIGHT || keyboard.keycode == ALLEGRO_KEY_D) {

    }
}

void AllegroApp::AddFigure()
{
    inFunc = true;
    int size = 10;//number of args, user inputs
    int sm = 0;
    float* args = new float[size]();
    cout << "Use Simple/Advanced input (input 0/1)\n";
    int choice;
    cin >> choice;
    if (choice == -1) { return; }
    if (choice == 0) {
        sm = 3;
        args[7] = 1;
        args[8] = 1;
        args[9] = 0;
        cout << "Please input spinning objects:\nx,y,height,width,e1 ry,e1 rx,pointCount\n";
    }
    else {
        cout << "Please input spinning objects:\nx,y,height,width,e1 ry,e1 rx,pointCount,e1 increase,e2 increase,spin direction(vertical/sideways(1/0))\n";
    }
    for(int i=0;i<size-sm;i++)//for(int i=0;i<size;i++)
    {
        cin >> args[i];
        if (args[i] == -1) { return; }
    }
    //poly3ds.emplace_back(x,y,height,width,e1ry,e2rx,pointCount,e1increase,e2increase,spinDirection);
    poly3ds.emplace_back(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
    p3dsSize++;
    poly3ds[p3dsSize - 1].Poly2ds.reserve(args[6]);//args[6]==pointCount
    for (int i = 0; i < (int)args[6]; i++)
    {
        poly3ds[p3dsSize - 1].Poly2ds.emplace_back(3);//poly3ds[j].Poly2ds.push_back(Poly2d(3));
    }
    cout << "Successfully created new figure!\n";
}
void AllegroApp::RemoveFigure()
{
    inFunc = true;
    cout << "Choose which figure to remove (now only last figure remove works (so your choice doesnt matter))\n";
    int choice;
    cin >> choice;
    if (choice == -1) { return; }
    if (choice > p3dsSize || choice < 0) { cout << "Choosen figure dos not exists\n"; return; }
    //poly3ds.erase(poly3ds.begin() + choice);//compile error
    poly3ds.pop_back();
    p3dsSize--;
    cout << "Successfully removed figure "<< choice <<"!\n";
    
}
void AllegroApp::EditFigure()
{
    inFunc = true;
    cout << "Choose which figure to edit\n";
    int choice,choice2;
    float pData;
    cin >> choice;
    if (choice == -1) { return; }
    if (choice > p3dsSize || choice < 0) { cout << "Choosen figure dos not exists\n"; return; }
    cout << "Choice parameter to edit\n0-x 1-y 2-height 3-width 4-e1 ry 5-e1 rx 6-e1 increase 7-e2 increase 8-spin direction\n";
    cin >> choice2;
    if (choice2 == -1) { return; }
    if (choice2 > 8 || choice <0) { cout << "Incorrect parameter\n"; return; }
    cout << "Input parameter data\n";
    cin >> pData;
    if (pData == -1) { return; }
    switch (choice2) {
    case 0:
        poly3ds[choice].x = pData;
        break;
    case 1:
        poly3ds[choice].y = pData;
        break;
    case 2:
        poly3ds[choice].height = pData;
        break;
    case 3:
        poly3ds[choice].width = pData;
        break;
    case 4:
        poly3ds[choice].ellipse.SetRy(pData);
        break;
    case 5:
        poly3ds[choice].ellipse2.SetRx(pData);
        break;
    case 6:
        poly3ds[choice].ellipse.SetInc(pData);
        break;
    case 7:
        poly3ds[choice].ellipse2.SetInc(pData);
        break;
    case 8:
        poly3ds[choice].drctn = pData;
        break;
    }
    cout << "Successfully edited figure " << choice << "!\n";
}

void AllegroApp::Run() {
    cout << "Welcome!\nIn this app you can simulate spinning 3d figures!\n\n";
    //cout << "To add object press 1\n";
    float delta = 1;

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

    cout << "Press 1 to add figure(-1 to cancel)\nPress 2 to remove figure(-1 to cancel)\nPress 3 to edit figure(-1 to cancel)\nPress Space to spin\nPress C to change spin direction\nHold Left/A to spin left\nHold Right/D to spin right\nHold Up/W to spin up\nHold Down/S to spin down\nSpin mouse wheel to scale cube\n";

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
            //OnKeyDown(ev.keyboard);
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
            //OnKeyUp(ev.keyboard);
            pressedKeys_[ev.keyboard.keycode] = false;
            if (ev.keyboard.keycode == ALLEGRO_KEY_1) {
                if (!inFunc) {
                    AddFigure();
                }
                inFunc = false;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_2) {
                if (!inFunc) {
                    RemoveFigure();
                }
                inFunc = false;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_3) {
                if (!inFunc) {
                    EditFigure();
                }
                inFunc = false;
            }
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