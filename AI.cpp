#include <iostream>
#include <map>
#include <string>

#include "AI.h" 

using namespace std;


vector<int> AI::place_ship_randomly(int size_of_ship){
    vector<int> ship_atomic_numbers;

    // Pass a random number between [1,118] as the first element until valid ship position found
    while (ship_atomic_numbers.empty()){
        ship_atomic_numbers = create_continuous_blocks(my_rand(118) + 1, size_of_ship);
    }

    map<string, bool> ship_map;
    for (int i = 0; i != size_of_ship; ++i){
        string electron_config = element_node_vector[ship_atomic_numbers[i]]->get_electron_config();
        ship_map[electron_config] = true;
    }
    
    ships.push_back(ship_map);
    ++number_of_ships;

    cout << "Ship of size " << size_of_ship << " placed at a random location." << endl;
    
    return ship_atomic_numbers;
}


vector<int> AI::create_continuous_blocks(int atomic_number, int size_of_ship){
    bool horizontal = my_rand(2);
    vector<int> ship_atomic_numbers;

    if (horizontal){
        for (int i = 0; i != size_of_ship; ++i){
            element_node* right_ship = element_node_vector[atomic_number]->get_right_ship();
            string electron_config = element_node_vector[atomic_number]->get_electron_config();

            // if current atomic number doesn't have a right neighbor OR 
            // if this player already has a ship at the current atomic number, return empty vec
            if (!right_ship || !check_unique(electron_config)){
                return { };
            } else {
                ship_atomic_numbers.push_back(atomic_number);
                atomic_number = right_ship->get_atomic_number();
            }
        }
    } else { 
        // vertical ship
        for (int i = 0; i != size_of_ship; ++i){
            element_node* below_ship = element_node_vector[atomic_number]->get_below_ship();
            string electron_config = element_node_vector[atomic_number]->get_electron_config();

            // if current atomic number doesn't have a down neighbor OR 
            // if this player already has a ship at the current atomic number, return empty vec
            if (!below_ship || !check_unique(electron_config)){
                return { };
            } else {
                ship_atomic_numbers.push_back(atomic_number);
                atomic_number = below_ship->get_atomic_number();
            }
        }
    }

    return ship_atomic_numbers;
}

string AI::take_educated_shot(){
    int max_possibility = 0;
    vector<element_node*> best_elements_to_shoot;

    for (int i = 1; i != 119; ++i){
        if (AI_element_node_vector[i]->possibilities > max_possibility && AI_element_node_vector[i]->status == 0){
            max_possibility = AI_element_node_vector[i]->possibilities;
            best_elements_to_shoot.clear();
            best_elements_to_shoot.push_back(AI_element_node_vector[i]);
        } else if (AI_element_node_vector[i]->possibilities == max_possibility) {
            best_elements_to_shoot.push_back(AI_element_node_vector[i]);
        }
    }
    
    int rand;
    
    // if no compelling location, 25% chance of hitting anywhere, 75% chance hitting high possibility
    int hit_high_or_low = my_rand(4);
    if (max_possibility <= 21 && hit_high_or_low == 0){
        do {
            rand = my_rand(118) + 1;    
        } while (AI_element_node_vector[rand]->status != 0);
        return AI_element_node_vector[rand]->get_electron_config();
    } else {
        rand = my_rand(best_elements_to_shoot.size());
        return best_elements_to_shoot[rand]->get_electron_config();
    }
    
}

void AI::hit(const player& player1, int atomic_number){
    ++hits;
    AI_element_node_vector[atomic_number]->status = 1;
    AI_element_node_vector[atomic_number]->possibilities = 0;

    recalculate_possibilities(player1, atomic_number);
}

void AI::missed(const player& player1, int atomic_number){
    ++misses;
    AI_element_node_vector[atomic_number]->status = -1;
    AI_element_node_vector[atomic_number]->possibilities = 0;
    recalculate_possibilities(player1, atomic_number);
}

