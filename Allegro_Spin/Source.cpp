#include <iostream>
#include <windows.h>
#include <cstdlib>
#include "AllegroApp.hpp"
using namespace std;

int main(int argc, char** argv) {
    srand(time(0));
    AllegroApp  allegro;
    AllegroBase& AllegroMain = allegro;
    if (!AllegroMain.Init(SCREEN_W, SCREEN_H, FPS))
    {
        AllegroMain.Destroy();
        return 1;
    }
    AllegroMain.Run();
    AllegroMain.Destroy();
    return 0;
}
