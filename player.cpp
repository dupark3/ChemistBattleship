#include <cstdlib> // rand()
#include <iostream>

#include "player.h"
#include "answerkey.h"

using namespace std;

// REFACTOR: ability to add multiple ships of varying sizes according to the rules
void player::place_ship(const std::string& element_symbol){
    int atomic_number = atomic_numbers[element_symbol];
    if (atomic_number > 0){
        ships[ electron_configs[atomic_number] ] = new ship(atomic_number, element_symbol);
    }
}

void player::place_ship(int atomic_number){
    if (atomic_number > 0 && atomic_number < 18){
        ships[ electron_configs[atomic_number] ] = new ship(atomic_number, element_symbols[atomic_number]);
    }
}

// REFACTOR: use bucket method to create more random numbers
// REFACTOR: ability to add three 3-block, two 4-block, and one 5-block ships. 
void player::place_ship_randomly(int number_of_blocks){
    for (int i = 0; i != number_of_blocks; ++i){
        place_ship(rand() % 18 + 1);
    }    
}

bool player::check_shot(const std::string& electron_config, std::string& element_symbol){
    if(ships[electron_config]){
        if (ships[electron_config]->status){
            ships[electron_config]->status = false;
            element_symbol = ships[electron_config]->element_symbol;
            return true;
        }
    }
    return false; 
}