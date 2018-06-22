#include "periodic_table.h"

using namespace std;

// answer keys
vector<element_node*> element_node_vector; // array index 0 is empty. index = atomic number
map<string, int> atomic_number_from_symbol; // map element symbol to atomic number
map<string, int> atomic_number_from_config; // map electron config to atomic number

string convert_to_long_form(const string& short_hand_config){
    string long_hand_config;
    
    // if short_hand is smaller than 4, it can't be a valid config. prevent seg fault by exiting.
    if (short_hand_config.size() < 4){
        return short_hand_config;
    }

    map<string, int> noble_gases = { {"[He]", 1}, {"[Ne]", 2}, 
                                     {"[Ar]", 3}, {"[Kr]", 4}, 
                                     {"[Xe]", 5}, {"[Rn]", 6}, 
                                     {"[Og]", 7} };

    // if the first four letters are a noble gas in brackets, 
    //convert it to its config in long form
    switch (noble_gases[short_hand_config.substr(0,4)]){
        case 1:
            long_hand_config = "1s2";
            break;
        case 2:
            long_hand_config = "1s2.2s2.2p6";
            break;
        case 3:
            long_hand_config = "1s2.2s2.2p6.3s2.3p6";
            break;
        case 4:
            long_hand_config = "1s2.2s2.2p6.3s2.3p6.4s2.3d10.4p6";
            break;
        case 5:
            long_hand_config = "1s2.2s2.2p6.3s2.3p6.4s2.3d10.4p6.5s2.4d10.5p6";
            break;
        case 6:
            long_hand_config = "1s2.2s2.2p6.3s2.3p6.4s2.3d10.4p6.5s2.4d10.5p6.6s2.4f14.5d10.6p6";
            break;
        case 7:
            long_hand_config = "1s2.2s2.2p6.3s2.3p6.4s2.3d10.4p6.5s2.4d10.5p6.6s2.4f14.5d10.6p6.7s2.5f14.6d10.7p6";
            break;
        default:
            return short_hand_config;
    }
    
    // if there are more than 4 letters, it must have trailing config after noble gas [??]
    if (short_hand_config.size() > 4){
        long_hand_config = long_hand_config + "." + short_hand_config.substr(4);
    }

    return long_hand_config;
}

 
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