void AI::recalculate_possibilities(const player& player1, int atomic_number){
    AI_element_node* element_pointer = AI_element_node_vector[atomic_number];
    string electron_config = element_pointer->get_electron_config();

    // if ship is sunk, convert the status of each element in the ship to -1 from 1
    if (player1.ship_sunk(electron_config)){
        // iterate through player1's vector until the correct map is found for this ship
        for (int i = 0; i != player1.ships.size(); ++i){
            if (player1.ships[i].find(electron_config) != player1.ships[i].cend()){
                for (auto j = player1.ships[i].begin(); j != player1.ships[i].end(); ++j){
                    int atomic_number = atomic_number_from_config[j->first];
                    AI_element_node_vector[atomic_number]->status = -1;
                    recalculate_after_miss_or_sink(player1, atomic_number);
                }
            }
        }
    }

    if (element_pointer->status == 1){
        recalculate_after_hit(player1, atomic_number);
    } else if (element_pointer->status == -1){
        recalculate_after_miss_or_sink(player1, atomic_number);
    }
}

void AI::recalculate_after_hit(const player& player1, int atomic_number){
    AI_element_node* element_pointer = AI_element_node_vector[atomic_number];
    
    // add 10 to possibilities of the above ship if it exsits
    if (element_pointer->above_ship && element_pointer->above_ship->status == 0){
        element_pointer->above_ship->possibilities += 10;
        
        // if right_ship exists and has already been hit, ship may be vertical. 
        if (element_pointer->below_ship && element_pointer->below_ship->status == 1){
            element_pointer->above_ship->possibilities += 20;
            if (element_pointer->below_ship->below_ship && element_pointer->below_ship->below_ship->status == 0){
                element_pointer->below_ship->below_ship->possibilities += 20;
            }
        }
    }

    // add 10 to possibilities of the below ship if it exists
    if (element_pointer->below_ship && element_pointer->below_ship->status == 0){
        element_pointer->below_ship->possibilities += 10;
        
        // if above ship exists and has already been hit, ship may be vertical
        if (element_pointer->above_ship && element_pointer->above_ship->status == 1){
            element_pointer->below_ship->possibilities += 20;
            if (element_pointer->above_ship->above_ship && element_pointer->above_ship->above_ship->status == 0){
                element_pointer->above_ship->above_ship->possibilities += 20;
            }
        }
    }

    // add 10 to possibilities of the right_ship if it exists
    if (element_pointer->right_ship && element_pointer->right_ship->status == 0){
        element_pointer->right_ship->possibilities += 10;
        
        // if left ship exists and has already been hit, ship may be horizontal. 
        if (element_pointer->left_ship && element_pointer->left_ship->status == 1){
            element_pointer->right_ship->possibilities += 20;
            if (element_pointer->left_ship->left_ship && element_pointer->left_ship->left_ship->status == 0){
                element_pointer->left_ship->left_ship->possibilities += 20;
            }
        }
        
    }

    // add 10 to possibilities of the left ship if it exists
    if (element_pointer->left_ship && element_pointer->left_ship->status == 0){
        element_pointer->left_ship->possibilities += 10;

        // if right ship already hit, ship may be horizontal
        if (element_pointer->right_ship && element_pointer->right_ship->status == 1){
            element_pointer->left_ship->possibilities += 20;   
            if (element_pointer->right_ship->right_ship && element_pointer->right_ship->right_ship->status == 0){
                element_pointer->right_ship->right_ship->possibilities += 20;
            }
        }
    }
}

