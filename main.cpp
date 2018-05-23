#include <chrono> // chrono::milliseconds(ms)
#include <cstdlib> // srand()
#include <ctime> // time()
#include <iostream>
#include <string>
#include <thread> // this_thread::sleep_for
#include <vector>

#include "player.h"
#include "answerkey.h"

using namespace std;

/*
TODO:
☑ AI places one 3-block ship randomly
☑ Use srand() and seed with time to be more random
☐ Use bucket method to create more random numbers
☐ Expand the periodic table
☐ Place multiple ships
☐ Prevent adding ships on the same spot or overlapping
☐ Make each turn a function to avoid repeating similar code
☐ Make player class contain groups of ships instead of a huge list of electron configs to allow "sunk" info
☐ Make AI smarter by shooting around a HIT until a ship is sunk

Extra Features:
☐ Add % for how accurate your shots were
☐ Add special bomb that explodes in a + sign
☐ Two player game

*/

int main(){
    load_periodic_table();

    // Set up player 1
    cout << "Enter your name: ";
    string player1name;
    if (cin >> player1name){
        cout << "Welcome, " << player1name << ", to the Periodic Table Battleship." << endl;
    }
    player player1(player1name);

    // Ask player 1 to place a 3-block ship until successful
    while (true){
        cout << "Place a 3-block ship by writing the element's symbols, separated by spaces: ";
        string element1, element2, element3;
        cin >> element1 >> element2 >> element3;
        vector<string> elements = {element1, element2, element3};
        if (player1.place_ship(elements)){
            cout << "Ship placed!" << endl;
            break;
        } else {
            cout << "Try again and ensure that your three elements are horizontal or vertical." << endl;
        }
    }


    // Set up player 2 
    std::string player2name = "AI";
    player player2(player2name);
    cout << "player2 is placing a 3-block ship randomly..." << endl;
    player2.place_ship_randomly(3);



    int round = 1;

    // game loop, break points within when all ships of a player has been sunk
    while (true){
        cout << endl << "******************** ROUND " << round++ << " STARTING ********************" << endl << endl;
        
        cout << player1name << "'s turn to take a shot with an electron configuration: ";
        
        // store electron config, atomic number, & element symbol as local variables for convenience
        string electron_config;
        cin >> electron_config;
        int atomic_number = electron_configs[electron_config];
        string element_symbol;

        if(player2.check_shot(electron_config)){
            element_symbol = element_node_array[atomic_number]->get_element_symbol();
            cout << player1name << " HIT! Element " << element_symbol << " has been shot down." << endl;
            if (player2.check_game_over()){
                this_thread::sleep_for(chrono::milliseconds(500));
                cout << "******************** GAME OVER, " << player1name << " IS VICTORIOUS ********************" << endl;
                break;
            }
        } else if (atomic_number == 0) {
            cout << player1name << " MISFIRE! Electron config " << electron_config << " is incorrect." << endl;
        } else {
            element_symbol = element_node_array[atomic_number]->get_element_symbol();
            cout << player1name << " MISS! Element " << element_symbol << " is open waters." << endl;
        }
        
        this_thread::sleep_for(chrono::milliseconds(500));

        // player2name's turn
        cout << endl << player2name << "'s turn to take a shot with an electron configuration: ";

        electron_config = element_node_array[rand() % 18 + 1]->get_electron_config();
        cout << electron_config << endl;
        atomic_number = electron_configs[electron_config];
        element_symbol = element_node_array[atomic_number]->get_element_symbol();

        if (player1.check_shot(electron_config)){
            cout << player2name << " HIT! Element " << element_symbol << " has been shot down." << endl;
            if (player1.check_game_over()){
                this_thread::sleep_for(chrono::milliseconds(500));
                cout << "******************** GAME OVER, " << player2name << " IS VICTORIOUS ********************" << endl;
                break;
            }
        } else if (atomic_number == 0) {
            cout << player2name << " MISFIRE! Electron config " << electron_config << " is incorrect." << endl;
        } else {
            cout << player2name <<  " MISS! Element " << element_symbol << " is open waters." << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(500));

        cout << endl;
        cout << player1name << ": " << player1.ships_left() << " ships remaining" << endl;
        cout << player2name << ": " << player2.ships_left() << " ships remaining" << endl;        

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    return 0;
}