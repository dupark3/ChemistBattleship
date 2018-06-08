#include <iostream>
#include <map>
#include <string>

#include "AI.h" 
#include "player.h" // player object passed sometimes to check for sunk ships

using namespace std;


void AI::place_ship_randomly(int size_of_ship){
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


vector<int> AI::create_continuous_blocks(int atomic_number, int size_of_ship){
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

string AI::take_educated_shot(){
    int max_possibility = 0;
    vector<element_node*> best_elements_to_shoot;

    for (int i = 1; i != 119; ++i){
        if (AI_element_node_vector[i]->possibilities > max_possibility && AI_element_node_vector[i]->status == 0){
            max_possibility = AI_element_node_vector[i]->possibilities;
            best_elements_to_shoot.clear();
            best_elements_to_shoot.push_back(AI_element_node_vector[i]);
        } else if (AI_element_node_vector[i]->possibilities == max_possibility) {
            best_elements_to_shoot.push_back(AI_element_node_vector[i]);
        }
    }
    
    int rand;
    
    // if no compelling location, 25% chance of hitting anywhere, 75% chance hitting high possibility
    int hit_high_or_low = my_rand(4);
    if (max_possibility <= 25 && hit_high_or_low == 0){
        do {
            rand = my_rand(118) + 1;    
        } while (AI_element_node_vector[rand]->status != 0);
        return AI_element_node_vector[rand]->get_electron_config();
    } else {
        rand = my_rand(best_elements_to_shoot.size());
        return best_elements_to_shoot[rand]->get_electron_config();
    }
    
}

void AI::hit(const player& player1, int atomic_number){
    ++hits;
    AI_element_node_vector[atomic_number]->status = 1;
    AI_element_node_vector[atomic_number]->possibilities = 0;
    recalculate_possibilities(player1, atomic_number);
}

void AI::missed(const player& player1, int atomic_number){
    ++misses;
    AI_element_node_vector[atomic_number]->status = -1;
    AI_element_node_vector[atomic_number]->possibilities = 0;
    recalculate_possibilities(player1, atomic_number);
}

void AI::recalculate_possibilities(const player& player1, int atomic_number){
    AI_element_node* element_pointer = AI_element_node_vector[atomic_number];
    string electron_config = element_pointer->get_electron_config();

    // if ship is sunk, convert the status of each element in the ship to -1 from 1
    if (player1.ship_sunk(electron_config)){
        // iterate through player1's vector until the correct map is found for this ship
        for (int i = 0; i != player1.ships.size(); ++i){
            if (player1.ships[i].find(electron_config) != player1.ships[i].cend()){
                for (auto j = player1.ships[i].begin(); j != player1.ships[i].end(); ++j){
                    int atomic_number = atomic_number_from_config[j->first];
                    AI_element_node_vector[atomic_number]->status = -1;
                }
            }
        }
    }

    if (element_pointer->status == 1){
        recalculate_after_hit(player1, atomic_number);
    } else if (element_pointer->status == -1){
        recalculate_after_miss_or_sink(player1, atomic_number);
    }
}

void AI::recalculate_after_hit(const player& player1, int atomic_number){
    AI_element_node* element_pointer = AI_element_node_vector[atomic_number];
    
    // add 10 to possibilities of the above ship if it exsits
    if (element_pointer->above_ship && element_pointer->above_ship->status == 0){
        element_pointer->above_ship->possibilities += 10;
        
        // if right_ship exists and has already been hit, ship may be vertical. 
        if (element_pointer->below_ship && element_pointer->below_ship->status == 1){
            element_pointer->above_ship->possibilities += 20;
            if (element_pointer->below_ship->below_ship && element_pointer->below_ship->below_ship->status == 0){
                element_pointer->below_ship->below_ship->possibilities += 20;
            }
        }
    }

    // add 10 to possibilities of the below ship if it exists
    if (element_pointer->below_ship && element_pointer->below_ship->status == 0){
        element_pointer->below_ship->possibilities += 10;
        
        // if above ship exists and has already been hit, ship may be vertical
        if (element_pointer->above_ship && element_pointer->above_ship->status == 1){
            element_pointer->below_ship->possibilities += 20;
            if (element_pointer->above_ship->above_ship && element_pointer->above_ship->above_ship->status == 0){
                element_pointer->above_ship->above_ship->possibilities += 20;
            }
        }
    }

    // add 10 to possibilities of the right_ship if it exists
    if (element_pointer->right_ship && element_pointer->right_ship->status == 0){
        element_pointer->right_ship->possibilities += 10;
        
        // if left ship exists and has already been hit, ship may be horizontal. 
        if (element_pointer->left_ship && element_pointer->left_ship->status == 1){
            element_pointer->right_ship->possibilities += 20;
            if (element_pointer->left_ship->left_ship && element_pointer->left_ship->left_ship->status == 0){
                element_pointer->left_ship->left_ship->possibilities += 20;
            }
        }
        
    }

    // add 10 to possibilities of the left ship if it exists
    if (element_pointer->left_ship && element_pointer->left_ship->status == 0){
        element_pointer->left_ship->possibilities += 10;

        // if right ship already hit, ship may be horizontal
        if (element_pointer->right_ship && element_pointer->right_ship->status == 1){
            element_pointer->left_ship->possibilities += 20;   
            if (element_pointer->right_ship->right_ship && element_pointer->right_ship->right_ship->status == 0){
                element_pointer->right_ship->right_ship->possibilities += 20;
            }
        }
    }
}

void AI::recalculate_after_miss_or_sink(const player& player1, int atomic_number){
    AI_element_node* element_pointer = AI_element_node_vector[atomic_number];

    // There are up to 24 possible ships that are affected due to a miss/sink
    // 24 different if statements written for readability. 

    // ship lies to the right only
    if (element_pointer->right_ship 
        && element_pointer->right_ship->right_ship){
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
    }
    if (element_pointer->right_ship 
        && element_pointer->right_ship->right_ship
        && element_pointer->right_ship->right_ship->right_ship){
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->right_ship->possibilities;
    }
    if (element_pointer->right_ship 
        && element_pointer->right_ship->right_ship
        && element_pointer->right_ship->right_ship->right_ship
        && element_pointer->right_ship->right_ship->right_ship->right_ship){
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->right_ship->right_ship->possibilities;
    }

    // ship lies to the left only
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
    }
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship
        && element_pointer->left_ship->left_ship->left_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->left_ship->possibilities;
    }
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship
        && element_pointer->left_ship->left_ship->left_ship
        && element_pointer->left_ship->left_ship->left_ship->left_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->left_ship->left_ship->possibilities;
    }

    // ship of size 3 stradles horizontally
    if (element_pointer->left_ship 
        && element_pointer->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
    }

    // ship of size 4 stradles horizontally
    if (element_pointer->left_ship 
        && element_pointer->right_ship
        && element_pointer->right_ship->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
    }
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship 
        && element_pointer->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
    }

    // ship of size 5 stradles horizontally
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship 
        && element_pointer->left_ship->left_ship->left_ship
        && element_pointer->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
    }
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship 
        && element_pointer->right_ship
        && element_pointer->right_ship->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
    }
    if (element_pointer->left_ship 
        && element_pointer->right_ship
        && element_pointer->right_ship->right_ship
        && element_pointer->right_ship->right_ship->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->right_ship->possibilities;
    }

    // ship lies to the above only  
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
    }
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship
        && element_pointer->above_ship->above_ship->above_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->above_ship->possibilities;
    }
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship
        && element_pointer->above_ship->above_ship->above_ship
        && element_pointer->above_ship->above_ship->above_ship->above_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->above_ship->above_ship->possibilities;
    }

    // ship lies to the below only
    if (element_pointer->below_ship 
        && element_pointer->below_ship->below_ship){
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
    }
    if (element_pointer->below_ship 
        && element_pointer->below_ship->below_ship
        && element_pointer->below_ship->below_ship->below_ship){
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->below_ship->possibilities;
    }
    if (element_pointer->below_ship 
        && element_pointer->below_ship->below_ship
        && element_pointer->below_ship->below_ship->below_ship
        && element_pointer->below_ship->below_ship->below_ship->below_ship){
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->below_ship->below_ship->possibilities;
    }

    // ship of size 3 stradles vertically
    if (element_pointer->above_ship 
        && element_pointer->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
    }

    // ship of size 4 stradles vertically
    if (element_pointer->above_ship 
        && element_pointer->below_ship
        && element_pointer->below_ship->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
    }
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship 
        && element_pointer->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
    }

    // ship of size 5 stradles vertically
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship 
        && element_pointer->above_ship->above_ship->above_ship
        && element_pointer->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
    }
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship 
        && element_pointer->below_ship
        && element_pointer->below_ship->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
    }
    if (element_pointer->above_ship 
        && element_pointer->below_ship
        && element_pointer->below_ship->below_ship
        && element_pointer->below_ship->below_ship->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->below_ship->possibilities;
    }
}


