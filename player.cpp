#include <algorithm> // sort()
#include <cstdlib> // rand()

#include "periodic_table.h"
#include "player.h"

using namespace std;

/*bool player::place_ship(const std::string& element_symbol){
    return place_ship(atomic_number_from_symbol[element_symbol]);
}*/

bool player::place_ship(const vector<string>& element_symbols){
    vector<int> ship_atomic_numbers;
    int ship_size = element_symbols.size();

    // convert element symbols of each element in this ship to atomic number
    for (int i = 0; i != ship_size; ++i){
        int atomic_number = atomic_number_from_symbol[element_symbols[i]];
        string electron_config = element_node_vector[atomic_number]->get_electron_config();

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
            string electron_config = element_node_vector[ship_atomic_numbers[i]]->get_electron_config();
            ship_map[electron_config] = true;
        }
        ships.push_back(ship_map);
        ++number_of_ships;
        return true;
    } else { 
        return false;
    }
}

void player::place_ship_randomly(int size_of_ship){
    vector<int> ship_atomic_numbers;

    // Pass a random number between [1,118] as the first element until valid ship position found
    while (ship_atomic_numbers.empty()){
        ship_atomic_numbers = create_continuous_blocks(my_rand(MAX_ELEMENT) + 1, size_of_ship);
    }

    map<string, bool> ship_map;
    for (int i = 0; i != size_of_ship; ++i){
        string electron_config = element_node_vector[ship_atomic_numbers[i]]->get_electron_config();
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

    if (element_node_vector[ship_atomic_numbers[0]]->get_right_ship() == 
        element_node_vector[ship_atomic_numbers[1]]){
        horizontal = true;
    }

    // check if all elements in the ship are connected by pointers
    for(int i = 0; i != ship_atomic_numbers.size() - 1; ++i){   
        if (horizontal){
            if (element_node_vector[ ship_atomic_numbers[i] ]->get_right_ship() != 
                element_node_vector[ ship_atomic_numbers[i + 1] ]){
                return false;
            }    
        } else {
            if (element_node_vector[ ship_atomic_numbers[i] ]->get_below_ship() != 
                element_node_vector[ ship_atomic_numbers[i + 1] ]){
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
            element_node* right_ship = element_node_vector[atomic_number]->get_right_ship();
            string electron_config = element_node_vector[atomic_number]->get_electron_config();

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
            element_node* below_ship = element_node_vector[atomic_number]->get_below_ship();
            string electron_config = element_node_vector[atomic_number]->get_electron_config();

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


vector< pair<string, bool> > player::check_X_bomb(const std::string& electron_config){

    int atomic_number = atomic_number_from_config[electron_config];
    element_node* center_element = element_node_vector[atomic_number];
    vector< pair<string, bool> > X_bomb_results;

    // check the top two corners and push_back into return vector
    if(center_element->above_ship){
        if (center_element->above_ship->left_ship){
            string corner_electron_config = center_element->above_ship->left_ship->get_electron_config();
            
            // true if shot made, false if missed
            if (check_shot(corner_electron_config)){
                X_bomb_results.push_back( {corner_electron_config, true} );
            } else {
                X_bomb_results.push_back( {corner_electron_config, false} );
            }
        }

        if (center_element->above_ship->right_ship){
            string corner_electron_config = center_element->above_ship->right_ship->get_electron_config();
            if (check_shot(corner_electron_config)){
                X_bomb_results.push_back( {corner_electron_config, true} );
            } else {
                X_bomb_results.push_back( {corner_electron_config, false} );
            }
        }
    }

    // check bottom two corners
    if (center_element->below_ship){
        if (center_element->below_ship->left_ship){
            string corner_electron_config = center_element->below_ship->left_ship->get_electron_config();
            if (check_shot(corner_electron_config)){
                X_bomb_results.push_back( {corner_electron_config, true} );
            } else {
                X_bomb_results.push_back( {corner_electron_config, false} );
            }
        }
        if (center_element->below_ship->right_ship){
            string corner_electron_config = center_element->below_ship->right_ship->get_electron_config();
            if (check_shot(corner_electron_config)){
                X_bomb_results.push_back( {corner_electron_config, true} );
            } else {
                X_bomb_results.push_back( {corner_electron_config, false} );
            }
        }
    }

    return X_bomb_results;
    
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

string convert_to_long_form(const string& short_hand_config){
    string long_hand_config;
    
    // if short_hand is smaller than 4, it can't be a valid config. prevent seg fault by exiting.
    if (short_hand_config.size() < 4){
        return short_hand_config;
    }

    // if the first four letters are a noble gas in brackets, convert it to its config in long form
    if (short_hand_config.substr(0, 4) == "[He]"){
        long_hand_config = "1s2";
    } else if (short_hand_config.substr(0, 4) == "[Ne]"){
        long_hand_config = "1s2.2s2.2p6";
    } else if (short_hand_config.substr(0, 4) == "[Ar]"){
        long_hand_config = "1s2.2s2.2p6.3s2.3p6";
    } else if (short_hand_config.substr(0, 4) == "[Kr]"){
        long_hand_config = "1s2.2s2.2p6.3s2.3p6.4s2.3d10.4p6";
    } else if (short_hand_config.substr(0, 4) == "[Xe]"){
        long_hand_config = "1s2.2s2.2p6.3s2.3p6.4s2.3d10.4p6.5s2.4d10.5p6";
    } else if (short_hand_config.substr(0, 4) == "[Rn]"){
        long_hand_config = "1s2.2s2.2p6.3s2.3p6.4s2.3d10.4p6.5s2.4d10.5p6.6s2.4f14.5d10.6p6";
    } else if (short_hand_config.substr(0, 4) == "[Og]"){
        long_hand_config = "1s2.2s2.2p6.3s2.3p6.4s2.3d10.4p6.5s2.4d10.5p6.6s2.4f14.5d10.6p6.7s2.5f14.6d10.7p6";
    } else {
        return short_hand_config;
    }
    
    // if there are more than 4 letters, it must have trailing config after noble gas [??]
    if (short_hand_config.size() > 4){
        long_hand_config = long_hand_config + "." + short_hand_config.substr(4);
    }

    return long_hand_config;
}