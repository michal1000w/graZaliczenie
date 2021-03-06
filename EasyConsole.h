#ifndef EasyConsole_h
#define EasyConsole_h

#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <time.h>

class EasyConsole{
public:
    void ConsoleInit();
    void ColorInit();
    void Color(int);
    void ColorEnd();
    void BoldText(bool);
    void UnderlineText(bool);
    void HideCursor(bool);
    void BlinkText(bool);
    void ClearScr();
    void Sleep(float);
};

#endif
