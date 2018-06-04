#ifndef GUARD_periodic_table_h
#define GUARD_periodic_table_h

#include <fstream> // ifstream
#include <iostream> // cerr
#include <map>
#include <string>
#include <vector>

// forward declarations
class element_node;

// global variables

const int MAX_ELEMENT = 118;

extern std::map<std::string, int> atomic_number_from_symbol; // map element symbol to atomic number
extern std::map<std::string, int> atomic_number_from_config; // map electron config to atomic number
extern std::vector<element_node*> element_node_vector; // array index 0 is empty. index = atomic number


/**************** class element_node *******************/

class element_node{

    template <class T>
    friend void load_periodic_table(std::vector<T*>&);
    friend void calculate_possibilities();
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

    private:
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

int next_rows_atomic_number(int);

template <class T>
void load_periodic_table(std::vector<T*>& node_vector){
    std::ifstream PeriodicTableFileStream;
    PeriodicTableFileStream.open("periodictable.txt");

    if (!PeriodicTableFileStream){
        std::cerr << "Unable to open periodic table file";
        std::exit(1);
    }

    // insert empty node into index 0 since there is no element at atomic number 0
    T* empty_element_node = new T;
    node_vector.push_back(empty_element_node);

    // read and load info
    int atomic_number;

    while(PeriodicTableFileStream >> atomic_number){
        // allocate memory for an element_node. 
        T* new_element_node = new T;
        node_vector.push_back(new_element_node);
        node_vector[atomic_number]->atomic_number = atomic_number;

        // read symbol and store into element_node and atomic_numbers_from_symbol hashmap
        std::string element_symbol;
        PeriodicTableFileStream >> element_symbol;
        node_vector[atomic_number]->element_symbol = element_symbol;
        atomic_number_from_symbol[element_symbol] = atomic_number;

        // read name and store into element_node 
        std::string element_name;
        PeriodicTableFileStream >> element_name;
        node_vector[atomic_number]->element_name = element_name;

        // read config and store into element_node and atomic_numbers_from_config hashmap
        std::string electron_config;
        PeriodicTableFileStream >> electron_config;
        node_vector[atomic_number]->electron_config = electron_config;
        atomic_number_from_config[electron_config] = atomic_number;
    }

    // set correct pointers to adjacent nodes to the right, left, below, above
    for(int i = 1; i != MAX_ELEMENT + 1; ++i){
        // four types resulting from the possibility of a valid/invalid right/down neighbors
        std::map<int, bool> both_valid  = { {3, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1},
        {9, 1}, {11, 1}, {13, 1}, {14, 1}, {15, 1}, {16, 1}, {17, 1}, {19, 1}, 
        {20,1}, {21, 1}, {22, 1}, {23, 1}, {24, 1}, {25, 1}, {26, 1}, {27, 1}, 
        {28, 1},{29, 1}, {30, 1}, {31, 1}, {32, 1}, {33, 1}, {34, 1}, {35, 1}, 
        {37, 1}, {38,1}, {39, 1}, {40, 1}, {41, 1}, {42, 1}, {43, 1}, {44, 1}, 
        {45, 1}, {46, 1},{47, 1}, {48, 1}, {49, 1}, {50, 1}, {51, 1}, {52, 1}, 
        {53, 1}, {55, 1}, {56,1}, {71, 1}, {72, 1}, {73, 1}, {74, 1}, {75, 1}, 
        {76, 1}, {77, 1}, {78, 1},{79, 1}, {80, 1}, {81, 1}, {82, 1}, {83, 1}, 
        {84, 1}, {85, 1}, {57, 1}, {58, 1}, {59,1}, {60, 1}, {61, 1}, {62, 1}, 
        {63, 1}, {64, 1}, {65, 1}, {66, 1}, {67, 1},{68, 1}, {69, 1} };

        std::map<int, bool> right_valid = { {87, 1}, {88, 1}, {103, 1}, {104, 1 },
        {105, 1}, {106, 1}, {107, 1}, {108, 1}, {109, 1}, {110, 1}, {111, 1}, 
        {112, 1}, {113, 1}, {114, 1}, {115, 1}, {116, 1}, {117, 1}, {89, 1 }, 
        {90, 1}, {91,1}, {92, 1}, {93, 1}, {94, 1}, {95, 1}, {96, 1}, {97, 1}, 
        {98, 1}, {99, 1},{100, 1}, {101, 1} };

        std::map<int, bool> down_valid  = { {1, 1}, {2, 1}, {4, 1}, {10, 1}, {12,1},
        {18, 1}, {36, 1}, {54, 1}, {86, 1}, {70, 1} } ;

        std::map<int, bool> no_valid    = { {118, 1}, {102, 1} };
        
        int next_row = next_rows_atomic_number(i);

        if (both_valid[i]) {
            node_vector[i]->right_ship = node_vector[i + 1];
            node_vector[i + 1]->left_ship = node_vector[i];
            node_vector[i]->below_ship = node_vector[next_row];
            node_vector[next_row]->above_ship = node_vector[i];
        } else if (right_valid[i]) {
            node_vector[i]->right_ship = node_vector[i + 1];
            node_vector[i + 1]->left_ship = node_vector[i];
            node_vector[i]->below_ship = 0;
        } else if (down_valid[i]) {
            node_vector[i]->right_ship = 0;
            node_vector[i]->below_ship = node_vector[next_row];
            node_vector[next_row]->above_ship = node_vector[i];
        } else if (no_valid[i]) {
            node_vector[i]->right_ship = 0;
            node_vector[i]->below_ship = 0;
        }
    }
    
    // fix transition from 6s/7s to 5d/6d
    node_vector[56]->right_ship = node_vector[71];
    node_vector[71]->left_ship = node_vector[56];
    node_vector[88]->right_ship = node_vector[103];
    node_vector[103]->left_ship = node_vector[88];
    
}

void print_periodic_table();



#endif