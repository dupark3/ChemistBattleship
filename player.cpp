#include <algorithm> // sort()
#include <cstdlib> // rand(), size_t
#include <iostream>
#include <vector>

#include "answerkey.h"
#include "player.h"

using namespace std;

void player::place_ship(const std::string& element_symbol){
    int atomic_number = element_symbols[element_symbol];
    if (atomic_number > 0){
        ships[ element_node_array[atomic_number]->get_electron_config() ] = true;
        ++number_of_ships;
    }
}

bool player::place_ship(const vector<string>& elements){
    vector<int> ship_atomic_numbers;

    for (int i = 0; i != elements.size(); ++i){
        ship_atomic_numbers.push_back(element_symbols[elements[i]]);
    }

    if (continuous_blocks(ship_atomic_numbers)){
        for (int i = 0; i != ship_atomic_numbers.size(); ++i){
            ships[ element_node_array[ship_atomic_numbers[i]]->get_electron_config() ] = true;
            ++number_of_ships;
        }
        return true;
    } else {
        return false;
    }
}

void player::place_ship(int atomic_number){
    if (atomic_number > 0 && atomic_number < 18){
        ships[ element_node_array[atomic_number]->get_electron_config() ] = true;
        ++number_of_ships;
    }
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

bool player::continuous_blocks(std::vector<int>& ship_atomic_numbers){
    if (ship_atomic_numbers.size() <= 1){
        return true;
    } 
    
    // find out if horizontal or vertical ship
    bool horizontal = false;
    sort(ship_atomic_numbers.begin(), ship_atomic_numbers.end());
    if (ship_atomic_numbers[1] - ship_atomic_numbers[0] == 1){
        horizontal = true;
    }

    for(int i = 0; i != ship_atomic_numbers.size() - 1; ++i){   
        if (horizontal){
            if (element_node_array[ ship_atomic_numbers[i] ]->get_right_ship() != 
                element_node_array[ ship_atomic_numbers[i + 1] ]){
                return false;
            }    
        } else {
            if (element_node_array[ ship_atomic_numbers[i] ]->get_down_ship() != 
                element_node_array[ ship_atomic_numbers[i + 1] ]){
                return false;
            }
        }
    }

    return true;
}