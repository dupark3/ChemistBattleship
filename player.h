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
    void place_ship(const std::vector<std::string>&);
    void place_ship_randomly(int);
    bool check_shot(const std::string&);
    bool check_game_over();
    int ships_left() { return number_of_ships; }
    

private:
    std::string name;
    std::map<std::string, bool> ships; // map of electron config to a node of ship info
    int number_of_ships;
    bool continuous_blocks(std::vector<int>&);
};

class element_node{
public:
private:
    std::string element_symbol;
    std::string electron_configuration;
    
    // true if player has a ship on this element block
    bool player1_ship;
    bool player2_ship;

    // pointer to the nods on the right and below this node. 
    // allows us to check if two nodes can be part of one ship. 
    element_node* valid_right_ship;
    element_node* valid_down_ship;
};


class periodic_table{
public:
private:
    // array index 0 is left empty in order to match the index with the atomic number
    element_node* element_node_array[MAX_ELEMENT + 1];
};


#endif