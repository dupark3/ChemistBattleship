#ifndef GUARD_AI_h
#define GUARD_AI_h

#include "player.h"

class AI : public player {
public: 
    AI(std::string s);
private:
    // each node contains a number for the probability of a ship being at that location
    // each node contains an int for unknown ship 0, hit ship 1, miss ship -1
    // each node contains a pointer to the one to the left, right, above, and below
    // randomly pick the node with the highest probability
    // if neighbor to a hit, add 20 to probability?
    std::map<int, std::vector<AIs_node> > AI_periodic_table; // possibilities mapped to each node
    void calculate_possibilities(int);
};

class AIs_node{
public:
    AIs_node() { }
private:
    element_node* element_node_ptr;
    int ship_presence; // 0 if unknown, +1 if hit, -1 if missed
    int possibilities;
};

#endif