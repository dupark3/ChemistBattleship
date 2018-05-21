#ifndef GUARD_player_h
#define GUARD_player_h

#include <map>
#include <string>

class ship;

class player{
public:
    player() : name(), ships() { }
    player(std::string s) : name(s), ships() { }

    void place_ship(const std::string&);
    void place_ship(int);
    void place_ship_randomly(int);
    bool check_shot(const std::string&);

private:
    std::string name;
    std::map<std::string, ship*> ships; // map of electron config to a node of ship info
};


class ship{
// REFACTOR: hide these memebers to private
public: 
    ship() : atomic_number(0), element_symbol(""), status(false) { }
    ship(int n, std::string s) : atomic_number(n), element_symbol(s), status(true) { }
    int atomic_number;
    std::string element_symbol;
    bool status;
};

#endif