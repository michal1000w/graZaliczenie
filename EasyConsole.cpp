#include "EasyConsole.h"

void EasyConsole::ConsoleInit(){
        setlocale(LC_ALL, ""); // ustawienie kodowania na polskie
        initscr(); //inicjacja ekranu konsoli
        noecho(); // nie wyświetla znaku po naciśnięciu klawisza (getch())
        keypad(stdscr, true); //oczytuje wszystkie znaki
        HideCursor(true); //ukrywanie kursora
        srand(time(NULL)); //resetowanie czasu
}
    
void EasyConsole::ColorInit() {
        start_color();
        use_default_colors();
    }
    
void EasyConsole::Color(int col){
        //inicjacja kolorów
        init_pair(1, COLOR_WHITE, -1);
        init_pair(2, COLOR_RED, -1);
        init_pair(3, COLOR_GREEN, -1);
        init_pair(4, COLOR_BLUE, -1);
        init_pair(5, COLOR_MAGENTA, -1);
        init_pair(6, COLOR_YELLOW, -1);
        init_pair(7, COLOR_CYAN, -1);
        init_pair(8, COLOR_WHITE, COLOR_WHITE);
        //ustawianie koloru
        attron(COLOR_PAIR(col));
    }
    
void EasyConsole::ColorEnd(){
        attroff(COLOR_PAIRS);
    }
    
void EasyConsole::BoldText(bool a){
        if (a == true)
            attron(A_BOLD);
        else
            attroff(A_BOLD);
    }
    
void EasyConsole::UnderlineText(bool a){
        if (a == true)
            attron(A_UNDERLINE);
        else
            attroff(A_UNDERLINE);
    }
    
void EasyConsole::HideCursor(bool a){
        if (a == true)
            curs_set(0);
        else
            curs_set(1);
    }
    
void EasyConsole::BlinkText(bool a){
        if (a == true)
            attron(A_BLINK);
        else
            attroff(A_BLINK);
    }

void EasyConsole::ClearScr(){
    clear();
    refresh();
}

void EasyConsole::Sleep(float time){
    usleep(time * 1000);
}
