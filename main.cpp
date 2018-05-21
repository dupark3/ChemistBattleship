#include <iostream>
#include <string>

#include "player.h"
#include "answerkey.h"

using namespace std;

int main(){
    load_periodic_table();

    cout << "Enter your name: ";
    string username;
    if (cin >> username){
        cout << "Welcome, " << username << ", to the Chemist Battleship." << endl;
    }

    player user(username);
    cout << "Place three 1 block ships by writing the element's symbols, separated by spaces: ";
    string element;

    for (int i = 0; i != 3; ++i){
        cin >> element;
        cout << "Placing " << element << "... " << endl;
        user.place_ship(element);
    }
    
    player computer("AI");
    cout << "Computer is placing three 1 block ships randomly..." << endl;
    computer.place_ship_randomly(3);

    cout << "*******************Let the battleship begin******************* " << endl;

    bool game_over = false;

    while (!game_over){
        cout << "It is " << username << "'s turn to take a shot with an electron configuration: ";
        string electron_config;
        cin >> electron_config;
        if(computer.check_shot(electron_config)){
            cout << "HIT! Element " << endl;
        }

    }

    


    return 0;
}