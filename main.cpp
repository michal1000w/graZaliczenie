/*
    Gra na projekt semestralny
    autor: Michał Wieczorek
*/

#include "Engine.cpp"
#include "menu.cpp"

int main(){
    EasyConsole eCon;
    eCon.ConsoleInit();
    eCon.ColorInit();
    
    Menu menu;
    menu.DrawMenu(70, 0);
    
    Engine engine;
    engine.Init();
    engine.MainLoop();
    
    getch();
    endwin();
}
