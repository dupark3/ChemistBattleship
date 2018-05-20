#ifndef GUARD_player_h
#define GUARD_player_h

#include <map>
#include <string>

class player{
public:
    player() : name(), ships() { }
    player(std::string s) : name(s), ships() { }

    void place_ship(std::string);
    void place_ship(int);

private:
    std::string name;
    std::map<int, bool> ships;
};

#endif