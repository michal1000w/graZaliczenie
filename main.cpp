#include "Engine.cpp"

int main(){
    EasyConsole eCon;
    eCon.ConsoleInit();
    eCon.ColorInit();
    
    Engine engine;
    engine.Init();
    engine.MainLoop();
    
    getch();
    endwin();
}
