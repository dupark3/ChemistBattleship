#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "AI.h"
#include "player.h"

using namespace std;

string AI::take_educated_shot(const player& player1){
    int max_possibility = 0;
    vector<element_node*> best_elements_to_shoot;
    for (int i = 1; i != 119; ++i){
        if (element_node_array[i]->possibilities > max_possibility){
            max_possibility = element_node_array[i]->possibilities;
            best_elements_to_shoot.clear();
            best_elements_to_shoot.push_back(element_node_array[i]);
        } else if (element_node_array[i]->possibilities == max_possibility) {
            best_elements_to_shoot.push_back(element_node_array[i]);
        }
    }
    int rand = my_rand(best_elements_to_shoot.size());
    return best_elements_to_shoot[rand]->get_electron_config();
    
}

void AI::hit(const player& player1, int atomic_number){
    element_node_array[atomic_number]->status = 1;
    element_node_array[atomic_number]->possibilities = 0;
    recalculate_possibilities(player1, atomic_number);
}

void AI::missed(const player& player1, int atomic_number){
    element_node_array[atomic_number]->status = -1;
    element_node_array[atomic_number]->possibilities = 0;
    recalculate_possibilities(player1, atomic_number);
}

void AI::recalculate_possibilities(const player& player1, int atomic_number){
    element_node* element_pointer = element_node_array[atomic_number];
    string electron_config = element_pointer->get_electron_config();

    // if ship is sunk, convert the status of each element in the ship to -1
    if (player1.ship_sunk(electron_config)){
        // iterate through player1's vector until the correct map is found for this ship
        for (int i = 0; i != player1.ships.size(); ++i){
            if (player1.ships[i].find(electron_config) != player1.ships[i].cend()){
                for (auto j = player1.ships[i].begin(); j != player1.ships[i].end(); ++j){
                    int atomic_number = atomic_number_from_config[j->first];
                    element_node_array[atomic_number]->status = -1;
                }

            }
        }
    }

    if (element_pointer->status == 1){
        recalculate_after_hit(player1, atomic_number);
    } else if (element_pointer->status == -1){
        recalculate_after_miss_or_sink(player1, atomic_number);
    }

    for (int i = 1; i != 119; ++i){
        cout << element_node_array[i]->element_symbol << " : " << element_node_array[i]->possibilities << endl;
    }
    
}

void AI::recalculate_after_hit(const player& player1, int atomic_number){
    element_node* element_pointer = element_node_array[atomic_number];
    
    // add more to above ship if it exsits
    if (element_pointer->above_ship && element_pointer->above_ship->status == 0){
        element_pointer->above_ship->possibilities += 10;
        
        // if below_ship exists and has already been hit, ship may be vertical. 
        if (element_pointer->below_ship && element_pointer->below_ship->status == 1){
            element_pointer->above_ship->possibilities += 20;
        }
    }

    if (element_pointer->below_ship && element_pointer->below_ship->status == 0){
        element_pointer->below_ship->possibilities += 10;
        
        if (element_pointer->above_ship && element_pointer->above_ship->status == 1){
            element_pointer->below_ship->possibilities += 20;
        }
    }

    if (element_pointer->right_ship && element_pointer->right_ship->status == 0){
        element_pointer->right_ship->possibilities += 10;
        
        // if left ship is already hit, ship may be horizontal. add more probability to the right
        if (element_pointer->left_ship && element_pointer->left_ship->status == 1){
            element_pointer->right_ship->possibilities += 20;
        }
        
    }

    if (element_pointer->left_ship && element_pointer->left_ship->status == 0){
        element_pointer->left_ship->possibilities += 10;

        // if right ship already hit, ship may be horizontal
        if (element_pointer->right_ship && element_pointer->right_ship->status == 1){
            element_pointer->left_ship->possibilities += 10;   
        }
    }
}

void AI::recalculate_after_miss_or_sink(const player& player1, int atomic_number){
    element_node* element_pointer = element_node_array[atomic_number];

    // subtract from elements to the right
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
    // subtract from elements to the left
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

    // subtract from elements above    
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


    // subtract from elements below
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
}


void calculate_possibilities(){
    for (int i = 1; i != 119; ++i){
        element_node* element_pointer = element_node_array[i];
        
        if(element_pointer->below_ship 
            && element_pointer->below_ship->below_ship){
            ++element_pointer->possibilities;
            ++element_pointer->below_ship->possibilities;
            ++element_pointer->below_ship->below_ship->possibilities;
        }

        if(element_pointer->below_ship 
            && element_pointer->below_ship->below_ship 
            && element_pointer->below_ship->below_ship->below_ship){
            ++element_pointer->possibilities;
            ++element_pointer->below_ship->possibilities;
            ++element_pointer->below_ship->below_ship->possibilities;
            ++element_pointer->below_ship->below_ship->below_ship->possibilities;
        }

        if(element_pointer->below_ship 
            && element_pointer->below_ship->below_ship 
            && element_pointer->below_ship->below_ship->below_ship 
            && element_pointer->below_ship->below_ship->below_ship->below_ship){
            ++element_pointer->possibilities;
            ++element_pointer->below_ship->possibilities;
            ++element_pointer->below_ship->below_ship->possibilities;
            ++element_pointer->below_ship->below_ship->below_ship->possibilities;
            ++element_pointer->below_ship->below_ship->below_ship->below_ship->possibilities;
        }

        if(element_pointer->right_ship 
            && element_pointer->right_ship->right_ship){
            ++element_pointer->possibilities;
            ++element_pointer->right_ship->possibilities;
            ++element_pointer->right_ship->right_ship->possibilities;
        }

        if(element_pointer->right_ship 
            && element_pointer->right_ship->right_ship 
            && element_pointer->right_ship->right_ship->right_ship){
            ++element_pointer->possibilities;
            ++element_pointer->right_ship->possibilities;
            ++element_pointer->right_ship->right_ship->possibilities;
            ++element_pointer->right_ship->right_ship->right_ship->possibilities;
        }

        if(element_pointer->right_ship 
            && element_pointer->right_ship->right_ship 
            && element_pointer->right_ship->right_ship->right_ship 
            && element_pointer->right_ship->right_ship->right_ship->right_ship){
            ++element_pointer->possibilities;
            ++element_pointer->right_ship->possibilities;
            ++element_pointer->right_ship->right_ship->possibilities;
            ++element_pointer->right_ship->right_ship->right_ship->possibilities;
            ++element_pointer->right_ship->right_ship->right_ship->right_ship->possibilities;
        }   
    }
        
    for (int i = 1; i != 119; ++i){
        cout << element_node_array[i]->element_symbol << " : " << element_node_array[i]->possibilities << endl;
    }
}