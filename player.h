#ifndef GUARD_player_h
#define GUARD_player_h

#include <map>
#include <string>
#include <vector>

#include "periodic_table.h"

class ship;

class player{
public:
    player() : name(), ships(), number_of_ships(), hits(), misses() { }
    player(std::string s) : name(s), ships(), number_of_ships(0), hits(0), misses(0) { }

    // void place_ship(const std::string&);
    bool place_ship(const std::vector<std::string>&);
    void place_ship_randomly(int);
    void place_ship(int);
    bool check_shot(const std::string&);
    bool check_game_over();
    int ships_left() { return number_of_ships; } 
    
    void hit() { ++hits; }
    void missed() { ++misses; }
    int get_accuracy() { return ((double)hits / (hits + misses)) * 100; }

private:
    std::string name;
    std::map<std::string, bool> ships; // map of electron config to a node of ship info
    int number_of_ships, hits, misses;
    bool check_if_continuous(std::vector<int>&);
    std::vector<int> create_continuous_blocks(int, int);
    
};


// nonmember functions
int my_rand(int);

#endif