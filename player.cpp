#include <iostream>

#include "player.h"
#include "answerkey.h"

using namespace std;

void player::place_ship(std::string element_symbol){
    int atomic_number = atomic_numbers[element_symbol];
    cout << atomic_number << endl;
    if (atomic_number > 0){
        cout << atomic_number << endl;
        ships[atomic_number] = true;
    }
}

void player::place_ship(int atomic_number){
    if (atomic_number > 0 && atomic_number < 118){
        cout << electron_configs[atomic_number] << endl;
        ships[atomic_number] = true;
    }
}