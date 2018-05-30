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