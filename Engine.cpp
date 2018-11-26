#include <ncurses.h>
#include <iostream>
#include <fstream>
#include "EasyConsole.h"

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
        int Lifes;
        int Score;
        char Char;
    };
    player Player;
    char Empty, Wall, Box;
    int gravityDelay;
    
public:
    void Init(){
        eCon.ClearScr();
        Empty = ' ';
        FillEmpty(); //inicjowanie tablicy zerami
        ReadMapFromFile("mapy/map1.txt");
        Player.X = sizeX/2;
        Player.Y = sizeY/2;
        Player.Lifes = 3;
        Player.Score = 0;
        Player.Char = '&';
        Wall = '#';
        Box = '0';
        gravityDelay = 0;
    }
    
    void MainLoop(){
        DrawFullBoard();
        DrawPlayer();
        
        while(true){
            if (MovePlayer() == 'q') //zatrzymanie pętli
                break;
            Gravity();
            DrawInfo();
            eCon.Sleep(50);
        }
    }
    
private:
    char MovePlayer(){
        nodelay(stdscr, true); //non-block input from getch()
        char keyPressed = getch();
        nodelay(stdscr, false);
        
        if (keyPressed == 3 && Player.Y > 0){ //strzałka w górę
            board[Player.Y][Player.X] = Empty;
            UpdateBoard(Player.Y, Player.X);
            Player.Y--;
            DrawPlayer();
        } else if (keyPressed == 2 && Player.Y < sizeY-1){ //strzałka w dół
            board[Player.Y][Player.X] = Empty;
            UpdateBoard(Player.Y, Player.X);
            Player.Y++;
            DrawPlayer();
        } else if (keyPressed == 5 && Player.X < sizeX-1){ //strzałka w prawo
            board[Player.Y][Player.X] = Empty;
            UpdateBoard(Player.Y, Player.X);
            Player.X++;
            DrawPlayer();
        } else if (keyPressed == 4 && Player.X > 0){ //strzałka w lewo
            board[Player.Y][Player.X] = Empty;
            UpdateBoard(Player.Y, Player.X);
            Player.X--;
            DrawPlayer();
        }
        return keyPressed;
    }
    
    void FillEmpty(){
        for (int y=0; y<sizeY; y++)
            for (int x=0; x<sizeX; x++)
                board[y][x] = Empty;
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
    
    void DrawInfo(){
        move(sizeY + 2,4);
        eCon.Color(2);
        printw("Lifes: %d     ", Player.Lifes);
        eCon.Color(1);
        printw("Score: %d     ", Player.Score);
        eCon.ColorEnd();
    }
    
    void Gravity(){
        for (int y=sizeY-2; y>=0; y--)
            for (int x=0; x<sizeX; x++){
                if (board[y][x] == Wall && board[y+1][x] == Empty && gravityDelay > 50){
                    board[y][x] = Empty;
                    board[y+1][x] = Wall;
                    UpdateBoard(y, x);
                    UpdateBoard(y+1,x);
                    gravityDelay = 0;
                } else
                    if (gravityDelay < 100)
                        gravityDelay++;
            }
    }
    
    void ReadMapFromFile(const string filename){
        string line;
        int y = 0;
        
        ifstream file;
        file.open(filename);
        if (file.is_open())
        {
            while ( getline (file,line) )
            {
                for (int i = 0; i < line.length(); i++)
                    board[y][i] = line[i];
                y++;
            }
            file.close();
        }
    }
};
