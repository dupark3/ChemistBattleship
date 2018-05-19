#include <iostream>
#include <string>

#include "player.h"

using namespace std;

int main(){
    cout << "Enter your name: ";
    string username;
    if (cin >> username){
        cout << "Welcome, " << username << ", to the Chemist Battleship." << endl;
    }
    player user(username);
    cout << "Place your 3-block ship by writing the first element's symbol: ";
    string element;
    if (cin >> element){
        place_ship(element);
    }

    return 0;
}