#ifndef menu_h
#define menu_h

#include "EasyConsole.h"
#include <ncurses.h>
#include <string>

using namespace std;

class Menu{
private:
    EasyConsole eCon;
public:
    void DrawMenu(int, int);
    void DrawMenuSterowanie(int);
    char DrawEndMenu(int,int);
private:
    void DrawLabel(int, string);
    void DrawMenuItem(int, string, bool);
    void DrawLine(int);
};

#endif
