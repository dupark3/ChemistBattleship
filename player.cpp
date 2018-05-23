#include <algorithm> // sort()
#include <cstdlib> // rand(), srand(), size_t
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
        int atomic_number = element_symbols[elements[i]];
        if (atomic_number == 0){
            return false;
        }
        ship_atomic_numbers.push_back(atomic_number);
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


void player::place_ship_randomly(int size_of_ship){
    vector<int> random_ship;
    
    srand(time(0));

    while (random_ship.empty()){
        random_ship = continuous_blocks(rand() % 18 + 1, size_of_ship);
    } 

    for (int i = 0; i != size_of_ship; ++i){
        place_ship(random_ship[i]);
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

vector<int> player::continuous_blocks(int first_atomic_number, int size_of_ship){
    bool horizontal = rand() % 2;
    vector<int> random_ship;

    if (horizontal){
        for (int i = 0; i != size_of_ship; ++i){
            if (first_atomic_number + i > MAX_ELEMENT){
                return { };
            }
            random_ship.push_back(first_atomic_number + i);
        }
    } 

    // vertical ship
    else { 
        for (int i = 0; i != size_of_ship; ++i){
            int next_row;
            if (first_atomic_number + i == 1){
                next_row = 2;
            } else if (first_atomic_number >= 2 && first_atomic_number + i <= 10){
                next_row = 8;
            } else {
                return { };
            }
            random_ship.push_back(first_atomic_number);
            first_atomic_number += next_row;
        }
    }

    if (continuous_blocks(random_ship)){
        return random_ship;
    } else {
        return { };
    }
}