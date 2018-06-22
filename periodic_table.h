#ifndef GUARD_periodic_table_h
#define GUARD_periodic_table_h

#include <fstream> // ifstream
#include <iostream> // cerr
#include <map>
#include <string>
#include <vector>

// forward declarations
class element_node;

// answer keys
extern std::vector<element_node*> element_node_vector; // array index 0 is empty. index = atomic number
extern std::map<std::string, int> atomic_number_from_symbol; // map element symbol to atomic number
extern std::map<std::string, int> atomic_number_from_config; // map electron config to atomic number

/**************** nonmebmer function *******************/
std::string convert_to_long_form(const std::string&);

/**************** class element_node *******************/

class element_node{
    friend class AI;
    friend class player;

    public:
        // Default constructor
        element_node() : atomic_number(0), element_symbol(), electron_config(), element_name(), 
                         right_ship(0), below_ship(0), left_ship(0), above_ship(0) { }

        // Accessor member functions
        int get_atomic_number() { return atomic_number; }
        std::string get_element_symbol() { return element_symbol; }
        std::string get_electron_config() { return electron_config; }
        std::string get_element_name() { return element_name; }
        element_node* get_left_ship() { return left_ship; }
        element_node* get_right_ship() { return right_ship; }
        element_node* get_above_ship() { return above_ship; }
        element_node* get_below_ship() { return below_ship; }

    
        int atomic_number;
        std::string element_symbol;
        std::string electron_config;
        std::string element_name;

        // Pointers to the neighboring element_nodes. 0 if no neighbor.
        element_node* left_ship;
        element_node* right_ship;
        element_node* above_ship;
        element_node* below_ship;
};



/**************** nonmember functions *******************/




#endif