#ifndef GUARD_AI_h
#define GUARD_AI_h

#include "player.h"

class AI : public player {
public: 
    AI(std::string s) : player(s) { }
    std::string take_educated_shot(const player&);
private:
    
};

#endif