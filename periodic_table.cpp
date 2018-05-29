#include <algorithm> // find
#include <cstdlib> // exit
#include <fstream> // ifstream
#include <iostream> // cerr
#include <map>
#include <string>
#include <vector>


#include "periodic_table.h"
#include "player.h"

using namespace std;

// global map objects defined here and externally linked
std::map<std::string, int> atomic_number_from_symbol;
std::map<std::string, int> atomic_number_from_config;
element_node* element_node_array[MAX_ELEMENT + 1];

void load_periodic_table(){
    ifstream PeriodicTableFileStream;
    PeriodicTableFileStream.open("periodictable.txt");

    if (!PeriodicTableFileStream){
        cerr << "Unable to open periodic table file";
        exit(1);
    }

    // read and load info
    int atomic_number;
    while(PeriodicTableFileStream >> atomic_number){
        // read symbol and store into an element_node and atomic_numbers hashmap
        string element_symbol;
        PeriodicTableFileStream >> element_symbol;
        element_node_array[atomic_number] = new element_node;
        element_node_array[atomic_number]->atomic_number = atomic_number;
        element_node_array[atomic_number]->element_symbol = element_symbol;
        atomic_number_from_symbol[element_symbol] = atomic_number;

        // read name and store into element_node
        string element_name;
        PeriodicTableFileStream >> element_name;
        element_node_array[atomic_number]->element_name = element_name;

        // read electron config and store into an element_node and electron_configs hashmap
        string electron_config;
        PeriodicTableFileStream >> electron_config;
        element_node_array[atomic_number]->electron_config = electron_config;
        atomic_number_from_config[electron_config] = atomic_number;
    }


    // set correct pointers to adjacent nodes to the right and below
    for(int i = 1; i != MAX_ELEMENT; ++i){
        // four scenarios resulting from the possibility of a valid right/down
        // neighbor or no right/down neighbors
        map<int, bool> both_valid  = { {3, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1},
        {9, 1}, {11, 1}, {13, 1}, {14, 1}, {15, 1}, {16, 1}, {17, 1}, {19, 1}, 
        {20,1}, {21, 1}, {22, 1}, {23, 1}, {24, 1}, {25, 1}, {26, 1}, {27, 1}, 
        {28, 1},{29, 1}, {30, 1}, {31, 1}, {32, 1}, {33, 1}, {34, 1}, {35, 1}, 
        {37, 1}, {38,1}, {39, 1}, {40, 1}, {41, 1}, {42, 1}, {43, 1}, {44, 1}, 
        {45, 1}, {46, 1},{47, 1}, {48, 1}, {49, 1}, {50, 1}, {51, 1}, {52, 1}, 
        {53, 1}, {55, 1}, {56,1}, {71, 1}, {72, 1}, {73, 1}, {74, 1}, {75, 1}, 
        {76, 1}, {77, 1}, {78, 1},{79, 1}, {80, 1}, {81, 1}, {82, 1}, {83, 1}, 
        {84, 1}, {85, 1}, {57, 1}, {58, 1}, {59,1}, {60, 1}, {61, 1}, {62, 1}, 
        {63, 1}, {64, 1}, {65, 1}, {66, 1}, {67, 1},{68, 1}, {69, 1} };

        map<int, bool> right_valid = { {87, 1}, {88, 1}, {103, 1}, {104, 1 },
        {105, 1}, {106, 1}, {107, 1}, {108, 1}, {109, 1}, {110, 1}, {111, 1}, 
        {112, 1}, {113, 1}, {114, 1}, {115, 1}, {116, 1}, {117, 1}, {89, 1 }, 
        {90, 1}, {91,1}, {92, 1}, {93, 1}, {94, 1}, {95, 1}, {96, 1}, {97, 1}, 
        {98, 1}, {99, 1},{100, 1}, {101, 1} };

        map<int, bool> down_valid  = { {1, 1}, {2, 1}, {4, 1}, {10, 1}, {12,1},
        {18, 1}, {36, 1}, {54, 1}, {86, 1}, {70, 1} } ;

        map<int, bool> no_valid    = { {118, 1}, {102, 1} };
        
        int next_row = next_rows_atomic_number(i);

        if (both_valid[i]) {
            element_node_array[i]->right_ship = element_node_array[i + 1];
            element_node_array[i]->down_ship = element_node_array[next_row];
        } else if (right_valid[i]) {
            element_node_array[i]->right_ship = element_node_array[i + 1];
            element_node_array[i]->down_ship = 0;
        } else if (down_valid[i]) {
            element_node_array[i]->right_ship = 0;
            element_node_array[i]->down_ship = element_node_array[next_row];
        } else if (no_valid[i]) {
            element_node_array[i]->right_ship = 0;
            element_node_array[i]->down_ship = 0;
        }
    }
    
    // fix transition from 6s/7s to 4f/5f
    element_node_array[56]->right_ship = element_node_array[71];
    element_node_array[88]->right_ship = element_node_array[103];

}

int next_rows_atomic_number(int atomic_number){
    if (atomic_number == 1){
        return atomic_number + 2;
    } else if (atomic_number >= 2 && atomic_number <= 12){
        return atomic_number + 8;
    } else if (atomic_number >= 13 && atomic_number <= 38){
        return atomic_number + 18;
    } else if (atomic_number >= 39 && atomic_number <= 86){
        return atomic_number + 32;
    } else {
        return 0;
    }
}

void print_periodic_table(){
                                   
                                   
                                   


    cout << 
    "╔══╗              __                               ╔══╗" << endl <<
    "║H ║              \\ \\___     .__                   ║He║" << endl <<
    "╠══╬══╗         .--\"\"___\\..--\"/     ╔══╦══╦══╦══╦══╬══╣" << endl <<
    "║Li║Be║     .__.|-\"\"\"..... \' /      ║B ║C ║N ║O ║F ║Ne║" << endl <<
    "╠══╬══╣_____\\_______________/______ ╠══╬══╬══╬══╬══╬══╣" << endl <<
    "║Na║Mg║    ~       ~        ~       ║Al║Si║P ║S ║Cl║Ar║" << endl <<
    "╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣" << endl <<
    "║K ║Ca║Sc║Ti║V ║Cr║Mn║Fe║Co║Ni║Cu║Zn║Ga║Ge║As║Se║Br║Kr║" << endl <<
    "╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣" << endl <<
    "║Rb║Sr║Y ║Zr║Nb║Mo║Tc║Ru║Rh║Pd║Ag║Cd║In║Sn║Sb║Te║I ║Xe║" << endl <<
    "╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣" << endl <<
    "║Cs║Ba░Lu║Hf║Ta║W ║Re║Os║Ir║Pt║Au║Hg║Tl║Pb║Bi║Po║At║Rn║" << endl <<
    "╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣" << endl <<
    "║Fr║Ra░Lr║Rf║Db║Sg║Bh║Hs║Mt║Ds║Rg║Cn║Nh║Fl║Mc║Lv║Ts║Og║" << endl <<
    "╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝" << endl <<
    "      ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗" << endl <<
    "      ░La║Ce║Pr║Nd║Pm║Sm║Eu║Gd║Tb║Dy║Ho║Er║Tm║Yb║" << endl <<
    "      ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣" << endl <<
    "      ░Ac║Th║Pa║U ║Np║Pu║Am║Cm║Bk║Cf║Es║Fm║Md║No║" << endl <<
    "      ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝" << endl;

}