#include "Engine.h"

void Engine::BoxMove(int kierunek){ //1 - lewo; 2 - prawo
    if (kierunek == 1){ //Lewo
        for (int x = Player.X; x > 0; x--){
            if (board[Player.Y][x] == Box && board[Player.Y][x-1] == Box) continue;
            else if (board[Player.Y][x] == Box && board[Player.Y][x-1] != Empty) break;
            else if (board[Player.Y][x] == Box && board[Player.Y][x-1] == Empty){
                for (int j = x-1; j < Player.X; j++){
                    board[Player.Y][j] = Box;
                    UpdateBoard(Player.Y, j);
                }
                board[Player.Y][Player.X] = Empty;
                UpdateBoard(Player.Y, Player.X);
                Player.X--;
                DrawPlayer();
                break;
            }
        }
    } else if (kierunek == 2){ //Prawo
        for (int x = Player.X; x < sizeX; x++){
            if (board[Player.Y][x] == Box && board[Player.Y][x+1] == Box) continue;
            else if (board[Player.Y][x] == Box && board[Player.Y][x+1] != Empty) break;
            else if (board[Player.Y][x] == Box && board[Player.Y][x+1] == Empty){
                for (int j = x+1; j > Player.X; j--){
                    board[Player.Y][j] = Box;
                    UpdateBoard(Player.Y, j);
                }
                board[Player.Y][Player.X] = Empty;
                UpdateBoard(Player.Y, Player.X);
                Player.X++;
                DrawPlayer();
                break;
            }
        }
    }
}

char Engine::MovePlayer(){
    nodelay(stdscr, true); //non-block input from getch()
    char keyPressed = getch();
    nodelay(stdscr, false);
    
    if (keyPressed == 3 && Player.Y > 0 && board[Player.Y-1][Player.X] != Wall && board[Player.Y-1][Player.X] != LaserPoz && board[Player.Y-1][Player.X] != LaserPion){ //strzałka w górę
        if (board[Player.Y-1][Player.X] != Box){
            board[Player.Y][Player.X] = Empty;
            UpdateBoard(Player.Y, Player.X);
            
            if (board[Player.Y-1][Player.X] == NextLev)
                return (char)230;
            else if (board[Player.Y-1][Player.X] == Diament)
                Player.Score += 10;
            
            Player.Y--;
            DrawPlayer();
        }
    } else if (keyPressed == 2 && Player.Y < sizeY-1 && board[Player.Y+1][Player.X] != Wall && board[Player.Y+1][Player.X] != LaserPoz && board[Player.Y+1][Player.X] != LaserPion){ //strzałka w dół
        if (board[Player.Y+1][Player.X] != Box){
            board[Player.Y][Player.X] = Empty;
            UpdateBoard(Player.Y, Player.X);
            
            if (board[Player.Y+1][Player.X] == NextLev)
                return (char)230;
            else if (board[Player.Y+1][Player.X] == Diament)
                Player.Score += 10;
            
            Player.Y++;
            DrawPlayer();
        }
    } else if (keyPressed == 5 && Player.X < sizeX-1 && board[Player.Y][Player.X+1] != Wall && board[Player.Y][Player.X+1] != LaserPoz && board[Player.Y][Player.X+1] != LaserPion){ //strzałka w prawo
        if (board[Player.Y][Player.X+1] == Box){
            BoxMove(2);
        } else if (board[Player.Y][Player.X+1] != Box){
            board[Player.Y][Player.X] = Empty;
            UpdateBoard(Player.Y, Player.X);
            
            if (board[Player.Y][Player.X+1] == NextLev)
                return (char)230;
            
            if (board[Player.Y][Player.X+1] == Diament)
                Player.Score += 10;
            
            Player.X++;
            DrawPlayer();
        }
    } else if (keyPressed == 4 && Player.X > 0 && board[Player.Y][Player.X-1] != Wall && board[Player.Y][Player.X-1] != LaserPoz && board[Player.Y][Player.X-1] != LaserPion){ //strzałka w lewo
        if (board[Player.Y][Player.X-1] == Box){
            BoxMove(1);
        } else if (board[Player.Y][Player.X-1] != Box){
            board[Player.Y][Player.X] = Empty;
            UpdateBoard(Player.Y, Player.X);
            
            if (board[Player.Y][Player.X-1] == NextLev)
                return (char)230;
            
            if (board[Player.Y][Player.X-1] == Diament)
                Player.Score += 10;
            
            Player.X--;
            DrawPlayer();
        }
    }
    return keyPressed;
}

void Engine::DrawPlayer(){
    board[Player.Y][Player.X] = Player.Char;
    UpdateBoard(Player.Y,Player.X);
}
