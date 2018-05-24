#include <algorithm> // sort()
#include <cstdlib> // rand()
#include <iostream>
#include <vector>

#include "periodic_table.h"
#include "player.h"

using namespace std;

void player::place_ship(const std::string& element_symbol){
    place_ship(element_symbols[element_symbol]);
}

bool player::place_ship(const vector<string>& elements){
    vector<int> ship_atomic_numbers;

    // convert element symbols to atomic number and store in a vector
    for (int i = 0; i != elements.size(); ++i){
        int atomic_number = element_symbols[elements[i]];
        ship_atomic_numbers.push_back(atomic_number);
    }

    // if the blocks are continuous, place those ships. if not, return false. 
    if (continuous_blocks(ship_atomic_numbers)){
        for (int i = 0; i != ship_atomic_numbers.size(); ++i){
            place_ship(ship_atomic_numbers[i]);
        }
        return true;
    } else { 
        return false;
    }
}

void player::place_ship(int atomic_number){
    if (atomic_number >= 1 && atomic_number <= MAX_ELEMENT){
        ships[ element_node_array[atomic_number]->get_electron_config() ] = true;
        ++number_of_ships;
    }
}


void player::place_ship_randomly(int size_of_ship){
    vector<int> ship_atomic_numbers;

    // Pass a random number between [1,118] as the first element until valid ship position found
    while (ship_atomic_numbers.empty()){
        ship_atomic_numbers = continuous_blocks(rand() % MAX_ELEMENT + 1, size_of_ship);
    }

    for (int i = 0; i != size_of_ship; ++i){
        place_ship(ship_atomic_numbers[i]);
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
    if (element_node_array[ship_atomic_numbers[0]]->get_right_ship() == 
        element_node_array[ship_atomic_numbers[1]]){
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

vector<int> player::continuous_blocks(int atomic_number, int size_of_ship){
    int horizontal = rand() % 2;
    vector<int> random_ship;

    if (horizontal == 0){
        for (int i = 0; i != size_of_ship; ++i){
            element_node* right_ship = element_node_array[atomic_number]->get_right_ship();

            if (!right_ship){
                return { };
            } else {
                random_ship.push_back(atomic_number);
                atomic_number = right_ship->get_atomic_number();
            }
            
        }
    } else { 
        // vertical ship
        for (int i = 0; i != size_of_ship; ++i){
            element_node* down_ship = element_node_array[atomic_number]->get_down_ship();

            if (!down_ship){
                return { };
            } else {
                random_ship.push_back(atomic_number);
                atomic_number = down_ship->get_atomic_number();
            }
        }
    }

    if (continuous_blocks(random_ship)){
        return random_ship;
    } else {
        return { };
    }
}