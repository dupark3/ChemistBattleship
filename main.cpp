/*
TODO:
☑ AI places one 3-block ship randomly
☑ Use srand() and seed with time to be more random
☑ Expand the periodic table
☑ Place multiple ships
☑ Fix the 6s-4f and 7s-5f transition
☑ Prevent adding ships on the same spot or overlapping
☑ Use bucket method to make rand() more evenly random
☑ Make player class contain a vector of map of ships instead allow "sunk" info (change num of ships)
☑ Unlink 3p down_ship to 3d. 3p should be linked to 4p
☑ Refactor int next_row(int atomic_number) to return the atomic number of the element below (0 if not found)
☑ Place ships of varying sizes
☑ AI class created that inherits the player class
☑ Make AI smarter by shooting around a HIT (check left/right/up/down) until a ship is sunk
☑ Remove dependency of AI class on element_node class (inherit and use load_periodic_table())

Extra Features:
☑ Print the periodic table on console at set-up phase
☑ Add % for how accurate your shots were
☑ Earn special bomb if you identify other person's guess correctly 5 times in a row
☑ Add special bomb that explodes in an X sign
☑ Allow short-hand electron config after five consecutive non-misfires
☐ Implement multiplayer (choice between playing against computer or another person)
☑ Provide a periodic table board that keeps track of hits/misses/sinks for the user

*/


#include <chrono> // chrono::milliseconds(ms)
#include <cstdlib> // srand(), rand(), 
#include <ctime> // time()
#include <iostream>
#include <thread> // this_thread::sleep_for


#include "AI.h"
#include "gameboard.h"
#include "periodic_table.h"
#include "player.h"

using namespace std;

