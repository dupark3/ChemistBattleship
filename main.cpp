#include <chrono> // chrono::milliseconds(ms)
#include <iostream>
#include <string>
#include <thread> // this_thread::sleep_for
#include <vector>

#include "player.h"
#include "answerkey.h"

using namespace std;

int main(){
    load_periodic_table();

    // Set up player 1
    cout << "Enter your name: ";
    string player1name;
    if (cin >> player1name){
        cout << "Welcome, " << player1name << ", to the Chemist Battleship." << endl;
    }

    player player1(player1name);
    cout << "Place a 3-block ships by writing the element's symbols, separated by spaces: ";
    string element1, element2, element3;
    cin >> element1 >> element2 >> element3;
    vector<string> elements = {element1, element2, element3};
    player1.place_ship(elements);
    
    // Set up player 2
    std::string player2name = "AI";
    player player2(player2name);
    cout << "player2 is placing three 1 block ships randomly..." << endl;
    player2.place_ship_randomly(3);

    int round = 1;

    // game loop, break points within when all ships of a player has been sunk
    while (true){
        cout << endl << "******************** ROUND " << round++ << " STARTING ********************" << endl << endl;
        
        cout << player1name << "'s turn to take a shot with an electron configuration: ";
        
        // store electron config, atomic number, & element symbol as local variables for convenience
        string electron_config;
        cin >> electron_config;
        int atomic_number = electron_configs_reverse[electron_config];
        string element_symbol = element_symbols[atomic_number];

        if(player2.check_shot(electron_config)){
            cout << player1name << " HIT! Element " << element_symbol << " has been shot down." << endl;
            if (player2.check_game_over()){
                cout << "******************** GAME OVER, " << player1name << " IS VICTORIOUS ********************" << endl;
                break;
            }
        } else if (atomic_number == 0) {
            cout << player1name << " MISFIRE! Electron config " << electron_config << " is incorrect." << endl;
        } else {
            cout << player1name << " MISS! Element " << element_symbol << " is open waters." << endl;
        }
        
        this_thread::sleep_for(chrono::milliseconds(1000));

        // player2name's turn
        cout << endl << player2name << "'s turn to take a shot with an electron configuration: ";

        electron_config = electron_configs[rand() % 18 + 1];
        cout << electron_config << endl;
        atomic_number = electron_configs_reverse[electron_config];
        element_symbol = element_symbols[atomic_number];

        if (player1.check_shot(electron_config)){
            cout << player2name << " HIT! Element " << element_symbol << " has been shot down." << endl;
            if (player1.check_game_over()){
                cout << "******************** GAME OVER, " << player2name << " IS VICTORIOUS ********************" << endl;
                break;
            }
        } else if (atomic_number == 0) {
            cout << player2name << " MISFIRE! Electron config " << electron_config << " is incorrect." << endl;
        } else {
            cout << player2name <<  " MISS! Element " << element_symbol << " is open waters." << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << endl;
        cout << player1name << ": " << player1.ships_left() << " ships remaining" << endl;
        cout << player2name << ": " << player2.ships_left() << " ships remaining" << endl;        
    }

    return 0;
}