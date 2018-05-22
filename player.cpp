#include <algorithm> // sort()
#include <cstdlib> // rand(), size_t
#include <iostream>
#include <vector>

#include "answerkey.h"
#include "player.h"

using namespace std;

void player::place_ship(const std::string& element_symbol){
    int atomic_number = atomic_numbers[element_symbol];
    if (atomic_number > 0){
        ships[ electron_configs[atomic_number] ] = true;
        ++number_of_ships;
    }
}

void player::place_ship(const vector<string>& elements){
    vector<int> ship_atomic_numbers;
    for (int i = 0; i != elements.size(); ++i){
        ship_atomic_numbers.push_back(atomic_numbers[elements[i]]);
    }

    if (continuous_blocks(ship_atomic_numbers)){
        for (int i = 0; i != ship_atomic_numbers.size(); ++i){
            ships[ electron_configs[ship_atomic_numbers[i]] ] = true;
            ++number_of_ships;
        }
    }
}

void player::place_ship(int atomic_number){
    if (atomic_number > 0 && atomic_number < 18){
        ships[ electron_configs[atomic_number] ] = true;
        ++number_of_ships;
    }
}

// REFACTOR: use bucket method to create more random numbers
// REFACTOR: ability to add three 3-block, two 4-block, and one 5-block ships. 
void player::place_ship_randomly(int number_of_blocks){
    for (int i = 0; i != number_of_blocks; ++i){
        place_ship(rand() % 18 + 1);
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

bool player::continuous_blocks(vector<int>& numbers){
    sort(numbers.begin(), numbers.end());
    int ship_size = numbers.size();
    if (numbers[1] - numbers[0] == 1){
        // horizontal ship
    } else if (){
        // vertical ship
    } 
    return false;
}