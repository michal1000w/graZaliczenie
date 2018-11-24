#include <ncurses.h>
#include <iostream>
#include "EasyConsole.cpp"

#define sizeX 70
#define sizeY 20

using namespace std;

class Engine{
private:
    EasyConsole eCon;
    char board[sizeY][sizeX];
    struct player{
        int X;
        int Y;
        char Char;
    };
    player Player;
    
public:
    void Init(){
        FillEmpty(); //inicjowanie tablicy zerami
        Player.X = sizeX/2;
        Player.Y = sizeY/2;
        Player.Char = '&';
    }
    
    void MainLoop(){
        DrawFullBoard();
        DrawPlayer();
        
        while(true){
            
            if (MovePlayer() == 'q') //zatrzymanie pętli
                break;
            
            Enemy();
        }
    }
    
private:
    void Enemy(){
        board[10][10] = '4';
        UpdateBoard(10, 10);
    }
    
    char MovePlayer(){
        nodelay(stdscr, true); //non-block input from getch()
        char keyPressed = getch();
        
        if (keyPressed == 'w'){
            board[Player.Y][Player.X] = ' ';
            UpdateBoard(Player.Y, Player.X);
            Player.Y--;
            DrawPlayer();
        } else if (keyPressed == 's'){
            board[Player.Y][Player.X] = ' ';
            UpdateBoard(Player.Y, Player.X);
            Player.Y++;
            DrawPlayer();
        } else if (keyPressed == 'd'){
            board[Player.Y][Player.X] = ' ';
            UpdateBoard(Player.Y, Player.X);
            Player.X++;
            DrawPlayer();
        } else if (keyPressed == 'a'){
            board[Player.Y][Player.X] = ' ';
            UpdateBoard(Player.Y, Player.X);
            Player.X--;
            DrawPlayer();
        }
        
        return keyPressed;
    }
    
    void FillEmpty(){
        for (int y=0; y<sizeY; y++)
            for (int x=0; x<sizeX; x++)
                board[y][x] = ' ';
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
    
    void UpdateBoard(int y, int x){
        move(y+1,x+1);
        if (board[y][x] == Player.Char){
            eCon.Color(6);
            eCon.BoldText(true);
            printw("%c",board[y][x]);
            eCon.Color(1);
            eCon.BoldText(false);
        } else {
            printw("%c",board[y][x]);
        }
    }
    
    void DrawPlayer(){
        board[Player.Y][Player.X] = Player.Char;
        UpdateBoard(Player.Y,Player.X);
    }
};
