#include <ncurses.h>

#define sizeX 30
#define sizeY 10

using namespace std;

class Engine{
private:
    char board[sizeY][sizeX];
    
public:
    void Init(){
        FillEmpty();
        DrawFullBoard();
    }
    
private:
    void FillEmpty(){
        for (int y=0; y<sizeY; y++)
            for (int x=0; x<sizeX; x++)
                board[y][x] = '#';
    }
    
    void DrawFullBoard(){
        for (int y=0; y<sizeY; y++){
            for (int x=0; x<sizeX; x++)
                printw("%c",board[y][x]);
            printw("\n");
        }
    }
};
