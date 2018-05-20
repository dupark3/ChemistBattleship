
#include <cstdlib> // exit
#include <fstream> // ifstream
#include <iostream> // cerr
#include <map>
#include <string>

#include "answerkey.h"

using namespace std;

void load_periodic_table(){
    cout << "Loading periodic table... " << endl;
    ifstream PeriodicTable;

    PeriodicTable.open("abridged_periodictable.txt");
    if (!PeriodicTable){
        cerr << "Unable to open periodic table file";
        exit(1);
    }

    int atomic_number;
    while(PeriodicTable >> atomic_number){
        // read symbol and store into atomic_numbers hashmap
        cout << "Reading atomic number " << atomic_number << endl;
        string element_symbol;
        PeriodicTable >> element_symbol;
        cout << "Reading element symbol " << element_symbol << endl;
        atomic_numbers[element_symbol] = atomic_number;

        // nothing to do with element name yet. read and dump.
        string element_name;
        PeriodicTable >> element_name;

        // read electron config and store into electron_configs hashmap
        string electron_config;
        PeriodicTable >> electron_config;
        cout << "Reading electron config " << electron_config << endl;
        electron_configs[atomic_number] = electron_config;
    }
}