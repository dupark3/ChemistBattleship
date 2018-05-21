// Contians two maps objects with periodic table's info

#ifndef GUARD_answerkey_h
#define GUARD_answerkey_h

#include <map>
#include <string>

// extern keyword used to create global map objects
extern std::map<std::string, int> atomic_numbers; // map element symbol to atomic number
extern std::string element_symbols[19]; // array of element symbols indexed by their atomic number
extern std::map<int, std::string> electron_configs; // map atomic number to electron config

void load_periodic_table();

#endif