#include "periodic_table.h"

using namespace std;

// global map objects defined here and externally linked
map<string, int> atomic_number_from_symbol;
map<string, int> atomic_number_from_config;
vector<element_node*> element_node_vector;

// load_periodic_table() defined in header file to avoid linker error

int next_rows_atomic_number(int atomic_number){
    if (atomic_number == 1){
        return atomic_number + 2;
    } else if (atomic_number >= 2 && atomic_number <= 12){
        return atomic_number + 8;
    } else if (atomic_number >= 13 && atomic_number <= 38){
        return atomic_number + 18;
    } else if (atomic_number >= 39 && atomic_number <= 86){
        return atomic_number + 32;
    } else {
        return 0;
    }
}