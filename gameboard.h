#ifndef GUARD_gameboard_h
#define GUARD_gameboard_h

#include <ncurses.h> 

class Display{
public:
    Display() { }
    
    void initialize() { 
        initscr();
        raw();
    }

    void wait() {
        getch();
    }

    void off() { 
        endwin();
    }

};

#endif