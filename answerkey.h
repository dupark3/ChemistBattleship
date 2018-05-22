// Contians two maps objects with periodic table's info

#ifndef GUARD_answerkey_h
#define GUARD_answerkey_h

#include <map>
#include <string>

class periodic_table;

const int MAX_ELEMENT = 18;

// extern keyword used to create global map objects
extern periodic_table periodic_table_object;
extern std::map<std::string, int> atomic_numbers; // map element symbol to atomic number
extern std::map<std::string, int> electron_configs_reverse; // map electron config to atomic number
// extern std::string element_symbols[19]; // array of element symbols indexed by their atomic number
// extern std::map<int, std::string> electron_configs; // map atomic number to electron config

class element_node{
public:
    element_node() : element_symbol(""), electron_configuration(""), 
                     player1_ship(false), player2_ship(false),
                     valid_right_ship(0), valid_down_ship(0) { }
private:
    std::string element_symbol;
    std::string electron_configuration;
    std::string element_name;
    
    // true if player has a ship on this element block
    bool player1_ship;
    bool player2_ship;

    // pointer to the nods on the right and below this node. 
    // allows us to check if two nodes can be part of one ship. 
    element_node* valid_right_ship;
    element_node* valid_down_ship;
};

class periodic_table{
friend void load_periodic_table();
public:
    periodic_table() { }
private:
    // array index 0 is left empty in order to match the index with the atomic number
    element_node* element_node_array[MAX_ELEMENT + 1];
};

void load_periodic_table();

#endif