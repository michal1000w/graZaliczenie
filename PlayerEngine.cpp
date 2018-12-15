#include "Engine.h"

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
            
            if (board[Player.Y][Player.X+1] == Diament)
                Player.Score += 10;
            
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
