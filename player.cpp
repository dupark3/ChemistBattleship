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

bool player::place_ship(const vector<string>& element_symbols, int ship_number){
    vector<int> ship_atomic_numbers;
    int ship_size = element_symbols.size();

    // convert element symbols of each element in this ship to atomic number
    for (int i = 0; i != ship_size; ++i){
        int atomic_number = atomic_number_from_symbol[element_symbols[i]];
        string electron_config = element_node_array[atomic_number]->get_electron_config();

        // check every ship the player owns for a match. If already exists, do not allow placing this ship
        for (int j = 0; j != number_of_ships; ++j){
            if (ships[j][electron_config] == true){
                return false;
            }
        }

        ship_atomic_numbers.push_back(atomic_number);
    }

    // if the elements are continuous, place those ships and increment num_of_ships
    if (check_if_continuous(ship_atomic_numbers)){
        map<string, bool> ship_map;
        for (int i = 0; i != ship_size; ++i){
            string electron_config = element_node_array[ship_atomic_numbers[i]]->get_electron_config();
            ship_map[electron_config] = true;
        }
        ships.push_back(ship_map);
        ++number_of_ships;
        return true;
    } else { 
        return false;
    }
}

void player::place_ship_randomly(int size_of_ship, int ship_number){
    vector<int> ship_atomic_numbers;

    // Pass a random number between [1,118] as the first element until valid ship position found
    while (ship_atomic_numbers.empty()){
        ship_atomic_numbers = create_continuous_blocks(my_rand(MAX_ELEMENT) + 1, size_of_ship);
    }

    map<string, bool> ship_map;
    for (int i = 0; i != size_of_ship; ++i){
        string electron_config = element_node_array[ship_atomic_numbers[i]]->get_electron_config();
        ship_map[electron_config] = true;
    }

    ships.push_back(ship_map);
    ++number_of_ships;
}


bool player::check_shot(const std::string& electron_config){
    for (int i = 0; i != number_of_ships; ++i){
        if(ships[i].find(electron_config) != ships[i].end() && ships[i][electron_config] == true){
            ships[i][electron_config] = false;
            if (ship_sunk(ships[i])){
                --number_of_ships;
            }
            return true;
        }
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

    // check if all elements in the ship are connected by pointers
    for(int i = 0; i != ship_atomic_numbers.size() - 1; ++i){   
        if (horizontal){
            if (element_node_array[ ship_atomic_numbers[i] ]->get_right_ship() != 
                element_node_array[ ship_atomic_numbers[i + 1] ]){
                return false;
            }    
        } else {
            if (element_node_array[ ship_atomic_numbers[i] ]->get_below_ship() != 
                element_node_array[ ship_atomic_numbers[i + 1] ]){
                return false;
            }
        }
    }

    return true;
}

vector<int> player::create_continuous_blocks(int atomic_number, int size_of_ship){
    bool horizontal = my_rand(2);
    vector<int> ship_atomic_numbers;

    if (horizontal){
        for (int i = 0; i != size_of_ship; ++i){
            element_node* right_ship = element_node_array[atomic_number]->get_right_ship();
            string electron_config = element_node_array[atomic_number]->get_electron_config();

            // if current atomic number doesn't have a right neighbor OR 
            // if this player already has a ship at the current atomic number, return empty vec
            if (!right_ship || !check_unique(electron_config)){
                return { };
            } else {
                ship_atomic_numbers.push_back(atomic_number);
                atomic_number = right_ship->get_atomic_number();
            }
        }
    } else { 
        // vertical ship
        for (int i = 0; i != size_of_ship; ++i){
            element_node* below_ship = element_node_array[atomic_number]->get_below_ship();
            string electron_config = element_node_array[atomic_number]->get_electron_config();

            // if current atomic number doesn't have a down neighbor OR 
            // if this player already has a ship at the current atomic number, return empty vec
            if (!below_ship || !check_unique(electron_config)){
                return { };
            } else {
                ship_atomic_numbers.push_back(atomic_number);
                atomic_number = below_ship->get_atomic_number();
            }
        }
    }

    return ship_atomic_numbers;
}

bool player::ship_sunk(const map<string, bool>& ship){
    for (auto i = ship.begin(); i != ship.end(); ++i){
        if (i->second == true){
            return false;
        }
    }
    return true;
}

bool player::ship_sunk(const string& electron_config) const{
    // iterate through the vector of maps
    for (int i = 0; i != ships.size(); ++i){
        
        // search the map to see if it contains the electron_config
        if (ships[i].find(electron_config) != ships[i].cend()){
            
            // if correct map found, iterate through the map to see if all blocks have been sunk
            for (auto j = ships[i].begin(); j != ships[i].end(); ++j){
                if (j->second == true){
                    return false;
                } 
            }
            
            // if all blocks are false, then ship is sunk
            return true;

        }
    }
    // if electron_config does not exist in ships vector, return false
    return false;
}

bool player::check_unique(const string& electron_config){
    for (int i = 0; i != number_of_ships; ++i){
        if(ships[i].find(electron_config) != ships[i].cend()){
            return false;
        }
    }
    return true;
}


// NON MEMBER FUNCTIONS

int my_rand(int max){
    int random_number;
    int bucket_size = RAND_MAX / max;
    do{
        random_number = rand() / bucket_size;
    } while (random_number > max);

    return random_number;
}

int intelligent_rand(){

}