void AI::calculate_possibilities(){
    for (int i = 1; i != 119; ++i){
        AI_element_node* node = AI_element_node_vector[i];

        // These two if-statements are a combination of six possibilities.
        // Less readable, a bit condensed. 

        // if current element has at least two elements below, it can have a ship
        if (node->below_ship && node->below_ship->below_ship){
            int ship_count = 1;
            if (node->below_ship->below_ship->below_ship){
                ++ship_count;
                if (node->below_ship->below_ship->below_ship->below_ship){
                    ++ship_count;
                    // if a five ship can exist, add one to the fifth element here
                    ++node->below_ship->below_ship
                                     ->below_ship->below_ship
                                     ->possibilities;
                }
                // the fourth element gets ship_count - 1 added since it is not part of the three-block ship
                node->below_ship->below_ship->below_ship->possibilities += ship_count - 1;
            }
            // first three elements get the ship_count added since they are part of every ship
            node->possibilities += ship_count;
            node->below_ship->possibilities += ship_count;
            node->below_ship->below_ship->possibilities += ship_count;
        }
    
        // if current element has at least two elements to the right, it can have a ship
        if (node->right_ship && node->right_ship->right_ship){
            int ship_count = 1;
            if (node->right_ship->right_ship->right_ship){
                ++ship_count;
                if (node->right_ship->right_ship->right_ship->right_ship){
                    ++ship_count;
                    // if a five ship can exist, add one to the fifth element here
                    ++node->right_ship->right_ship
                                     ->right_ship->right_ship
                                     ->possibilities;
                }
                // the fourth element gets ship_count - 1 added since it is not part of the three-block ship
                node->right_ship->right_ship->right_ship->possibilities += ship_count - 1;
            }
            // first three elements get the ship_count added since they are part of every ship
            node->possibilities += ship_count;
            node->right_ship->possibilities += ship_count;
            node->right_ship->right_ship->possibilities += ship_count;
        }
    }
}

// NON MEMBER FUNCTION

int my_rand(int max){
    int random_number;
    int bucket_size = RAND_MAX / max;
    do{
        random_number = rand() / bucket_size;
    } while (random_number > max);

    return random_number;
}