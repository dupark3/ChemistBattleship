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
    element_node* best_element_to_shoot;
    for (int i = 1; i != 119; ++i){
        if (element_node_array[i]->possibilities > max_possibility){
            max_possibility = element_node_array[i]->possibilities;
            best_element_to_shoot = element_node_array[i];
        }
    }

    return best_element_to_shoot->get_electron_config();
    
}