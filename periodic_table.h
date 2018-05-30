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
friend void calculate_possibilities();
friend class AI;
public:
    element_node() : element_symbol(""), electron_config(""), 
                     right_ship(0), below_ship(0), left_ship(0), above_ship(0),
                     possibilities(0), status(0) { }
    int get_atomic_number() { return atomic_number; }
    std::string get_element_symbol() { return element_symbol; }
    std::string get_electron_config() { return electron_config; }
    std::string get_element_name() { return element_name; }
    element_node* get_right_ship() { return right_ship; }
    element_node* get_below_ship() { return below_ship; }
    element_node* get_left_ship() { return left_ship; }
    element_node* get_above_ship() { return above_ship; }
    
private:
    int atomic_number;
    std::string element_symbol;
    std::string electron_config;
    std::string element_name;

    // pointer to the nods on the right and below this node on the actual periodic table. 0 if not valid.
    element_node* right_ship;
    element_node* below_ship;
    element_node* left_ship;
    element_node* above_ship;

    int possibilities;
    int status; // 0 if unknown, 1 if hit, -1 if miss or sunk
};



/**************** nonmember functions *******************/

void load_periodic_table();
int next_rows_atomic_number(int);
void print_periodic_table();

void calculate_possibilities();

#endif