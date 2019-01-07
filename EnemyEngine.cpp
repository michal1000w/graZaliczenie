#include "Engine.h"

///////////////////////AI v3

bool Engine::InitNodes(){
	nodes = new sNode[sizeY * sizeX];
	for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++){
			nodes[y * sizeX + x].x = x;
			nodes[y * sizeX + x].y = y;
			nodes[y * sizeX + x].Obstacle = false;
			nodes[y * sizeX + x].parent = nullptr;
			nodes[y * sizeX + x].Visited = false;
		}
	//Create connections
	for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++){
			if (y>0)
				nodes[y * sizeX + x].Neighbours.push_back(&nodes[(y-1)*sizeX+(x+0)]);
			if (y<sizeY-1)
				nodes[y * sizeX + x].Neighbours.push_back(&nodes[(y+1)*sizeX+(x+0)]);
			if (x>0)
				nodes[y * sizeX + x].Neighbours.push_back(&nodes[(y+0)*sizeX+(x-1)]);
			if(x<sizeX-1)
				nodes[y * sizeX + x].Neighbours.push_back(&nodes[(y+0)*sizeX+(x+1)]);
		}
	return true;
}

void Engine::ReloadNodes(){
  for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++){
			nodes[y * sizeX + x].x = x;
			nodes[y * sizeX + x].y = y;
			nodes[y * sizeX + x].Obstacle = false;
			nodes[y * sizeX + x].parent = nullptr;
			nodes[y * sizeX + x].Visited = false;
      nodes[y * sizeX + x].Neighbours.clear();
		}
	//Create connections
	for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++){
			if (y>0)
				nodes[y * sizeX + x].Neighbours.push_back(&nodes[(y-1)*sizeX+(x+0)]);
			if (y<sizeY-1)
				nodes[y * sizeX + x].Neighbours.push_back(&nodes[(y+1)*sizeX+(x+0)]);
			if (x>0)
				nodes[y * sizeX + x].Neighbours.push_back(&nodes[(y+0)*sizeX+(x-1)]);
			if(x<sizeX-1)
				nodes[y * sizeX + x].Neighbours.push_back(&nodes[(y+0)*sizeX+(x+1)]);
		}
}

void Engine::SetupNodes(){
	for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++){
			if (board[y][x] == Wall || board[y][x] == Box || board[y][x] == Dirt || board[y][x] == Diament || board[y][x] == Drzwi || board[y][x] == LaserPoz || board[y][x] == LaserPion || board[y][x] == key.Char || board[y][x] == NextLev) nodes[y * sizeX + x].Obstacle = true;
			//else if (board[y][x] == Enemy) nodeStart = &nodes[y * sizeX + x];
			else if (board[y][x] == Player.Char) nodeEnd = &nodes[y * sizeX + x];
      else nodes[y * sizeX + x].Obstacle = false;
		}
}

bool Engine::Solve_AStar(){
	for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++){
			nodes[y*sizeX+x].Visited = false;
			nodes[y*sizeX+x].GlobalGoal = INFINITY;
			nodes[y*sizeX+x].LocalGoal = INFINITY;
			nodes[y*sizeX+x].parent = nullptr;
		}
	auto distance = [](sNode *a, sNode *b){
		return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
	};
	auto heuristic = [distance](sNode *a, sNode *b){
		return distance(a,b);
	};

	sNode *Current = nodeStart;
	nodeStart->LocalGoal = 0.0f;
	nodeStart->GlobalGoal = heuristic(nodeStart, nodeEnd);

	list<sNode*> NotTestedNodes;
	NotTestedNodes.push_back(nodeStart);

	while (!NotTestedNodes.empty() && Current != nodeEnd){
		NotTestedNodes.sort([](const sNode* lhs, const sNode* rhs){ return lhs->GlobalGoal < rhs->GlobalGoal; } );

		while(!NotTestedNodes.empty() && NotTestedNodes.front()->Visited)
			NotTestedNodes.pop_front();

		if (NotTestedNodes.empty()) break;

		Current = NotTestedNodes.front();
		Current->Visited = true;

		for (auto Neighbour : Current->Neighbours){
			if (!Neighbour->Visited && Neighbour->Obstacle == false)
				NotTestedNodes.push_back(Neighbour);

			float PossiblyLowerGoal = Current->LocalGoal + distance(Current, Neighbour);

			if (PossiblyLowerGoal < Neighbour->LocalGoal){
				Neighbour->parent = Current;
				Neighbour->LocalGoal = PossiblyLowerGoal;

				Neighbour->GlobalGoal = Neighbour->LocalGoal + heuristic(Neighbour, nodeEnd);
			}
		}
	}
	return true;
}

bool Engine::DrawShortestPath(bool visible){
  bool PathExists = false;
	if (nodeEnd != nullptr) {
    PathExists = true;
		sNode *p = nodeEnd;
		while (p->parent != nullptr) {
      if (board[p->y][p->x] != Player.Char && board[p->y][p->x] != Enemy){
			   board[p->y][p->x] = '.';
         if (visible) UpdateBoard(p->y,p->x);
       }
			p = p->parent;
		}
	}
  return PathExists;
}

void Engine::EnemyMove3(int Delay){
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
                //InitNodes();
                ReloadNodes();
                SetupNodes();
                nodeStart = &nodes[y * sizeX + x];
                Solve_AStar();
                if (DrawShortestPath(true)){
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



bool Engine::deadEnd(int y, int x){
  if (y == start.y && x == start.x)
    return (board[y][x] != Empty && board[y][x] != Enemy) || board[y][x] == '.';
  else
    return board[y][x] != Empty || board[y][x] == '.';
}

void Engine::ClearDots(){
  for (int y = 0; y < sizeY; y++)
    for (int x = 0; x < sizeX; x++){
      if (board[y][x] == '.') board[y][x] = Empty;
      //UpdateBoard(y,x);
    }
}

bool Engine::SolveM(int y, int x){
  //return true;
  if (board[y][x] == Player.Char) return true;
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