void AI::recalculate_after_miss_or_sink(const player& player1, int atomic_number){
    AI_element_node* element_pointer = AI_element_node_vector[atomic_number];

    // There are up to 24 possible ships that are affected due to a miss/sink
    // 24 different if statements written for readability. 

    // ship lies to the right only
    if (element_pointer->right_ship 
        && element_pointer->right_ship->right_ship){
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
    }
    if (element_pointer->right_ship 
        && element_pointer->right_ship->right_ship
        && element_pointer->right_ship->right_ship->right_ship){
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->right_ship->possibilities;
    }
    if (element_pointer->right_ship 
        && element_pointer->right_ship->right_ship
        && element_pointer->right_ship->right_ship->right_ship
        && element_pointer->right_ship->right_ship->right_ship->right_ship){
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->right_ship->right_ship->possibilities;
    }

    // ship lies to the left only
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
    }
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship
        && element_pointer->left_ship->left_ship->left_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->left_ship->possibilities;
    }
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship
        && element_pointer->left_ship->left_ship->left_ship
        && element_pointer->left_ship->left_ship->left_ship->left_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->left_ship->left_ship->possibilities;
    }

    // ship of size 3 stradles horizontally
    if (element_pointer->left_ship 
        && element_pointer->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
    }

    // ship of size 4 stradles horizontally
    if (element_pointer->left_ship 
        && element_pointer->right_ship
        && element_pointer->right_ship->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
    }
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship 
        && element_pointer->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
    }

    // ship of size 5 stradles horizontally
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship 
        && element_pointer->left_ship->left_ship->left_ship
        && element_pointer->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
    }
    if (element_pointer->left_ship 
        && element_pointer->left_ship->left_ship 
        && element_pointer->right_ship
        && element_pointer->right_ship->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->left_ship->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
    }
    if (element_pointer->left_ship 
        && element_pointer->right_ship
        && element_pointer->right_ship->right_ship
        && element_pointer->right_ship->right_ship->right_ship){
        --element_pointer->left_ship->possibilities;
        --element_pointer->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->possibilities;
        --element_pointer->right_ship->right_ship->right_ship->possibilities;
    }

    // ship lies to the above only  
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
    }
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship
        && element_pointer->above_ship->above_ship->above_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->above_ship->possibilities;
    }
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship
        && element_pointer->above_ship->above_ship->above_ship
        && element_pointer->above_ship->above_ship->above_ship->above_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->above_ship->above_ship->possibilities;
    }

    // ship lies to the below only
    if (element_pointer->below_ship 
        && element_pointer->below_ship->below_ship){
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
    }
    if (element_pointer->below_ship 
        && element_pointer->below_ship->below_ship
        && element_pointer->below_ship->below_ship->below_ship){
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->below_ship->possibilities;
    }
    if (element_pointer->below_ship 
        && element_pointer->below_ship->below_ship
        && element_pointer->below_ship->below_ship->below_ship
        && element_pointer->below_ship->below_ship->below_ship->below_ship){
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->below_ship->below_ship->possibilities;
    }

    // ship of size 3 stradles vertically
    if (element_pointer->above_ship 
        && element_pointer->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
    }

    // ship of size 4 stradles vertically
    if (element_pointer->above_ship 
        && element_pointer->below_ship
        && element_pointer->below_ship->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
    }
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship 
        && element_pointer->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
    }

    // ship of size 5 stradles vertically
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship 
        && element_pointer->above_ship->above_ship->above_ship
        && element_pointer->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
    }
    if (element_pointer->above_ship 
        && element_pointer->above_ship->above_ship 
        && element_pointer->below_ship
        && element_pointer->below_ship->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->above_ship->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
    }
    if (element_pointer->above_ship 
        && element_pointer->below_ship
        && element_pointer->below_ship->below_ship
        && element_pointer->below_ship->below_ship->below_ship){
        --element_pointer->above_ship->possibilities;
        --element_pointer->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->possibilities;
        --element_pointer->below_ship->below_ship->below_ship->possibilities;
    }
}


void AI::calculate_possibilities(){
    for (int i = 1; i != 119; ++i){
        AI_element_node* node = AI_element_node_vector[i];

        // These two if-statements are a combination of six possibilities.
        // Less readable, a bit condensed. 

        // if current element has at least two elements below, it can have a ship
        if (node->below_ship && node->below_ship->below_ship){
            int ship_count = 1;
            if (node->below_ship->below_ship->below_ship){
                ++ship_count;
                if (node->below_ship->below_ship->below_ship->below_ship){
                    ++ship_count;
                    // if a five ship can exist, add one to the fifth element here
                    ++node->below_ship->below_ship
                                     ->below_ship->below_ship
                                     ->possibilities;
                }
                // the fourth element gets ship_count - 1 added since it is not part of the three-block ship
                node->below_ship->below_ship->below_ship->possibilities += ship_count - 1;
            }
            // first three elements get the ship_count added since they are part of every ship
            node->possibilities += ship_count;
            node->below_ship->possibilities += ship_count;
            node->below_ship->below_ship->possibilities += ship_count;
        }
    
        // if current element has at least two elements to the right, it can have a ship
        if (node->right_ship && node->right_ship->right_ship){
            int ship_count = 1;
            if (node->right_ship->right_ship->right_ship){
                ++ship_count;
                if (node->right_ship->right_ship->right_ship->right_ship){
                    ++ship_count;
                    // if a five ship can exist, add one to the fifth element here
                    ++node->right_ship->right_ship
                                     ->right_ship->right_ship
                                     ->possibilities;
                }
                // the fourth element gets ship_count - 1 added since it is not part of the three-block ship
                node->right_ship->right_ship->right_ship->possibilities += ship_count - 1;
            }
            // first three elements get the ship_count added since they are part of every ship
            node->possibilities += ship_count;
            node->right_ship->possibilities += ship_count;
            node->right_ship->right_ship->possibilities += ship_count;
        }
    }
}

