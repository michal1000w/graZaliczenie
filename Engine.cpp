#include <ncurses.h>
#include "EasyConsole.cpp"

#define sizeX 70
#define sizeY 20

using namespace std;

class Engine{
private:
    EasyConsole eCon;
    char board[sizeY][sizeX];
    
public:
    void Init(){
        FillEmpty();
    }
    
    void MainLoop(){
        DrawFullBoard();
        
        while(true){
            char keyPressed = getch();
            if (keyPressed == 'q')
                break;
        }
    }
    
private:
    void FillEmpty(){
        for (int y=0; y<sizeY; y++)
            for (int x=0; x<sizeX; x++)
                board[y][x] = '#';
    }
    
    void DrawFullBoard(){
        //rysowanie ramki
        for (int i=0; i<sizeX+2; i++) printw("=");
        printw("\n");
        for (int y=0; y<sizeY; y++){
            printw("|");
            for (int x=0; x<sizeX; x++)
                printw("%c",board[y][x]);
            printw("|\n");
        }
        for (int i=0; i<sizeX+2; i++) printw("=");
    }
};
