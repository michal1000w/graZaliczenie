#include "Engine.h"

void Engine::ReadMapFromFile(const string filename){
    string line;
    int y = 0;

    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        while ( getline (file,line) ){
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

void Engine::LoadMapsInfo(const string filename){
  string line;
  int LevelCount = 0;
  Levels.clear();

  ifstream file;
  file.open(filename);
  if (file.is_open()){
    LevelCount++;
    while (getline (file, line)){
      Levels.push_back(line);
      LevelCount++;
    }
    file.close();
  }
  LastLevel = LevelCount;
}

void Engine::LoadLevel(){
    FillEmpty(); //inicjowanie tablicy zerami
    if (Level > 0)
        ReadMapFromFile(Levels[Level-1]);
    else if (Level == -1)
      ReadMapFromFile("mapy/test1.txt");
}
