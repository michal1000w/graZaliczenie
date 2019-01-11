/*
    Gra na projekt semestralny
    autor: Michał Wieczorek
*/

#include "Engine.h"
#include "menu.h"

extern const int sizeX;

int main(){
    EasyConsole eCon;
    eCon.ConsoleInit();
    eCon.ColorInit();

    Menu menu;
    printw("Przed rozpoczeciem skonfiguruj okienko konsoli\n");
    printw("Aby przejsc do konfiguracji nacisnij dowolny klawisz");
    getch();
    menu.DrawConSize(sizeY+4, sizeX+28);
    menu.DrawMenu(sizeX+28, 0);
    Engine engine;
    //engine.Init(-1);

    ///////////Zrobić zapis gry
    engine.Init();
    engine.MainLoop();

    endwin();
}
