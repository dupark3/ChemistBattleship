#include <iostream>
#include <string>

#include "player.h"
#include "answerkey.h"

using namespace std;

int main(){
    cout << "Enter your name: ";
    string username;
    if (cin >> username){
        cout << "Welcome, " << username << ", to the Chemist Battleship." << endl;
    }

    load_periodic_table();

    player user(username);
    cout << "Place three 1 block ships by writing the first element's symbol, separated by spaces: ";
    string element;

    for (int i = 0; i != 3; ++i){
        cin >> element;
        cout << "Placing " << element << "... " << endl;
        user.place_ship(element);
    }
    
    player computer("AI");
    cout << "Computer is placing his ships...";

    for (int i = 0; i != 3; ++i){

    }

    return 0;
}