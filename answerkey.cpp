
#include <cstdlib> // exit
#include <fstream> // ifstream
#include <iostream> // cerr
#include <map>
#include <string>

#include "answerkey.h"

using namespace std;

// global map objects defined here and externally linked
std::map<std::string, int> atomic_numbers;
std::string element_symbols[19];
std::map<int, std::string> electron_configs;

void load_periodic_table(){
    ifstream PeriodicTable;
    PeriodicTable.open("abridged_periodictable.txt");

    if (!PeriodicTable){
        cerr << "Unable to open periodic table file";
        exit(1);
    }

    int atomic_number;
    while(PeriodicTable >> atomic_number){
        // read symbol and store into atomic_numbers hashmap
        string element_symbol;
        PeriodicTable >> element_symbol;
        atomic_numbers[element_symbol] = atomic_number;
        element_symbols[atomic_number] = element_symbol;
        
        // nothing to do with element name yet. read and do nothing. 
        string element_name;
        PeriodicTable >> element_name;

        // read electron config and store into electron_configs hashmap
        string electron_config;
        PeriodicTable >> electron_config;
        electron_configs[atomic_number] = electron_config;
    }
    
}