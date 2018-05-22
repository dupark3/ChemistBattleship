#include <algorithm> // find
#include <cstdlib> // exit
#include <fstream> // ifstream
#include <iostream> // cerr
#include <map>
#include <string>
#include <vector>


#include "answerkey.h"
#include "player.h"

using namespace std;

// global map objects defined here and externally linked
periodic_table periodic_table_object;
std::map<std::string, int> atomic_numbers;
std::map<std::string, int> electron_configs;
// std::string element_symbols[19];
// std::map<int, std::string> electron_configs_reverse;

void load_periodic_table(){
    ifstream PeriodicTableFileStream;
    PeriodicTableFileStream.open("abridged_PeriodicTableFileStream.txt");

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
        periodic_table_object.element_node_array[atomic_number]->element_symbol = element_symbol;

        // read name and store into element_node
        string element_name;
        PeriodicTableFileStream >> element_name;
        periodic_table_object.element_node_array[atomic_number]->element_name = element_name;

        // read electron config and store into an element_node and electron_configs hashmap
        string electron_config;
        PeriodicTableFileStream >> electron_config;
        periodic_table_object.element_node_array[atomic_number]->electron_configuration = electron_config;
        electron_configs[electron_config] = atomic_number;
    }
    
    // set correct pointers to adjacent nodes to the right and below
    for(int i = 1; i != MAX_ELEMENT; ++i){
        // four scenarios resulting from the possibility of a valid right/down neighbor or no right/down neighbors
        map<int, bool> both_valid  = { {3 , 1}, {5 , 1}, {6 , 1}, {7 , 1}, {8 , 1}, {9 , 1} };
        map<int, bool> right_valid = { {11, 1}, {13, 1}, {14, 1}, {15, 1}, {16, 1}, {17, 1} };
        map<int, bool> down_valid  = { {1 , 1}, {2 , 1}, {4 , 1}, {10, 1} };
        map<int, bool> no_valid    = { {12, 1}, {18, 1} };
        
        int next_row;
        if (i == 1){
            next_row = 2;
        } else if (i >= 2 && i < 13){
            next_row = 8;
        } 

        if (both_valid[i]) {
            periodic_table_object.element_node_array[i]->right_valid = periodic_table_object.element_node_array[i + 1];
            periodic_table_object.element_node_array[i]->down_valid = periodic_table_object.element_node_array[i + next_row];
        } else if (right_valid[i]) {
            periodic_table_object.element_node_array[i]->right_valid = periodic_table_object.element_node_array[i + 1];
            periodic_table_object.element_node_array[i]->down_valid = 0;
        } else if (down_valid[i]) {
            periodic_table_object.element_node_array[i]->right_valid = 0;
            periodic_table_object.element_node_array[i]->down_valid = periodic_table_object.element_node_array[i + next_row];
        } else if (no_valid[i]) {
            periodic_table_object.element_node_array[i]->right_valid = 0;
            periodic_table_object.element_node_array[i]->down_valid = 0;
        }
        
    }
}