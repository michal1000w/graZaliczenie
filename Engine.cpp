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
    char Empty, Wall, Box, Dirt, LaserPoz, LaserPion, StrzalPoz, StrzalPion;
    char NextLev;
    int Level, LevScore;
    int gravityDelay, shotDelay, sDelay;
    bool shot;
    
public:
    void Init(int Lev = 1){
        eCon.ClearScr();
        Empty = ' ';
        Level = Lev;
        
        Player.Char = '&';
        LoadLevel();
        
        //Player.X = sizeX/2;
        //Player.Y = sizeY/2;
        Player.Lifes = 3;
        Player.Score = 0;
        Wall = 'H';
        Box = '0';
        Dirt = '#';
        NextLev = '^';
        LaserPoz = '-';
        LaserPion = '|';
        StrzalPoz = 'o';
        StrzalPion = '*';
        shotDelay = sDelay = gravityDelay = 0;
        shot = false;
    }
    
    void MainLoop(){
        DrawFullBoard();
        DrawPlayer();
        
        while(true){
            char keyPressed = MovePlayer();
            if (keyPressed == 'q' || keyPressed == 'Q') //zatrzymanie pętli
                break;
            else if (keyPressed == 'r' || keyPressed == 'R'){ //restart level
                Init(Level);
                Player.Score = LevScore;
                MainLoop();
                break;
            } else if (keyPressed == (char)230){ //next level
                Level++;
                Player.Score += 20;
                LevScore = Player.Score;
                LoadLevel();
                eCon.ClearScr();
                MainLoop();
                break;
            }
            Gravity();
            Strzaly();
            DrawInfo();
            eCon.Sleep(50);
        }
    }
    
