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
    cout << "Place your 3-block ship by writing the first element's symbol: ";
    string element;
    if (cin >> element){
        user.place_ship(element);
    }

    return 0;
}