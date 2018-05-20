
#include <cstdlib> // exit
#include <fstream> // ifstream
#include <iostream> // cerr
#include <map>
#include <string>

#include "answerkey.h"

void load_periodic_table(){
    std::ifstream PeriodicTable;

    PeriodicTable.open("abridged_periodictable.txt");
    if (!PeriodicTable){
        std::cerr << "Unable to open periodic table file";
        std::exit(1);
    }

    int atomic_number;
    while(PeriodicTable >> atomic_number){
        // read symbol and store into atomic_numbers hashmap
        std::string element_symbol;
        PeriodicTable >> element_symbol;
        atomic_numbers[element_symbol] = atomic_number;

        // nothing to do with element name yet. read and dump.
        std::string element_name;
        PeriodicTable >> element_name;

        // read electron config and store into electron_configs hashmap
        
    }
}