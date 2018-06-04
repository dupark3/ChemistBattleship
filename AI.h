#ifndef GUARD_AI_h
#define GUARD_AI_h

#include <vector>

#include "player.h" // AI class inherits player class 
#include "periodic_table.h" // AI_element_node class inherits element_node class

// forward declarations
class AI_element_node;

class AI : public player {
    // friend declarations
        friend class AI_element_node;
        template <class T> friend void load_periodic_table(std::vector<T*>&);

    public: 
        AI() : player() { }
        AI(std::string s) : player(s) { 
            load_periodic_table(AI_element_node_vector);
            calculate_possibilities(); 
        }
        // need destructor to avoid major memory leak
        /*~AI() {
            for (int i = 0; i != 119; ++i){
                delete AI_element_node_vector[i];
            }
        }*/

        std::string take_educated_shot();
        void hit(const player&, int);
        void missed(const player&, int);

    private:
        std::vector<AI_element_node*> AI_element_node_vector;
        void calculate_possibilities();
        void recalculate_possibilities(const player&, int);
        void recalculate_after_hit(const player&, int);
        void recalculate_after_miss_or_sink(const player&, int);
};


/* AI_element_node and a vector of AI_element_node pointers is used to support
the calculation of the number of possible ships on any given element block. */
class AI_element_node : public element_node {
    // friend declarations
        friend class AI;
        template <class T> friend void load_periodic_table(std::vector<T*>&);

    public: 
        AI_element_node() : right_ship(0), below_ship(0), left_ship(0), above_ship(0),
                            possibilities(0), status(0) { }

    private:
        AI_element_node* left_ship;
        AI_element_node* right_ship;
        AI_element_node* above_ship;
        AI_element_node* below_ship;

        int possibilities;
        int status;
};

#endif