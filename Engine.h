#ifndef Engine_h
#define Engine_h

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "EasyConsole.h"
#include "menu.h"

const int sizeX = 70;
const int sizeY = 20;

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
    player PoczPlayer;
    char Empty, Wall, Box, Dirt, LaserPoz, LaserPion, StrzalPoz, StrzalPion, Diament;
    char NextLev;
    int Level, LevScore, LevLifes;
    int gravityDelay, shotDelay, sDelay, enemyDelay;
    bool shot;
    char Enemy;
    
public:
    void Init(int Lev = 1, int Lifes = 3);
    void MainLoop();
    
private:
    char EndPage();
    void LoadLevel();
    char MovePlayer();
    void FillEmpty();
    void DrawFullBoard();
    void UpdateBoard(int, int);
    void DrawPlayer();
    void DrawInfo();
    void DrawLegend();
    void Gravity();
    char Strzaly();
    void EnemyMove();
    void ReadMapFromFile(const string filename);
};


#endif /* Engine_h */
