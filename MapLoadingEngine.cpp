#include "Engine.h"

void Engine::ReadMapFromFile(const string filename){
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
                    PoczPlayer.Y = y;
                    PoczPlayer.X = i;
                }
            }
            y++;
        }
        file.close();
    }
}

void Engine::LoadLevel(){
    FillEmpty(); //inicjowanie tablicy zerami
    if (Level == 1)
        ReadMapFromFile("mapy/map1.txt");
    else if (Level == 2)
        ReadMapFromFile("mapy/map2.txt");
}
