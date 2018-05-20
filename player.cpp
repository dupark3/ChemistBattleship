#include <iostream>

#include "player.h"
#include "answerkey.h"

using namespace std;

void player::place_ship(std::string element_symbol){
    int atomic_number = atomic_numbers[element_symbol];
    if (atomic_number != 0){
        ships[atomic_number] = true;
    }
}