#include <iostream>
#include <string>

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

    cout << "*******************Let the battleship begin******************* " << endl;

    bool game_over = false;

    while (!game_over){
        cout << "It is " << player1 << "'s turn to take a shot with an electron configuration: ";
        string electron_config;
        string element_symbol;

        cin >> electron_config;
        if(computer.check_shot(electron_config, element_symbol)){
            cout << "HIT! Element " << element_symbol << " has been shot down." << endl;
        } else {
            cout << "MISS! Element " << element_symbol << " is open waters." << endl;
        }
        
        cout << "It is " << player2 << "'s turn to take a shot with an electron configuration: ";

        electron_config = electron_configs[rand() % 18 + 1];
        cout << electron_config << endl;


    }

    


    return 0;
}