#ifndef GUARD_answerkey_h
#define GUARD_answerkey_h

#include <cstdlib> // exit
#include <fstream> // ifstream
#include <iostream> // cerr
#include <map>
#include <string>

static std::map<std::string, int> atomic_numbers;
static std::map<int, std::string> electron_configs;

ifstream PeriodicTable;

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

#endif