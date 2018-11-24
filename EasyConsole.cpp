#include <ncurses.h>
#include <iostream>

class EasyConsole{
public:
    void ConsoleInit(){
        setlocale(LC_ALL, ""); // ustawienie kodowania na polskie
        initscr(); //inicjacja ekranu konsoli
        noecho(); // nie wyświetla znaku po naciśnięciu klawisza (getch())
        keypad(stdscr, true); //oczytuje wszystkie znaki
        HideCursor(true); //ukrywanie kursora
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
    
    void BoldText(bool a){
        if (a == true)
            attron(A_BOLD);
        else
            attroff(A_BOLD);
    }
    
    void UnderlineText(bool a){
        if (a == true)
            attron(A_UNDERLINE);
        else
            attroff(A_UNDERLINE);
    }
    
    void HideCursor(bool a){
        if (a == true)
            curs_set(0);
        else
            curs_set(1);
    }
};
