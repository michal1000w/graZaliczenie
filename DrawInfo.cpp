#include "Engine.h"

void Engine::DrawInfo(){
    move(sizeY + 2,4);
    eCon.Color(2);
    printw("Zycia: %d     ", Player.Lifes);
    eCon.Color(1);
    printw("Punkty: %d     ", Player.Score);
    eCon.Color(6);
    printw("Poziom: %d   ", Level);
    eCon.ColorEnd();
}

void Engine::DrawLegend(){
    int posY = 1, posX = sizeX + 4;
    move(posY, posX);
    eCon.Color(3);
    printw("Legenda:");
    
    posY += 2;
    move(posY, posX);
    eCon.Color(8);
    printw("%c", Wall); //ściana
    eCon.ColorEnd();
    printw(" - sciana");
    
    posY++;
    move(posY, posX);
    printw("%c", Dirt); //Empty
    printw(" - ziemia");
    
    posY++;
    move(posY, posX);
    eCon.Color(6);
    printw("%c", Player.Char); //Gracz
    eCon.ColorEnd();
    printw(" - gracz");
    
    posY++;
    move(posY, posX);
    eCon.Color(7);
    eCon.BlinkText(true);
    eCon.BoldText(true);
    printw("%c", NextLev); //Next lev
    eCon.ColorEnd();
    eCon.BlinkText(false);
    eCon.BoldText(false);
    printw(" - Nastepny poziom");
    
    posY++;
    move(posY, posX);
    eCon.Color(7);
    eCon.BlinkText(true);
    eCon.BoldText(true);
    printw("%c", key.Char); //Next lev
    eCon.ColorEnd();
    eCon.BlinkText(false);
    eCon.BoldText(false);
    printw(" - Klucz");
    
    posY++;
    move(posY, posX);
    eCon.Color(3);
    printw("%c", Box); //Box
    eCon.ColorEnd();
    printw(" - pudelko");
    posY++;
    move(posY, posX);
    printw("(mozna przesuwac)");
    posY++;
    move(posY, posX);
    printw("(posiadaja grawitacje)");
    
    posY++;
    move(posY, posX);
    eCon.Color(3);
    printw("%c", Drzwi); //Drzwi
    eCon.ColorEnd();
    printw(" - Drzwi");
    
    posY++;
    move(posY, posX);
    printw("%c,%c",LaserPoz, LaserPion);
    printw(" - lasery");
    
    posY++;
    move(posY, posX);
    eCon.Color(2);
    printw("%c,%c",StrzalPoz, StrzalPion);
    eCon.ColorEnd();
    printw(" - strzaly");
    posY++;
    move(posY, posX);
    printw("(zabijaja po");
    posY++;
    move(posY, posX);
    printw("trafieniu gracza)");
    
    posY++;
    move(posY, posX);
    eCon.Color(5);
    printw("%c", Enemy);
    eCon.ColorEnd();
    printw(" - wrogowie");
    
    posY++;
    move(posY, posX);
    eCon.Color(7);
    printw("%c", Diament);
    eCon.ColorEnd();
    printw(" - diamenty");
    posY++;
    move(posY, posX);
    printw("(+10 pkt)");
    
    
    posY += 2;
    move(posY, posX);
    printw("Ekwipunek: ");
    posY++;
    move(posY, posX);
    eCon.Color(3);
    if (key.count > 0){
        printw(" - Klucze: %d", key.count);
    } else
        printw("                   ");
    
}
