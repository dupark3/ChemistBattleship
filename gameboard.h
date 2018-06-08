#ifndef GUARD_gameboard_h
#define GUARD_gameboard_h

#include <string>
#include <vector>

#include "player.h"

class display_driver{
    public:
        display_driver();

        void set_players(const player&, const player&);

        void print_periodic_tables();

        void place_ship(const std::vector<std::string>&);
        void enemy_shot(int, bool);
        void player_shot(int, bool);

        void enemy_ship_sunk(const std::string&, const player&);
        void player_ship_sunk(const std::string&, const player&);

    private:
        std::vector<std::string> symbols;
        std::vector<char*> ship_status;
        std::vector<char*> shot_status;
        
        std::string ship_emoji = "⛵ ";
        std::string hit_emoji = "🔥 ";
        std::string sunk_emoji = "🔥🔥";
        std::string miss_emoji = "❌ ";

        const player* player1_pointer;
        const player* player2_pointer;
};

#endif