#ifndef GUARD_periodic_table_h
#define GUARD_periodic_table_h

#include <map>
#include <string>

class element_node;

/**************** global variables *******************/

const int MAX_ELEMENT = 118;

extern std::map<std::string, int> atomic_number_from_symbol; // map element symbol to atomic number
extern std::map<std::string, int> atomic_number_from_config; // map electron config to atomic number

// array index 0 is left empty in order to match the index with the atomic number
extern element_node* element_node_array[MAX_ELEMENT + 1];



/**************** class element_node *******************/

class element_node{
friend void load_periodic_table();
public:
    element_node() : element_symbol(""), electron_config(""), 
                     right_ship(0), down_ship(0) { }
    int get_atomic_number() { return atomic_number; }
    std::string get_element_symbol() { return element_symbol; }
    std::string get_electron_config() { return electron_config; }
    std::string get_element_name() { return element_name; }
    element_node* get_right_ship() { return right_ship; }
    element_node* get_down_ship() { return down_ship; }
private:
    int atomic_number;
    std::string element_symbol;
    std::string electron_config;
    std::string element_name;

    // pointer to the nods on the right and below this node on the actual periodic table. 0 if not valid.
    element_node* right_ship;
    element_node* down_ship;
};



/**************** nonmember functions *******************/

void load_periodic_table();
void print_periodic_table();

#endif