#ifndef GUARD_gameboard_h
#define GUARD_gameboard_h

#include <ncurses.h> 
// #include <locale.h>

class Game{
public:
    Game() { }
    
    void initialize_window() { 
        // setlocale(LC_ALL,"");
        initscr();
        raw();
    }

    void wait() {
        getch();
    }

    void close_window() { 
        endwin();
    }

    void print_periodic_tables();
    void set_up_player();
    void set_up_ships(int, int);
    void set_up_AI();

};

void print_periodic_tables();

#endif