#include "Engine.h"

void Engine::Init(int Lev, int Lifes, int KeyCount){
    eCon.ClearScr();
    Empty = ' ';
    Level = Lev;

    Player.Char = '&';
    LoadLevel();

    Player.Lifes = Lifes;
    Player.Score = 0;
    if (Lev == 1) LevScore = 0;
    Wall = 'H';
    Box = '0';
    Dirt = '#';
    NextLev = '^';
    LaserPoz = '-';
    LaserPion = '|';
    StrzalPoz = 'o';
    StrzalPion = '*';
    Enemy = '$';
    Diament = '@';
    Drzwi = '_';
    key.Char = '!';
    key.count = KeyCount;
    keyPocz.count = KeyCount;
    shotDelay = sDelay = gravityDelay = enemyDelay = 0;
    LevLifes = Player.Lifes;
    shot = false;

    LastLevel = 3;
}

void Engine::MainLoop(){
    DrawFullBoard();
    DrawPlayer();
    DrawLegend();

    InitNodes();

    while(true){
        char keyPressed = MovePlayer();
        if (keyPressed == 'q' || keyPressed == 'Q') //zatrzymanie pętli
            break;
        else if (keyPressed == 'r' || keyPressed == 'R'){ //restart level
            Init(Level, LevLifes, keyPocz.count);
            Player.Score = LevScore;
            MainLoop();
            break;
        } else if (keyPressed == (char)230){ //next level
            Level++;
            if (!(Level >= LastLevel)){
                Player.Score += 20;
                LevScore = Player.Score;
                LevLifes = Player.Lifes;
                LoadLevel();
                eCon.ClearScr();
                keyPocz.count = key.count;
                MainLoop();
                break;
            } else {
                char keyPressed = EndPage();
                if (keyPressed == 'r'){
                    Init();
                    MainLoop();
                }
                break;
            }
        }
        Gravity();

        if (Strzaly() == (char)230){ //uderzenie w strzały
            Player.Lifes--;
            //LevScore = Player.Score;
            board[Player.Y][Player.X] = Empty;
            UpdateBoard(Player.Y,Player.X);
            Player.X = PoczPlayer.X;
            Player.Y = PoczPlayer.Y;
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

        //EnemyMove();
        //EnemyMove2(10);
        EnemyMove3(10);

        DrawInfo();
        eCon.Sleep(50);
    }
}

char Engine::EndPage(){
    Menu menu;
    return menu.DrawEndMenu(sizeX, Player.Score);
}

void Engine::Gravity(){
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
