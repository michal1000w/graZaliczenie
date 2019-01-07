#ifndef Engine_h
#define Engine_h

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>
#include <string>

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
    struct Key{
        int Char;
        int count;
    } key, keyPocz;
    char Empty, Wall, Box, Dirt, LaserPoz, LaserPion, StrzalPoz, StrzalPion, Diament, Drzwi;
    char NextLev, Path;
    int Level, LevScore, LevLifes;
    int gravityDelay, shotDelay, sDelay, enemyDelay;
    bool shot;
    char Enemy;
    int LastLevel;

    //AI
    struct Start{
      int x;
      int y;
      int num;
    } start;

    struct sNode{
	    bool Obstacle = false;
	    bool Visited = false;
	    float GlobalGoal;
      float LocalGoal;
	    int x;
	    int y;
	    vector<sNode*> Neighbours;
	    sNode* parent;
    };
    sNode* nodes = nullptr;
    sNode *nodeStart = nullptr;
    sNode *nodeEnd = nullptr;

public:
    void Init(int Lev = 1, int Lifes = 3, int KeyCount = 0);
    void MainLoop();

private:
    char EndPage();
    void LoadLevel();
    char MovePlayer();
    void BoxMove(int);
    void FillEmpty();
    void DrawFullBoard();
    void UpdateBoard(int, int);
    void DrawPlayer();
    void DrawInfo();
    void DrawLegend();
    void Gravity();
    char Strzaly();
    void EnemyMove();

    void EnemyMove2(int Delay = 7);
    bool deadEnd(int,int);
    bool SolveM(int,int);
    void ClearDots(bool visible = false);

    int EnemyMove3(int Delay = 7);
    bool InitNodes();
    void SetupNodes();
    bool Solve_AStar(sNode*);
    bool DrawShortestPath(bool,sNode*);
    void ReloadNodes();

    void ReadMapFromFile(const string filename);
};


#endif /* Engine_h */
