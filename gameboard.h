#ifndef GUARD_gameboard_h
#define GUARD_gameboard_h

#include <ncurses.h> 
#include <locale.h>

class Display{
public:
    Display() { }
    
    void initialize() { 
        setlocale(LC_ALL,"");
        initscr();
        raw();
    }

    void wait() {
        getch();
    }

    void off() { 
        endwin();
    }

    void print_periodic_tables();

};

#endif