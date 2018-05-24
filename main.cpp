#include <chrono> // chrono::milliseconds(ms)
#include <cstdlib> // srand(), rand()
#include <ctime> // time()
#include <iostream>
#include <string>
#include <thread> // this_thread::sleep_for
#include <vector>

#include "periodic_table.h"
#include "player.h"

using namespace std;

/*
TODO:
☑ AI places one 3-block ship randomly
☑ Use srand() and seed with time to be more random
☑ Expand the periodic table
☑ Place multiple ships
☑ Fix the 6s-4f and 7s-5f transition being
☑ Prevent adding ships on the same spot or overlapping
☐ Use bucket method to create more random numbers
☐ Make player class contain groups of ships instead of a huge list of electron configs to allow "sunk" info
☐ Make AI smarter by shooting around a HIT (check left/right/up/down) until a ship is sunk
☐ Make each turn a function to avoid repeating similar code

Extra Features:
☑ Print the periodic table on console at set-up phase
☐ Add % for how accurate your shots were
☐ Add special bomb that explodes in a + sign
☐ Earn special bomb if you identify other person's guess correctly 5 times in a row
☐ Give user choice between single or multiplayer

*/

int main(){
    srand(time(0));

    load_periodic_table();

    // Set up player 1
    cout << "Enter your name: ";
    string player1name;
    if (cin >> player1name){
        cout << "Welcome, " << player1name << ", to the Periodic Table Battleship." << endl;
    }
    player player1(player1name);

    cout << endl << "                   PERIODIC TABLE" << endl;

    print_periodic_table();

    // Ask player 1 to place five 3-block ship until successful
    for (int i = 0; i != 5; ){
        cout << "Place a 3-block ship by writing the element's symbols, separated by spaces: ";
        string element1, element2, element3;
        cin >> element1 >> element2 >> element3;
        vector<string> elements = {element1, element2, element3};
        if (player1.place_ship(elements)){
            cout << "Ship #" << ++i << " placed at " << element1 << ", " << element2 << ", and " << element3 << endl;
        } else {
            cout << "Try again and ensure that your three elements are horizontal or vertical." << endl;
        }
    }

    // Set up player 2 
    std::string player2name = "AI";
    player player2(player2name);
    for(int i = 0; i != 5; ){
        player2.place_ship_randomly(3);
        cout << "Ship #" << ++i << " placed at a random location." << endl;
    }

    int round = 1;

    // game loop, break points within when all ships of a player has been sunk
    while (true){
        cout << endl << "******************** ROUND " << round++ << " STARTING ********************" << endl << endl;
        
        // player1's turn
        cout << player1name << "'s turn to take a shot with an electron configuration: ";
        
        // store config, atomic number, symbol as local variables for convenience
        string electron_config;
        cin >> electron_config;
        int atomic_number = atomic_number_from_config[electron_config];
        string element_symbol;

        // check_shot is called on the opponent's player object to see if it's a hit
        if(player2.check_shot(electron_config)){
            element_symbol = element_node_array[atomic_number]->get_element_symbol();
            cout << player1name << " HIT! Element " << element_symbol << " has been shot down." << endl;
            if (player2.check_game_over()){
                this_thread::sleep_for(chrono::milliseconds(300));
                cout << "******************** GAME OVER, " << player1name << " IS VICTORIOUS ********************" << endl;
                break;
            }
        } else if (atomic_number == 0) {
            cout << player1name << " MISFIRE! Electron config " << electron_config << " is incorrect." << endl;
        } else {
            element_symbol = element_node_array[atomic_number]->get_element_symbol();
            cout << player1name << " MISS! Element " << element_symbol << " is open waters." << endl;
        }
        
        this_thread::sleep_for(chrono::milliseconds(300));

        // player2's turn
        cout << endl << player2name << "'s turn to take a shot with an electron configuration: ";

        // pick a random shot
        electron_config = element_node_array[rand() % 118 + 1]->get_electron_config();
        cout << electron_config << endl;

        // set local variables for conveneince of printing shot info
        atomic_number = atomic_number_from_config[electron_config];
        element_symbol = element_node_array[atomic_number]->get_element_symbol();

        if (player1.check_shot(electron_config)){
            cout << player2name << " HIT! Element " << element_symbol << " has been shot down." << endl;
            if (player1.check_game_over()){
                this_thread::sleep_for(chrono::milliseconds(300));
                cout << "******************** GAME OVER, " << player2name << " IS VICTORIOUS ********************" << endl;
                break;
            }
        } else {
            cout << player2name <<  " MISS! Element " << element_symbol << " is open waters." << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(300));

        cout << endl;
        cout << player1name << ": " << player1.ships_left() << " ships remaining" << endl;
        cout << player2name << ": " << player2.ships_left() << " ships remaining" << endl;        

        this_thread::sleep_for(chrono::milliseconds(300));
    }

    return 0;
}