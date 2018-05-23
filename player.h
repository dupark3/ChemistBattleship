#ifndef GUARD_player_h
#define GUARD_player_h

#include <map>
#include <string>
#include <vector>

#include "answerkey.h"

class ship;

class player{
public:
    player() : name(), ships() { }
    player(std::string s) : name(s), ships(), number_of_ships(0) { }

    void place_ship(const std::string&);
    void place_ship(int);
    bool place_ship(const std::vector<std::string>&);
    void place_ship_randomly(int);
    bool check_shot(const std::string&);
    bool check_game_over();
    int ships_left() { return number_of_ships; }
    

private:
    std::string name;
    std::map<std::string, bool> ships; // map of electron config to a node of ship info
    int number_of_ships;
    bool continuous_blocks(std::vector<int>&);
    std::vector<int> continuous_blocks(int, int);
};

#endif