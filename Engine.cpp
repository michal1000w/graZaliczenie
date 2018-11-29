#include <ncurses.h>
#include <iostream>
#include <fstream>

#include "EasyConsole.h"
#include "menu.h"

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
    int gravityDelay, shotDelay, sDelay, enemyDelay;
    bool shot;
    char Enemy;
    
public:
    void Init(int Lev = 1, int Lifes = 3){
        eCon.ClearScr();
        Empty = ' ';
        Level = Lev;
        
        Player.Char = '&';
        LoadLevel();
        
        //Player.X = sizeX/2;
        //Player.Y = sizeY/2;
        Player.Lifes = Lifes;
        Player.Score = 0;
        Wall = 'H';
        Box = '0';
        Dirt = '#';
        NextLev = '^';
        LaserPoz = '-';
        LaserPion = '|';
        StrzalPoz = 'o';
        StrzalPion = '*';
        Enemy = '$';
        shotDelay = sDelay = gravityDelay = enemyDelay = 0;
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
                Init(Level, Player.Lifes);
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
            
            if (Strzaly() == (char)230){ //uderzenie w strzały
                Player.Lifes--;
                LoadLevel();
                eCon.ClearScr();
                MainLoop();
                break;
            }
            
            if (Player.Lifes <= 0){ //koniec gry
                char keyPressed = EndPage();
                if (keyPressed == 'r'){
                    Init();
                    MainLoop();
                }
                break;
            }
            
            EnemyMove();
            
            DrawInfo();
            eCon.Sleep(50);
        }
    }
    
