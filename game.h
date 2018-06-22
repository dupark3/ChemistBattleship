#ifndef GUARD_game_h
#define GUARD_game_h

#include <map>
#include <unordered_map>
#include <string>
#include <vector>

#include "AI.h"
#include "gameboard.h"
#include "player.h"
#include "periodic_table.h"

#define MAX_ELEMENT 118

class Game{
public:
    Game();
    
    void setup();
    void run();
private:
    player player1;
    AI player2;

    std::string player1name;
    std::string player2name;
    
    display_driver display;
    std::string game_text;

    
};

#endif