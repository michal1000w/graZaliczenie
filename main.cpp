#include <ncurses.h>

int main(){
    initscr();
    printw("Witaj Świecie\n");
    getch();
    endwin();
}