private:
    char EndPage(){
        Menu menu;
        return menu.DrawEndMenu(70, Player.Score);
    }
    
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
        
        if (keyPressed == 3 && Player.Y > 0 && board[Player.Y-1][Player.X] != Wall && board[Player.Y-1][Player.X] != LaserPoz && board[Player.Y-1][Player.X] != LaserPion){ //strzałka w górę
            if (board[Player.Y-1][Player.X] != Box){
                board[Player.Y][Player.X] = Empty;
                UpdateBoard(Player.Y, Player.X);
                
                if (board[Player.Y-1][Player.X] == NextLev)
                    return (char)230;
                
                Player.Y--;
                DrawPlayer();
            }
        } else if (keyPressed == 2 && Player.Y < sizeY-1 && board[Player.Y+1][Player.X] != Wall && board[Player.Y+1][Player.X] != LaserPoz && board[Player.Y+1][Player.X] != LaserPion){ //strzałka w dół
            if (board[Player.Y+1][Player.X] != Box){
                board[Player.Y][Player.X] = Empty;
                UpdateBoard(Player.Y, Player.X);
                
                if (board[Player.Y+1][Player.X] == NextLev)
                    return (char)230;
                
                Player.Y++;
                DrawPlayer();
            }
        } else if (keyPressed == 5 && Player.X < sizeX-1 && board[Player.Y][Player.X+1] != Wall && board[Player.Y][Player.X+1] != LaserPoz && board[Player.Y][Player.X+1] != LaserPion){ //strzałka w prawo
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
        } else if (keyPressed == 4 && Player.X > 0 && board[Player.Y][Player.X-1] != Wall && board[Player.Y][Player.X-1] != LaserPoz && board[Player.Y][Player.X-1] != LaserPion){ //strzałka w lewo
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
                    eCon.ColorEnd();
                    eCon.BlinkText(false);
                    eCon.BoldText(false);
                } else if (board[y][x] == Box){
                    eCon.Color(3);
                    printw("%c",board[y][x]);
                    eCon.ColorEnd();
                } else if (board[y][x] == Wall || board[y][x] == LaserPoz || board[y][x] == LaserPion){
                    eCon.ColorEnd();
                    printw("%c",board[y][x]);
                } else if (board[y][x] == Enemy){
                    eCon.Color(5);
                    printw("%c",board[y][x]);
                    eCon.ColorEnd();
                } else {
                    eCon.Color(1);
                    printw("%c",board[y][x]);
                    eCon.ColorEnd();
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
            eCon.ColorEnd();
            eCon.BoldText(false);
        } else if (board[y][x] == NextLev){
            eCon.Color(7);
            eCon.BlinkText(true);
            eCon.BoldText(true);
            printw("%c",board[y][x]);
            eCon.ColorEnd();
            eCon.BlinkText(false);
            eCon.BoldText(false);
        } else if (board[y][x] == Box){
            eCon.Color(3);
            printw("%c",board[y][x]);
            eCon.ColorEnd();
        } else if (board[y][x] == Wall || board[y][x] == LaserPoz || board[y][x] == LaserPion){
            eCon.ColorEnd();
            printw("%c",board[y][x]);
        } else if (board[y][x] == StrzalPoz || board[y][x] == StrzalPion){
            eCon.Color(2);
            printw("%c",board[y][x]);
            eCon.ColorEnd();
        } else if (board[y][x] == Enemy){
            eCon.Color(5);
            printw("%c",board[y][x]);
            eCon.ColorEnd();
        } else {
            eCon.Color(1);
            printw("%c",board[y][x]);
            eCon.ColorEnd();
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
    
    char Strzaly(){
        shot = false;
        if (sDelay > 10) { //Rysowanie pierwszego strzału
        for (int y=sizeY; y>=0; y--)
            for (int x=sizeX; x>=0; x--)
                //if (sDelay > 1620){
                    if (board[y][x] == LaserPoz && board[y][x+1] == Empty){ //rysowanie pierwszego strzału Poziom
                        board[y][x+1] = StrzalPoz;
                        UpdateBoard(y, x+1);
                        sDelay = 0;
                        shot = true;
                    } else if (board[y][x] == LaserPion && board[y+1][x] == Empty){ //rysowanie pierwszego strzału Pion
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
                    if (board[y][x] == StrzalPoz && (board[y][x+1] == Empty || board[y][x+1] == Dirt || board[y][x+1] == Wall)){ //poruszanie się strzały Poziom
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        if (board[y][x+1] != Dirt && board[y][x+1] != Wall && !(x+1 > sizeX-1)){
                            board[y][x+1] = StrzalPoz;
                            UpdateBoard(y, x+1);
                        }
                        shotDelay = 0;
                    } else if (board[y][x] == StrzalPion && (board[y+1][x] == Empty || board[y+1][x] == Dirt || board[y+1][x] == Wall)){ //poruszanie się strzału pion
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        if (board[y+1][x] != Dirt && board[y+1][x] != Wall && !(y+1 > sizeY-2)){
                            board[y+1][x] = StrzalPion;
                            UpdateBoard(y+1, x);
                        }
                        shotDelay = 0;
                    } else if ((board[y][x] == StrzalPion && board[y+1][x] == Player.Char) || (board[y][x] == StrzalPoz && board[y][x+1] == Player.Char)){  //uderzenie w gracza
                        return (char)230;
                    }
        } else shotDelay++;
        
        return (char)210;
    }
    
    void EnemyMove(){ // poprawić bo zbugowane
        if (enemyDelay > 7){
            for (int y=0;y<sizeY;y++)
                for (int x=0;x<sizeX;x++){
                    int kierunek = rand()%4 + 1;
                    if (board[y][x] == Enemy && enemyDelay > 10600){
                        if (board[y][x+1] == Empty && kierunek == 1){ //prawo (puste)
                            board[y][x] = Empty;
                            UpdateBoard(y, x);
                            board[y][x+1] = Enemy;
                            UpdateBoard(y, x+1);
                            enemyDelay = 0;
                        } else if (board[y][x-1] == Empty && kierunek == 2){ //lewo (puste)
                            board[y][x] = Empty;
                            UpdateBoard(y, x);
                            board[y][x-1] = Enemy;
                            UpdateBoard(y, x-1);
                            enemyDelay = 0;
                        } else if (board[y+1][x] == Empty && kierunek == 3){ // dół (puste)
                            board[y][x] = Empty;
                            UpdateBoard(y, x);
                            board[y+1][x] = Enemy;
                            UpdateBoard(y+1, x);
                            enemyDelay = 0;
                        } else if (board[y-1][x] == Empty && kierunek == 4){ //góra (puste)
                            board[y][x] = Empty;
                            UpdateBoard(y, x);
                            board[y-1][x] = Enemy;
                            UpdateBoard(y-1, x);
                            enemyDelay = 0;
                        } else if (board[y][x+1] != Empty && kierunek == 1 && board[y][x-1] == Empty){ //lewo gdy w prawo nie można
                            board[y][x] = Empty;
                            UpdateBoard(y, x);
                            board[y][x-1] = Enemy;
                            UpdateBoard(y, x-1);
                            enemyDelay = 0;
                        } else if (board[y][x-1] != Empty && kierunek == 2 && board[y][x+1] == Empty){ //prawo gdy w lewo nie można
                            board[y][x] = Empty;
                            UpdateBoard(y, x);
                            board[y][x+1] = Enemy;
                            UpdateBoard(y, x+1);
                            enemyDelay = 0;
                        } else if (board[y+1][x] != Empty && kierunek == 3 && board[y-1][x] == Empty){ //góra, gdy w dół nie można
                            board[y][x] = Empty;
                            UpdateBoard(y, x);
                            board[y-1][x] = Enemy;
                            UpdateBoard(y-1, x);
                            enemyDelay = 0;
                        } else if (board[y-1][x] != Empty && kierunek == 4 && board[y+1][x] == Empty){ //dół, gdy w górę nie można
                            board[y][x] = Empty;
                            UpdateBoard(y, x);
                            board[y+1][x] = Enemy;
                            UpdateBoard(y+1, x);
                            enemyDelay = 0;
                        } else enemyDelay++;
                        
                    } else enemyDelay++;
                }
        } else if (enemyDelay < 10) enemyDelay++;
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
