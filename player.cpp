#include <cstdlib> // rand(), size_t
#include <iostream>

#include "player.h"
#include "answerkey.h"

using namespace std;

// REFACTOR: ability to add multiple ships of varying sizes according to the rules
void player::place_ship(const std::string& element_symbol){
    int atomic_number = atomic_numbers[element_symbol];
    if (atomic_number > 0){
        ships[ electron_configs[atomic_number] ] = true;
    }
    ++number_of_ships;
}

void player::place_ship(int atomic_number){
    if (atomic_number > 0 && atomic_number < 18){
        ships[ electron_configs[atomic_number] ] = true;
    }
    ++number_of_ships;
}

// REFACTOR: use bucket method to create more random numbers
// REFACTOR: ability to add three 3-block, two 4-block, and one 5-block ships. 
void player::place_ship_randomly(int number_of_blocks){
    for (int i = 0; i != number_of_blocks; ++i){
        place_ship(rand() % 18 + 1);
    }    
}

bool player::check_shot(const std::string& electron_config){
    if(ships[electron_config]){
        ships[electron_config] = false;
        --number_of_ships;
        return true;        
    }
    return false; 
}

bool player::check_game_over(){
    return number_of_ships == 0;
}