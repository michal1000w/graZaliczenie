#include "EasyConsole.h"
#include <ncurses.h>
#include <string>

using namespace std;

class Menu{
private:
    EasyConsole eCon;
public:
    void DrawMenu(int x, int pos){
        eCon.ClearScr();
        DrawLabel(3, x, "Boulder Dash");
        getch();
    }
    
private:
    void DrawLabel(int y, int x, string text){
        for (int i=0; i<x; i++) printw("="); //rysowanie górnej linii
        int boki = int(x - text.length())/2;
        printw("\n|");
        if ((boki*2)+text.length() == x){
            boki--;
            for (int i = 0; i<boki; i++) printw(" ");
            printw("%s",text.c_str());
            for (int i = 0; i<boki; i++) printw(" ");
        } else {
            boki--;
            for (int i = 0; i<boki; i++) printw(" ");
            printw("%s",text.c_str());
            for (int i = 0; i<=boki; i++) printw(" ");
        }
        printw("|\n");
        for (int i=0; i<x; i++) printw("=");
        printw("\n");
    }
};
