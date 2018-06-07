#ifndef GUARD_gameboard_h
#define GUARD_gameboard_h

#include <string>
#include <vector>

class display_driver{
    public:
        display_driver();

        void print_periodic_tables();
        void place_ship(const std::vector<std::string>&);
        void enemy_shot(int, bool);
        void player_shot(int, bool);
    private:
        std::vector<std::string> symbols;
        std::vector<char*> ship_status;
        std::vector<char*> shot_status;
        
        std::string ship_emoji = "⛵ ";
        std::string hit_emoji = "🔥 ";
        std::string sunk_emoji = "🔥🔥";
        std::string miss_emoji = "❌ ";

        int X_bombs;
        bool short_form_bonus;
};

#endif