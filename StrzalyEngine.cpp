#include "Engine.h"

char Engine::Strzaly(){
    shot = false;
    if (sDelay > 10) { //Rysowanie pierwszego strzału
        for (int y=sizeY; y>=0; y--)
            for (int x=sizeX; x>=0; x--)
                //if (sDelay > 1620){
                if (board[y][x] == LaserPoz && (board[y][x+1] == Empty || board[y][x+1] == Player.Char)){ //rysowanie pierwszego strzału Poziom
                    if (board[y][x+1] == Player.Char) return (char)230;
                    board[y][x+1] = StrzalPoz;
                    UpdateBoard(y, x+1);
                    sDelay = 0;
                    shot = true;
                } else if (board[y][x] == LaserPion && (board[y+1][x] == Empty || board[y+1][x] == Player.Char)){ //rysowanie pierwszego strzału Pion
                    if (board[y+1][x] == Player.Char) return (char)230;
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
                if (board[y][x] == StrzalPoz && (board[y][x+1] == Empty || board[y][x+1] == Dirt || board[y][x+1] == Wall || board[y][x+1] == Enemy || board[y][x+1] == Box || board[y][x+1] == Diament)){ //poruszanie się strzały Poziom
                    board[y][x] = Empty;
                    UpdateBoard(y, x);
                    if (board[y][x+1] != Dirt && board[y][x+1] != Wall && !(x+1 > sizeX-1) && board[y][x+1] != Enemy && board[y][x+1] != Box && board[y][x+1] != Diament){
                        board[y][x+1] = StrzalPoz;
                        UpdateBoard(y, x+1);
                    }
                    shotDelay = 0;
                } else if (board[y][x] == StrzalPion && (board[y+1][x] == Empty || board[y+1][x] == Dirt || board[y+1][x] == Wall || board[y+1][x] == Enemy || board[y+1][x] == Box || board[y+1][x] == Diament)){ //poruszanie się strzału pion
                    board[y][x] = Empty;
                    UpdateBoard(y, x);
                    if (board[y+1][x] != Dirt && board[y+1][x] != Wall && !(y+1 > sizeY-2) && board[y+1][x] != Enemy && board[y+1][x] != Box && board[y+1][x] != Diament){
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