private:
    void LoadLevel(){
        FillEmpty(); //inicjowanie tablicy zerami
        if (Level == 1)
            ReadMapFromFile("mapy/map1.txt");
        else if (Level == 2)
            ReadMapFromFile("mapy/map2.txt");
    }
    char MovePlayer(){
        nodelay(stdscr, true); //non-block input from getch()
        char keyPressed = getch();
        nodelay(stdscr, false);
        
        if (keyPressed == 3 && Player.Y > 0 && board[Player.Y-1][Player.X] != Wall){ //strzałka w górę
            if (board[Player.Y-1][Player.X] != Box){
                board[Player.Y][Player.X] = Empty;
                UpdateBoard(Player.Y, Player.X);
                
                if (board[Player.Y-1][Player.X] == NextLev)
                    return (char)230;
                
                Player.Y--;
                DrawPlayer();
            }
        } else if (keyPressed == 2 && Player.Y < sizeY-1 && board[Player.Y+1][Player.X] != Wall){ //strzałka w dół
            if (board[Player.Y+1][Player.X] != Box){
                board[Player.Y][Player.X] = Empty;
                UpdateBoard(Player.Y, Player.X);
                
                if (board[Player.Y+1][Player.X] == NextLev)
                    return (char)230;
                
                Player.Y++;
                DrawPlayer();
            }
        } else if (keyPressed == 5 && Player.X < sizeX-1 && board[Player.Y][Player.X+1] != Wall){ //strzałka w prawo
            if (board[Player.Y][Player.X+1] == Box && board[Player.Y][Player.X+2] == Empty){
                board[Player.Y][Player.X+2] = Box;
                UpdateBoard(Player.Y, Player.X+2);
                board[Player.Y][Player.X] = Empty;
                UpdateBoard(Player.Y,Player.X);
                Player.X++;
                DrawPlayer();
            } else if (board[Player.Y][Player.X+1] != Box){
                board[Player.Y][Player.X] = Empty;
                UpdateBoard(Player.Y, Player.X);
                
                if (board[Player.Y][Player.X+1] == NextLev)
                    return (char)230;
                
                Player.X++;
                DrawPlayer();
            }
        } else if (keyPressed == 4 && Player.X > 0 && board[Player.Y][Player.X-1] != Wall){ //strzałka w lewo
            if (board[Player.Y][Player.X-1] == Box && board[Player.Y][Player.X-2] == Empty){
                board[Player.Y][Player.X-2] = Box;
                UpdateBoard(Player.Y, Player.X-2);
                board[Player.Y][Player.X] = Empty;
                UpdateBoard(Player.Y, Player.X);
                Player.X--;
                DrawPlayer();
            } else if (board[Player.Y][Player.X-1] != Box){
                board[Player.Y][Player.X] = Empty;
                UpdateBoard(Player.Y, Player.X);
                
                if (board[Player.Y][Player.X-1] == NextLev)
                    return (char)230;
                
                Player.X--;
                DrawPlayer();
            }
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
            for (int x=0; x<sizeX; x++){
                if (board[y][x] == NextLev){
                    eCon.Color(7);
                    eCon.BlinkText(true);
                    eCon.BoldText(true);
                    printw("%c",board[y][x]);
                    eCon.Color(1);
                    eCon.BlinkText(false);
                    eCon.BoldText(false);
                } else if (board[y][x] == Box){
                    eCon.Color(3);
                    printw("%c",board[y][x]);
                    eCon.Color(1);
                } else if (board[y][x] == Wall || board[y][x] == LaserPoz || board[y][x] == LaserPion){
                    eCon.ColorEnd();
                    printw("%c",board[y][x]);
                } else {
                    eCon.Color(1);
                    printw("%c",board[y][x]);
                }
            }
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
        } else if (board[y][x] == NextLev){
            eCon.Color(7);
            eCon.BlinkText(true);
            eCon.BoldText(true);
            printw("%c",board[y][x]);
            eCon.Color(1);
            eCon.BlinkText(false);
            eCon.BoldText(false);
        } else if (board[y][x] == Box){
            eCon.Color(3);
            printw("%c",board[y][x]);
            eCon.Color(1);
        } else if (board[y][x] == Wall || board[y][x] == LaserPoz || board[y][x] == LaserPion){
            eCon.ColorEnd();
            printw("%c",board[y][x]);
        } else if (board[y][x] == StrzalPoz || board[y][x] == StrzalPion){
            eCon.Color(2);
            printw("%c",board[y][x]);
        } else {
            eCon.Color(1);
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
        eCon.Color(6);
        printw("Level: %d   ", Level);
        eCon.ColorEnd();
    }
    
    void Gravity(){
        if (gravityDelay > 1){
            for (int y=sizeY-2; y>=0; y--)
                for (int x=0; x<sizeX; x++)
                    if (board[y][x] == Box && board[y+1][x] == Empty){
                        board[y][x] = Empty;
                        board[y+1][x] = Box;
                        UpdateBoard(y, x);
                        UpdateBoard(y+1,x);
                        gravityDelay = 0;
                    }
        } else
            if (gravityDelay < 3)
                gravityDelay++;
    }
    
    void Strzaly(){
        shot = false;
        if (sDelay > 10) { //Rysowanie pierwszego strzału
        for (int y=sizeY; y>=0; y--)
            for (int x=sizeX; x>=0; x--)
                //if (sDelay > 1620){
                    if (board[y][x] == LaserPoz && board[y][x+1] == ' '){ //rysowanie pierwszego strzału Poziom
                        board[y][x+1] = StrzalPoz;
                        UpdateBoard(y, x+1);
                        sDelay = 0;
                        shot = true;
                    } else if (board[y][x] == LaserPion && board[y+1][x] == ' '){ //rysowanie pierwszego strzału Pion
                        board[y+1][x] = StrzalPion;
                        UpdateBoard(y+1, x);
                        sDelay = 0;
                        shot = true;
                    }
                //}
        }else sDelay++;
        
        if (shotDelay > 2 && shot == false){ //ruch strzałów
            for (int y=sizeY; y>=0; y--)
                for (int x=sizeX; x>=0; x--)
                    if (board[y][x] == StrzalPoz && (board[y][x+1] == ' ' || board[y][x+1] == Dirt || board[y][x+1] == Wall)){ //poruszanie się strzały Poziom
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        if (board[y][x+1] != Dirt && board[y][x+1] != Wall && !(x+1 > sizeX-1)){
                            board[y][x+1] = StrzalPoz;
                            UpdateBoard(y, x+1);
                        }
                        shotDelay = 0;
                    } else if (board[y][x] == StrzalPion && (board[y+1][x] == ' ' || board[y+1][x] == Dirt || board[y+1][x] == Wall)){ //poruszanie się strzału pion
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        if (board[y+1][x] != Dirt && board[y+1][x] != Wall && !(y+1 > sizeY-2)){
                            board[y+1][x] = StrzalPion;
                            UpdateBoard(y+1, x);
                        }
                        shotDelay = 0;
                    }
        } else shotDelay++;
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
                for (int i = 0; i < line.length(); i++){
                    board[y][i] = line[i];
                    if (board[y][i] == Player.Char){
                        Player.Y = y;
                        Player.X = i;
                    }
                }
                y++;
            }
            file.close();
        }
    }
};
