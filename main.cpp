#include <ncurses.h>
#include <iostream>

#include "Engine.cpp"
#include "EasyConsole.cpp"

void Alle(){
    char znak = getch();
    attron(A_BOLD); //pogrubiony tekst
    printw( "%d" , znak);
    
    attron(A_BOLD | A_UNDERLINE); //pogubienie i podkreślenie
    printw("\nkolejna linia, podkreślona");
    attroff(A_BOLD | A_UNDERLINE); //usuwa dodatki tekstu
    printw("\nNormalny tekst");
}

int main(){
    EasyConsole eCon;
    eCon.ConsoleInit();
    eCon.ColorInit();
    
    Engine engine;
    engine.Init();
    
    getch();
    endwin();
}
