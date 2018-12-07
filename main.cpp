/*
    Gra na projekt semestralny
    autor: Michał Wieczorek
*/

#include "Engine.cpp"
#include "menu.h"

extern const int sizeX;

int main(){
    EasyConsole eCon;
    eCon.ConsoleInit();
    eCon.ColorInit();
    
    Menu menu;
    menu.DrawMenu(sizeX, 0);
    Engine engine;
    engine.Init();
    engine.MainLoop();
    
    endwin();
}
