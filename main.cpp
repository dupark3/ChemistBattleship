#include <chrono> // chrono::milliseconds(ms)
#include <iostream>
#include <string>
#include <thread> // this_thread::sleep_for

#include "player.h"
#include "answerkey.h"

using namespace std;

int main(){
    load_periodic_table();

    cout << "Enter your name: ";
    string player1;
    if (cin >> player1){
        cout << "Welcome, " << player1 << ", to the Chemist Battleship." << endl;
    }

    player user(player1);
    cout << "Place three 1 block ships by writing the element's symbols, separated by spaces: ";
    string element;

    for (int i = 0; i != 3; ++i){
        cin >> element;
        cout << "Placing " << element << "... " << endl;
        user.place_ship(element);
    }
    
    std::string player2 = "AI";
    player computer(player2);
    cout << "Computer is placing three 1 block ships randomly..." << endl;
    computer.place_ship_randomly(3);

    int round = 1;
    // game loop, break points within
    while (true){
        cout << endl << "******************** ROUND " << round++ << " STARTING ********************" << endl << endl;
        // player1's turn. input from user is electron config. 
        // store atomic number and element symbol for convenience as local variables
        cout << player1 << "'s turn to take a shot with an electron configuration: ";
        string electron_config;
        cin >> electron_config;
        int atomic_number = electron_configs_reverse[electron_config];
        string element_symbol = element_symbols[atomic_number];

        if(computer.check_shot(electron_config)){
            cout << player1 << " HIT! Element " << element_symbol << " has been shot down." << endl;
            if (computer.check_game_over()){
                cout << "******************** GAME OVER, " << player1 << " IS VICTORIOUS ********************" << endl;
                break;
            }
        } else if (atomic_number == 0) {
            cout << player1 << " MISFIRE! Electron config " << electron_config << " is incorrect." << endl;
        } else {
            cout << player1 << " MISS! Element " << element_symbol << " is open waters." << endl;
        }
        
        this_thread::sleep_for(chrono::milliseconds(1000));

        // Player2's turn
        cout << endl << player2 << "'s turn to take a shot with an electron configuration: ";

        electron_config = electron_configs[rand() % 18 + 1];
        cout << electron_config << endl;
        atomic_number = electron_configs_reverse[electron_config];
        element_symbol = element_symbols[atomic_number];

        if (user.check_shot(electron_config)){
            cout << player2 << " HIT! Element " << element_symbol << " has been shot down." << endl;
            if (user.check_game_over()){
                cout << "******************** GAME OVER, " << player2 << " IS VICTORIOUS ********************" << endl;
                break;
            }
        } else if (atomic_number == 0) {
            cout << player2 << " MISFIRE! Electron config " << electron_config << " is incorrect." << endl;
        } else {
            cout << player2 <<  " MISS! Element " << element_symbol << " is open waters." << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << endl;
        cout << player1 << ": " << user.ships_left() << " ships remaining" << endl;
        cout << player2 << ": " << computer.ships_left() << " ships remaining" << endl;        
    }

    return 0;
}