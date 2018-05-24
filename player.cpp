#include <algorithm> // sort()
#include <cstdlib> // rand()
#include <iostream>
#include <vector>

#include "periodic_table.h"
#include "player.h"

using namespace std;

/*bool player::place_ship(const std::string& element_symbol){
    return place_ship(atomic_number_from_symbol[element_symbol]);
}*/

bool player::place_ship(const vector<string>& element_symbols){
    vector<int> ship_atomic_numbers;
    int ship_size = element_symbols.size();

    // convert element symbols to atomic number and store in a vector
    for (int i = 0; i != ship_size; ++i){
        int atomic_number = atomic_number_from_symbol[element_symbols[i]];
        ship_atomic_numbers.push_back(atomic_number);
        
        // do not allow players to place ships where they already have one
        if (ships[element_node_array[atomic_number]->get_electron_config()] == true){
            return false;
        }
    }

    // if the blocks are continuous, place those ships. if not, return false. 
    if (check_if_continuous(ship_atomic_numbers)){
        for (int i = 0; i != ship_size; ++i){
            place_ship(ship_atomic_numbers[i]);
        }
        return true;
    } else { 
        return false;
    }
}

void player::place_ship_randomly(int size_of_ship){
    vector<int> ship_atomic_numbers;

    // Pass a random number between [1,118] as the first element until valid ship position found
    while (ship_atomic_numbers.empty()){
        ship_atomic_numbers = create_continuous_blocks(rand() % MAX_ELEMENT + 1, size_of_ship);
    }

    for (int i = 0; i != size_of_ship; ++i){
        place_ship(ship_atomic_numbers[i]);
    }
}

void player::place_ship(int atomic_number){
    if (atomic_number >= 1 && atomic_number <= MAX_ELEMENT){
        ships[ element_node_array[atomic_number]->get_electron_config() ] = true;
        ++number_of_ships;
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

bool player::check_if_continuous(std::vector<int>& ship_atomic_numbers){
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

vector<int> player::create_continuous_blocks(int atomic_number, int size_of_ship){
    bool horizontal = rand() % 2;
    vector<int> ship_atomic_numbers;

    if (horizontal){
        for (int i = 0; i != size_of_ship; ++i){
            element_node* right_ship = element_node_array[atomic_number]->get_right_ship();

            // if current atomic number doesn't have a right neighbor OR 
            // if this player already has a ship at the current atomic number, return empty vec
            if (!right_ship || 
                ships[ element_node_array[atomic_number]->get_electron_config() ] == true){
                return { };
            } else {
                ship_atomic_numbers.push_back(atomic_number);
                atomic_number = right_ship->get_atomic_number();
            }
        }
    } else { 
        // vertical ship
        for (int i = 0; i != size_of_ship; ++i){
            element_node* down_ship = element_node_array[atomic_number]->get_down_ship();

            // if current atomic number doesn't have a down neighbor OR 
            // if this player already has a ship at the current atomic number, return empty vec
            if (!down_ship ||
                ships[ element_node_array[atomic_number]->get_electron_config() ] == true){
                return { };
            } else {
                ship_atomic_numbers.push_back(atomic_number);
                atomic_number = down_ship->get_atomic_number();
            }
        }
    }

    return ship_atomic_numbers;
}