/*
TODO:
☑ AI places one 3-block ship randomly
☑ Use srand() and seed with time to be more random
☑ Expand the periodic table
☑ Place multiple ships
☑ Fix the 6s-4f and 7s-5f transition
☑ Prevent adding ships on the same spot or overlapping
☑ Use bucket method to make rand() more evenly random
☑ Make player class contain a vector of map of ships instead allow "sunk" info (change num of ships)
☑ Unlink 3p down_ship to 3d. 3p should be linked to 4p
☑ Refactor int next_row(int atomic_number) to return the atomic number of the element below (0 if not found)
☑ Place ships of varying sizes
☑ AI class created that inherits the player class
☑ Make AI smarter by shooting around a HIT (check left/right/up/down) until a ship is sunk
☑ Remove dependency of AI class on element_node class (inherit and use load_periodic_table())
☑ Build game text instead of only having a line or two after each system("clear")
☑ Press enter to continue from round to round
☑ Player sink doesn't change emoji
☑ Don't need to pass player object to sunk ship in display since it has player pointers
☐ Recalculate after sink should recalculate the entire board maybe since it doesn't subtract 10/20 from hits

Extra Features:
☑ Print the periodic table on console at set-up phase
☑ Add % for how accurate your shots were
☑ Earn special bomb if you identify other person's guess correctly 5 times in a row
☑ Add special bomb that explodes in an X sign
☑ Allow short-hand electron config after five consecutive non-misfires
☑ Provide a periodic table board that keeps track of hits/misses/sinks for the user
☐ Implement multiplayer (choice between playing against computer or another person)

*/


#include <cstdlib> // srand(), rand(), 
#include <ctime> // time() to seed srand()
#include <iostream>

#include "game.h"

using namespace std;

int main(){
    load_periodic_table(element_node_vector);
    cout << "main CHECK" << endl;
    Game game;
    game.setup();
    game.run();
    return 0;
}