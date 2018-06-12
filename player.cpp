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

        if(!check_unique(electron_config)){
            return false;
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

bool player::check_shot(const std::string& electron_config){
    int size_of_vector = ships.size();
    
    for (int i = 0; i != size_of_vector; ++i){
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
        if (ships[i].find(electron_config) != ships[i].end()){
            // on the correct map, see if any element still remains
            for (auto j = ships[i].begin(); j != ships[i].end(); ++j){
                if (j->second == true){
                    return false;
                } 
            }
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

int player::get_accuracy() const { 
 if (hits + misses == 0){
    return 0;
 } else {
    return ((double)hits / (hits + misses)) * 100; 
 }
 
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