int main(){
    // seed rand() with time
    srand(time(0));

    // load periodictable.txt into answer key data structures
    load_periodic_table(element_node_vector);

    // create display_driver class object to control game board
    display_driver display;
    player player1;
    AI player2;
    display.set_players(player1, player2);
    display.print_periodic_tables();

    // SET UP PLAYER 1 (player class)
    cout << "Enter your name: ";
    string player1name;
    cin >> player1name;
    player1.set_name(player1name);

    // SET UP PLAYER 2 (AI derived class from player)
    std::string player2name = "AI";
    player2.set_name(player2name);
    
    
    display.print_periodic_tables();
    cout << "Welcome, " << player1name << ", to the Periodic Table Battleship" << endl;

    // Ask player 1 to place four 3-block ship until successful
    for (int i = 0; i != 1; ++i){
        cout << endl << "PLACING THREE BLOCK SHIPS: " << endl;
        cout << "Place a 3-block ship #" << i + 1 
             << " by writing the element's symbols, separated by spaces: ";
        string element1, element2, element3;
        cin >> element1 >> element2 >> element3;
        vector<string> elements = {element1, element2, element3};
        if (player1.place_ship(elements)){
            display.place_ship(elements);
            cout << "Ship #" << i + 1 << " of size 3 placed at " << element1 << ", " << element2 << ", and " << element3 << endl;
        } else {
            display.print_periodic_tables();
            cout << "IMPOSSIBLE! Try again and ensure that your elements are horizontal or vertical." << endl;
            --i;
        }
        cin.clear();
    }
    
    // Ask player 1 to place three 4-block ship until successful
    for (int i = 0; i != 0; ++i){
        cout << endl << "PLACING FOUR BLOCK SHIPS: " << endl;
        cout << "Place a 4-block ship #" << i + 1 
             << " by writing the element's symbols, separated by spaces: ";
        string element1, element2, element3, element4;
        cin >> element1 >> element2 >> element3 >> element4;
        vector<string> elements = {element1, element2, element3, element4};
        if (player1.place_ship(elements)){
            display.place_ship(elements);
            cout << "Ship #" << i + 1 << " of size 4 placed at " << element1 << ", " << element2 << ", " << element3 << ", and " << element4 << endl;
        } else {
            display.print_periodic_tables();
            cout << "IMPOSSIBLE! Try again and ensure that your elements are horizontal or vertical." << endl;
            --i;
        }
        cin.clear();
    }

    // Ask player 1 to place two 5-block ship until successful
    for (int i = 0; i != 0; ++i){
        cout << endl << "PLACING FIVE BLOCK SHIPS: " << endl;
        cout << "Place a 5-block ship #" << i + 1 
             << " by writing the element's symbols, separated by spaces: ";
        string element1, element2, element3, element4, element5;
        cin >> element1 >> element2 >> element3 >> element4 >> element5;
        vector<string> elements = {element1, element2, element3, element4, element5};
        if (player1.place_ship(elements)){
            display.place_ship(elements);
            cout << "Ship #" << i + 1 << " of size 5 placed at " << element1 << ", " << element2 << ", " << element3 << ", " << element4 << ", and " << element5 << endl;
        } else {
            display.print_periodic_tables();
            cout << "IMPOSSIBLE! Try again and ensure that your elements are horizontal or vertical." << endl;
            --i;
        }
        cin.clear();
    }

    // Set up AI's ships
    cout << endl << player2name << " is placing his ships..." << endl;
    for(int i = 0; i != 4; ++i){
        player2.place_ship_randomly(3);
    }
    for(int i = 0; i != 3; ++i){
        player2.place_ship_randomly(4);
    }
    for(int i = 0; i != 2; ++i){
        player2.place_ship_randomly(5);
    }
    this_thread::sleep_for(chrono::milliseconds(1500));

    /**********************************game START*********************************************/
    int round = 1;

    // game loop, break points within when all ships of a player has been sunk
    while (true){
        display.print_periodic_tables();
        cout << "ROUND " << round++ << endl;
        
        // PLAYER 1's TURN
        cout << endl << player1name << "'s turn to take a shot with an electron configuration: ";
        string electron_config;
        cin >> electron_config;
        
        // check the use of X-bomb. Check only the four corners of the X. 
        // Leave center element for check_shot() in the following if statement
        if (electron_config == "X" && player1.get_X_bombs() > 0){
            player1.lose_X_bomb();
            display.print_periodic_tables();
            cout << "ROUND " << round++ << endl;
            cout << "X-Bomb Activated! Enter the electron configuration of the center of your X-Bomb: ";
            cin >> electron_config;
            
            // pass config through conversion. will not change it if it was long form already.
            if (player1.short_form_allowed()){
                electron_config = convert_to_long_form(electron_config);
            }

            vector< pair<string, bool> > X_bomb_result = player2.check_X_bomb(electron_config);

            for (int i = 0; i != X_bomb_result.size(); ++i){
                int atomic_number = atomic_number_from_config[X_bomb_result[i].first];
                string element_symbol = element_node_vector[atomic_number]->get_element_symbol();
                string corner_electron_config = X_bomb_result[i].first;
                bool hit = X_bomb_result[i].second;
                
                if (hit){
                    player1.hit();
                    display.player_shot(atomic_number, true);
                    cout << player1name << " HIT! Element " << element_symbol << " has been shot down." << endl;
                    if (player2.check_game_over()){
                        this_thread::sleep_for(chrono::milliseconds(300));
                        cout << "******************** GAME OVER, " << player1name << " IS VICTORIOUS ********************" << endl;
                        return 0;
                    } else if (player2.ship_sunk(corner_electron_config)){
                        cout << "SHIP SUNK at " << element_symbol << "!" << endl;
                    }
                } else {
                    player1.missed();
                    display.player_shot(atomic_number, false);
                    cout << player1name << " MISSED! Element " << element_symbol << " is open waters." << endl;
                }
            }
        }
        
        // if no X-bomb was used, we must check for short form
        if (player1.short_form_allowed()){
            electron_config = convert_to_long_form(electron_config);
        }

        int atomic_number = atomic_number_from_config[electron_config];
        string element_symbol;

        // check_shot is called on the opponent's player object to see if it's a hit
        if(player2.check_shot(electron_config)){
            player1.hit(); // for calculating accuracy. increments number of hits
            display.player_shot(atomic_number, true);
            element_symbol = element_node_vector[atomic_number]->get_element_symbol();
            cout << player1name << " HIT! Element " << element_symbol << " has been shot down." << endl;
            if (player2.check_game_over()){
                this_thread::sleep_for(chrono::milliseconds(300));
                cout << "******************** GAME OVER, " << player1name << " IS VICTORIOUS ********************" << endl;
                return 0;
            } else if (player2.ship_sunk(electron_config)){
                cout << "SHIP SUNK!" << endl;
            }
        } else if (atomic_number == 0) {
            player1.misfire();
            cout << player1name << " MISFIRE! Electron config " << electron_config << " is incorrect." << endl;
        } else {
            player1.missed();
            display.player_shot(atomic_number, false);
            element_symbol = element_node_vector[atomic_number]->get_element_symbol();
            cout << player1name << " MISSED! Element " << element_symbol << " is open waters." << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(300));

        // player2's turn

        cout << endl << player2name << "\'s turn to take a shot with an electron configuration: ";
        
        // take an educated shot
        electron_config = player2.take_educated_shot();
        atomic_number = atomic_number_from_config[electron_config];
        element_symbol = element_node_vector[atomic_number]->get_element_symbol();
        cout << electron_config << endl;
        
        // ask user to identify this electron config
        cout << "Identify the element: ";
        string element_symbol_guess;
        cin >> element_symbol_guess;
        if (element_symbol == element_symbol_guess){
            player1.correct_guess();
            cout << endl << "Correct! You have identified " << player1.get_correct_guesses() << " in a row. " << endl;
            if (player1.get_correct_guesses() == 5){
                player1.earn_X_bomb();
                player1.reset_guesses();
                cout << "You have earned an X-bomb. You have " << player1.get_X_bombs() << " X-bombs. Write X to use. " << endl;
            }
        } else {
            player1.reset_guesses();
            cout << endl << "Incorrect. Number of correct guesses have been reset to zero. " << endl;
        }


        if (player1.check_shot(electron_config)){
            player2.hit(player1, atomic_number);
            display.enemy_shot(atomic_number, true);
            cout << player2name << " HIT! Element " << element_symbol << " has been shot down." << endl;
            if (player1.check_game_over()){
                this_thread::sleep_for(chrono::milliseconds(300));
                cout << "******************** GAME OVER, " << player2name << " IS VICTORIOUS ********************" << endl;
                break;
            } else if (player1.ship_sunk(electron_config)){
                cout << "SHIP SUNK!" << endl;
            }
        } else {
            player2.missed(player1, atomic_number);
            display.enemy_shot(atomic_number, false);
            cout << player2name <<  " MISSED! Element " << element_symbol << " is open waters." << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    
    return 0;
}