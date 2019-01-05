#include "Engine.h"

bool Engine::reachedEnd(int y, int x){
  return board[y][x] == Player.Char;
}

bool Engine::deadEnd(int y, int x){
  return (board[y][x] != Empty && board[y][x] != Enemy) || board[y][x] == '.';
}

void Engine::ClearDots(){
  for (int y = 0; y < sizeY; y++)
    for (int x = 0; x < sizeX; x++){
      if (board[y][x] == '.') board[y][x] = Empty;
    }
}

bool Engine::SolveM(int y, int x){
  //return true;
  if (reachedEnd(y,x)) return true;
  else if(deadEnd(y,x)){
    start.x = x;
    start.y = y;
    return false;
  }
  else {
    board[y][x] = '.';
    UpdateBoard(y,x);
    start.y = y;
    start.x = x;
    if (y-1 >= 0 && SolveM(y-1,x)) return true;
    else if(x+1 < sizeX && SolveM(y,x+1)) return true;
    else if(y+1 < sizeY && SolveM(y+1,x)) return true;
    else if (x-1 >= 0 && SolveM(y,x-1)) return true;
    else{
      board[y][x] = ' ';
      UpdateBoard(y,x);
      start.y = y;
      start.x = x;
      return false;
    }
  }
  return false;
}

void Engine::EnemyMove2(int Delay){
    vector <int> przesunieci;
    przesunieci.clear();
    bool czyBreak = false;
    if (enemyDelay > Delay){
        for (int y=0; y<sizeY; y++)
            for (int x = 0; x<sizeX; x++){
              if (board[y][x] == Enemy){
                //Sprawdzanie, czy dany wróg nie został już poruszony
                if (przesunieci.size() >= 2)
                    for (int i=0; i < przesunieci.size()/2; i++)
                        if (y == przesunieci[i*2] && x == przesunieci[i*2 + 1]){ //żeby nie przesuwał po raz drugi tego samego
                            czyBreak = true;
                            break;
                        }
                if (czyBreak == true){
                    czyBreak = false;
                    continue;  //poprzednio był break, sprawdzić jak będzie działać
                }

                //AI
                start.x = x;
                start.y = y;
                if (SolveM(start.y,start.x)){
                  if (board[y+1][x] == '.'){
                    board[y+1][x] = Enemy;
                    board[y][x] = Empty;
                    UpdateBoard(y+1,x);
                    UpdateBoard(y,x);
                    przesunieci.push_back(y+1);
                    przesunieci.push_back(x);
                  } else if (board[y-1][x] == '.'){
                    board[y-1][x] = Enemy;
                    board[y][x] = Empty;
                    UpdateBoard(y-1,x);
                    UpdateBoard(y,x);
                    przesunieci.push_back(y-1);
                    przesunieci.push_back(x);
                  } else if (board[y][x+1] == '.'){
                    board[y][x+1] = Enemy;
                    board[y][x] = Empty;
                    UpdateBoard(y,x+1);
                    UpdateBoard(y,x);
                    przesunieci.push_back(y);
                    przesunieci.push_back(x+1);
                  } else if (board[y][x-1] == '.'){
                    board[y][x-1] = Enemy;
                    board[y][x] = Empty;
                    UpdateBoard(y,x-1);
                    UpdateBoard(y,x);
                    przesunieci.push_back(y);
                    przesunieci.push_back(x-1);
                  } else {
                    board[y][x] = Enemy;
                    UpdateBoard(y,x);
                    przesunieci.push_back(y);
                    przesunieci.push_back(x);
                  }
                } else {
                  board[y][x] = Enemy;
                  UpdateBoard(y,x);
                }
                ClearDots();
                enemyDelay = 0;
            }
          }

    } else if (enemyDelay < Delay+3)
        enemyDelay++;
}

void Engine::EnemyMove(){ // zrobić lepsze AI, niekoniecznie losowe
    vector <int> przesunieci;
    bool czyBreak = false;
    if (enemyDelay > 7){
        for (int y=0;y<sizeY;y++)
            for (int x=0;x<sizeX;x++){
                int kierunek = rand()%4 + 1;
                if (board[y][x] == Enemy){
                    if (przesunieci.size() >= 2)
                        for (int i=0; i < przesunieci.size()/2; i++)
                            if (y == przesunieci[i*2] && x == przesunieci[i*2 + 1]){ //żeby nie przesuwał po raz drugi tego samego
                                czyBreak = true;
                                break;
                            }
                    if (czyBreak == true){
                        continue;
                    }

                    if (board[y][x+1] == Empty && kierunek == 1){ //prawo (puste)
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        board[y][x+1] = Enemy;
                        UpdateBoard(y, x+1);
                        enemyDelay = 0;
                        przesunieci.push_back(y);
                        przesunieci.push_back(x+1);
                    } else if (board[y][x-1] == Empty && kierunek == 2){ //lewo (puste)
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        board[y][x-1] = Enemy;
                        UpdateBoard(y, x-1);
                        enemyDelay = 0;
                        przesunieci.push_back(y);
                        przesunieci.push_back(x-1);
                    } else if (board[y+1][x] == Empty && kierunek == 3){ // dół (puste)
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        board[y+1][x] = Enemy;
                        UpdateBoard(y+1, x);
                        enemyDelay = 0;
                        przesunieci.push_back(y+1);
                        przesunieci.push_back(x);
                    } else if (board[y-1][x] == Empty && kierunek == 4){ //góra (puste)
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        board[y-1][x] = Enemy;
                        UpdateBoard(y-1, x);
                        enemyDelay = 0;
                        przesunieci.push_back(y-1);
                        przesunieci.push_back(x);
                    } else if (board[y][x+1] != Empty && kierunek == 1 && board[y][x-1] == Empty){ //lewo gdy w prawo nie można
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        board[y][x-1] = Enemy;
                        UpdateBoard(y, x-1);
                        enemyDelay = 0;
                        przesunieci.push_back(y);
                        przesunieci.push_back(x-1);
                    } else if (board[y][x-1] != Empty && kierunek == 2 && board[y][x+1] == Empty){ //prawo gdy w lewo nie można
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        board[y][x+1] = Enemy;
                        UpdateBoard(y, x+1);
                        enemyDelay = 0;
                        przesunieci.push_back(y);
                        przesunieci.push_back(x+1);
                    } else if (board[y+1][x] != Empty && kierunek == 3 && board[y-1][x] == Empty){ //góra, gdy w dół nie można
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        board[y-1][x] = Enemy;
                        UpdateBoard(y-1, x);
                        enemyDelay = 0;
                        przesunieci.push_back(y-1);
                        przesunieci.push_back(x);
                    } else if (board[y-1][x] != Empty && kierunek == 4 && board[y+1][x] == Empty){ //dół, gdy w górę nie można
                        board[y][x] = Empty;
                        UpdateBoard(y, x);
                        board[y+1][x] = Enemy;
                        UpdateBoard(y+1, x);
                        enemyDelay = 0;
                        przesunieci.push_back(y+1);
                        przesunieci.push_back(x);
                    }

                }
                if (czyBreak == true){
                    czyBreak = false;
                    continue;
                }
            }
    } else if (enemyDelay < 10) enemyDelay++;
}
