#ifndef GUARD_player_h
#define GUARD_player_h

#include <map>
#include <string>
#include <vector>
#include <utility> // pair used in returning hit/miss info on 4 elements after check_X_bomb()

#include "periodic_table.h"

// forward declarations
class ship;

class player{
friend class AI;
public:
    player() : name(), ships(), number_of_ships(0), 
               hits(0), misses(0), correct_guesses(0), X_bombs(0) { }
    player(std::string s) : name(s), ships(), number_of_ships(0), 
                            hits(0), misses(0), 
                            correct_guesses(0), X_bombs(0), 
                            consecutive_correct_configs(0) { }
    
    // Place ship with vector of configs or with size of ship and ship_number
    bool place_ship(const std::vector<std::string>&);
    void place_ship_randomly(int);
    
    bool check_shot(const std::string&);
    bool check_game_over();

    bool ship_sunk(const std::map<std::string, bool>&);
    bool ship_sunk(const std::string&) const;
    int ships_left() const { return number_of_ships; } 
    

    // accuracy and short_hand config support member functions
    void hit() { ++hits; ++consecutive_correct_configs;}
    void missed() { ++misses; ++consecutive_correct_configs; }
    void misfire() { ++misses; consecutive_correct_configs = 0; }
    int get_accuracy() const { return ((double)hits / (hits + misses)) * 100; }
    int get_consecutive_correct_configs() { return consecutive_correct_configs; }
    bool short_form_allowed() { return consecutive_correct_configs >= 3; }
    
    // X_bomb support member functions
    void correct_guess() { ++correct_guesses; }
    int get_correct_guesses() const { return correct_guesses; }
    void reset_guesses() { correct_guesses = 0; }
    void earn_X_bomb() { ++X_bombs; }
    void lose_X_bomb() { --X_bombs; }
    std::vector< std::pair<std::string, bool> > check_X_bomb(const std::string&);
    int get_X_bomb() { return X_bombs; }

protected:
    std::string name;
    std::vector< std::map<std::string, bool> > ships; // map of electron config to a node of ship info
    int number_of_ships;
    int hits, misses;
    int correct_guesses, X_bombs;

    bool check_if_continuous(std::vector<int>&);
    std::vector<int> create_continuous_blocks(int, int);
    bool check_unique(const std::string&);
    
    int consecutive_correct_configs;

};


// nonmember functions
int my_rand(int);
std::string convert_to_long_form(const std::string&);

#endif