int AI::next_rows_atomic_number(int atomic_number){
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

void AI::load_periodic_table(vector<AI_element_node*>& AI_node_vector){
    std::ifstream PeriodicTableFileStream;
    PeriodicTableFileStream.open("periodictable.txt");

    if (!PeriodicTableFileStream){
        std::cerr << "Unable to open periodic table file";
        std::exit(1); // throw exception here instead?
    }

    // insert empty node into index 0 since there is no element at atomic number 0
    AI_element_node* empty_element_node = new AI_element_node;
    AI_node_vector.push_back(empty_element_node);

    // read and load info
    int atomic_number;

    while(PeriodicTableFileStream >> atomic_number){
        // allocate memory for an element_node. 
        AI_element_node* new_element_node = new AI_element_node;
        AI_node_vector.push_back(new_element_node);
        AI_node_vector[atomic_number]->atomic_number = atomic_number;

        // read symbol and store into element_node 
        string element_symbol;
        PeriodicTableFileStream >> element_symbol;
        AI_node_vector[atomic_number]->element_symbol = element_symbol;

        // read name and store into element_node 
        string element_name;
        PeriodicTableFileStream >> element_name;
        AI_node_vector[atomic_number]->element_name = element_name;

        // read config and store into element_node
        string electron_config;
        PeriodicTableFileStream >> electron_config;
        AI_node_vector[atomic_number]->electron_config = electron_config;
        
    }

    // set correct pointers to adjacent nodes to the right, left, below, above
    for(int i = 1; i != 119 + 1; ++i){
        
        // four types resulting from the possibility of a valid/invalid right/down neighbors
        // hard coding necessary here to represent the unique shape of the periodic table
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
            AI_node_vector[i]->right_ship = AI_node_vector[i + 1];
            AI_node_vector[i + 1]->left_ship = AI_node_vector[i];
            AI_node_vector[i]->below_ship = AI_node_vector[next_row];
            AI_node_vector[next_row]->above_ship = AI_node_vector[i];
        } else if (right_valid[i]) {
            AI_node_vector[i]->right_ship = AI_node_vector[i + 1];
            AI_node_vector[i + 1]->left_ship = AI_node_vector[i];
            AI_node_vector[i]->below_ship = 0;
        } else if (down_valid[i]) {
            AI_node_vector[i]->right_ship = 0;
            AI_node_vector[i]->below_ship = AI_node_vector[next_row];
            AI_node_vector[next_row]->above_ship = AI_node_vector[i];
        } else if (no_valid[i]) {
            AI_node_vector[i]->right_ship = 0;
            AI_node_vector[i]->below_ship = 0;
        }
    }
    
    // fix transition from 6s/7s to 5d/6d
    AI_node_vector[56]->right_ship = AI_node_vector[71];
    AI_node_vector[71]->left_ship = AI_node_vector[56];
    AI_node_vector[88]->right_ship = AI_node_vector[103];
    AI_node_vector[103]->left_ship = AI_node_vector[88];
    
}

// NON MEMBER FUNCTION

int my_rand(int max){
    int random_number;
    int bucket_size = RAND_MAX / max;
    do{
        random_number = rand() / bucket_size;
    } while (random_number > max);

    return random_number;
}