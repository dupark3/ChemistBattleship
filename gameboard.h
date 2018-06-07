#ifndef GUARD_gameboard_h
#define GUARD_gameboard_h

#include <string>
#include <vector>

class display_driver{
    public:
        display_driver();

        void print_periodic_tables();
        void place_boat(int);
        void enemy_shot(int, bool);
        void player_shot(int, bool);
    private:
        std::vector<std::string> symbols;
        std::vector<char*> boat_status;
        std::vector<char*> shot_status;
};

#endif