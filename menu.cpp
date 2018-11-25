#include "EasyConsole.h"
#include <ncurses.h>
#include <string>

using namespace std;

class Menu{
private:
    EasyConsole eCon;
public:
    void DrawMenu(int x, int pos){
        while(true){
            eCon.ClearScr();
            DrawLabel(x, "Projekt Rainbowdash");
            DrawMenuItem(x, "autor: Michal Wieczorek", false);
            DrawLine(x);
            DrawMenuItem(x, "Aby wybrac element uzyj strzalek", false);
            DrawLine(x);
            DrawMenuItem(x, " ", false);
            if (pos == 0)
                DrawMenuItem(x, "Nowa gra", true);
            else
                DrawMenuItem(x, "Nowa gra", false);
            if (pos == 1)
                DrawMenuItem(x, "Sterowanie", true);
            else
                DrawMenuItem(x, "Sterowanie", false);
            DrawMenuItem(x, " ", false);
            DrawLine(x);
        
            //Poruszanie się po menu
            char keyPressed = getch();
            //3 - strzałka w górę
            //2 - strzałka w dół
            //5 - strzałka w prawo
            //4 - strzałka w lewo
            if (keyPressed == 2 && pos < 1)
                pos++;
            else if (keyPressed == 3 && pos > 0)
                pos--;
            else if (keyPressed == 10 && pos == 0)
                break;
            else if (keyPressed == 10 && pos == 1)
                DrawMenuSterowanie(x);
            else if (keyPressed == 'q'){
                endwin();
                exit(1);
                break;
            }
        }
    }
    
    void DrawMenuSterowanie(int x){
        eCon.ClearScr();
        DrawLabel(x, "Sterowanie");
        DrawMenuItem(x, " ", false);
        DrawMenuItem(x,"Uzyj strzalek do poruszania sie po planszy;", false);
        DrawMenuItem(x, "Aby wyjsc z gry nacisnij 'q'", false);
        
        DrawMenuItem(x, " ", false);
        DrawMenuItem(x, "Nacisnij dowolny klawisz by wrocic do menu;", false);
        DrawMenuItem(x, " ", false);
        DrawLine(x);
        getch();
    }
    
private:
    void DrawLabel(int x, string text){
        for (int i=0; i<x; i++) printw("="); //rysowanie górnej linii
        int boki = int(x - text.length())/2;
        printw("\n|");
        eCon.Color(3);
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
        eCon.ColorEnd();
        printw("|\n");
        for (int i=0; i<x; i++) printw("=");
        printw("\n");
    }
    
    void DrawMenuItem(int x, string text, bool selected){
        int boki = int(x - text.length())/2;
        printw("|");
        
        if (selected){
            eCon.BoldText(true);
            eCon.Color(2);
            
            if (boki*2 + text.length() == x){
                boki-=3;
                for (int i=0; i<boki; i++) printw(" ");
                printw("->");
                eCon.UnderlineText(true);
                printw("%s",text.c_str());
                eCon.UnderlineText(false);
                printw("<-");
                for (int i=0; i<boki; i++) printw(" ");
            } else {
                boki-=3;
                for (int i=0; i<boki; i++) printw(" ");
                printw("->");
                eCon.UnderlineText(true);
                printw("%s",text.c_str());
                eCon.UnderlineText(false);
                printw("<-");
                for (int i=0; i<=boki; i++) printw(" ");
            }
            eCon.ColorEnd();
            eCon.BoldText(false);
        } else {
            if (boki*2 + text.length() == x){
                boki--;
                for (int i=0; i<boki; i++) printw(" ");
                printw("%s",text.c_str());
                for (int i=0; i<boki; i++) printw(" ");
            } else {
                boki--;
                for (int i=0; i<boki; i++) printw(" ");
                printw("%s",text.c_str());
                for (int i=0; i<=boki; i++) printw(" ");
            }
        }
        printw("|\n");
    }
    
    void DrawLine(int x){
        for (int i=0; i<x; i++) printw("=");
        printw("\n");
    }
};
