#include "Engine.h"

void Engine::FillEmpty(){
    for (int y=0; y<sizeY; y++)
        for (int x=0; x<sizeX; x++)
            board[y][x] = Empty;
}

void Engine::DrawFullBoard(){
    //rysowanie ramki
    for (int i=0; i<sizeX+2; i++) printw("=");
    printw("\n");
    for (int y=0; y<sizeY; y++){
        printw("|");
        for (int x=0; x<sizeX; x++){
            if (board[y][x] == NextLev || board[y][x] == key.Char){
                eCon.Color(7);
                eCon.BlinkText(true);
                eCon.BoldText(true);
                printw("%c",board[y][x]);
                eCon.ColorEnd();
                eCon.BlinkText(false);
                eCon.BoldText(false);
            } else if (board[y][x] == Box || board[y][x] == Drzwi){
                eCon.Color(3);
                printw("%c",board[y][x]);
                eCon.ColorEnd();
            } else if (board[y][x] == LaserPoz || board[y][x] == LaserPion){
                eCon.ColorEnd();
                printw("%c",board[y][x]);
            } else if (board[y][x] == Enemy){
                eCon.Color(5);
                printw("%c",board[y][x]);
                eCon.ColorEnd();
            } else if (board[y][x] == Diament){
                eCon.Color(7);
                printw("%c",board[y][x]);
                eCon.ColorEnd();
            } else if (board[y][x] == Wall){
                eCon.Color(8);
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

void Engine::UpdateBoard(int y, int x){
    move(y+1,x+1);
    if (board[y][x] == Player.Char){
        eCon.Color(6);
        eCon.BoldText(true);
        printw("%c",board[y][x]);
        eCon.ColorEnd();
        eCon.BoldText(false);
    } else if (board[y][x] == NextLev || board[y][x] == key.Char){
        eCon.Color(7);
        eCon.BlinkText(true);
        eCon.BoldText(true);
        printw("%c",board[y][x]);
        eCon.ColorEnd();
        eCon.BlinkText(false);
        eCon.BoldText(false);
    } else if (board[y][x] == Box || board[y][x] == Drzwi){
        eCon.Color(3);
        printw("%c",board[y][x]);
        eCon.ColorEnd();
    } else if (board[y][x] == LaserPoz || board[y][x] == LaserPion){
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
    } else if (board[y][x] == Diament){
        eCon.Color(7);
        printw("%c",board[y][x]);
        eCon.ColorEnd();
    } else if (board[y][x] == Wall){
        eCon.Color(8);
        printw("%c",board[y][x]);
        eCon.ColorEnd();
    } else {
        eCon.Color(1);
        printw("%c",board[y][x]);
        eCon.ColorEnd();
    }
}
