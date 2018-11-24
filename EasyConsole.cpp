#include <ncurses.h>
#include <iostream>

class EasyConsole{
public:
    void ConsoleInit(){
        setlocale(LC_ALL, ""); // ustawienie kodowania na UTF-8
        initscr(); //inicjacja ekranu konsoli
        noecho(); // nie wyświetla znaku po naciśnięciu klawisza (getch())
        keypad(stdscr, true); //oczytuje wszystkie znaki
    }
    
    void ColorInit() {
        start_color();
        use_default_colors();
    }
    
    void Color(int col){
        //inicjacja kolorów
        init_pair(1, COLOR_WHITE, -1);
        init_pair(2, COLOR_RED, -1);
        init_pair(3, COLOR_GREEN, -1);
        init_pair(4, COLOR_BLUE, -1);
        init_pair(5, COLOR_MAGENTA, -1);
        //ustawianie koloru
        attron(COLOR_PAIR(col));
    }
    void ColorEnd(){
        attroff(COLOR_PAIRS);
    }
};
