#ifndef GUARD_AI_h
#define GUARD_AI_h

#include "player.h"

class AI : public player {
public: 
    AI(std::string s) : player(s) { }
    std::string take_educated_shot(const player&);
    void hit(const player&, int);
    void missed(const player&, int);
private:
    void recalculate_possibilities(const player&, int);
    void recalculate_after_hit(const player&, int);
    void recalculate_after_miss_or_sink(const player&, int);
};

#endif