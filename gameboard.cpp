#include <chrono> // chrono::milliseconds(ms)
#include <thread> // this_thread::sleep_for

#include "AI.h"
#include "gameboard.h"
#include "periodic_table.h"

using namespace std;

display_driver::display_driver()  {
    // reserve enough space to prevent reallocation
    symbols.reserve(119);
    ship_status.reserve(119);
    shot_status.reserve(119);

    // off set index by one to match atomic number
    symbols.push_back("");
    ship_status.push_back(&symbols[0][0]);
    shot_status.push_back(&symbols[0][0]);

    // store element symbols in the vectors
    for (int i = 1; i != 119; ++i){
        string temp = element_node_vector[i]->get_element_symbol();
        if (temp.size() == 1){
            temp.push_back(' ');
        }
        symbols.push_back(temp);
        ship_status.push_back(&symbols[i][0]);
        shot_status.push_back(&symbols[i][0]);
    }

    // Utility support for viewing AI's possibilities calculations
    possibilities_string.reserve(119);
    possibilities_status.reserve(119);
    
    possibilities_string.push_back("");
    possibilities_status.push_back(&possibilities_string[0][0]);   
}

void display_driver::set_players(const player& player1, const AI& player2){
    player1_pointer = &player1;
    player2_pointer = &player2;
}

void display_driver::print_periodic_tables(const string& game_text){
    // ncurses lib had problems interacting with the stdlib
    // using system for now instead
    system("clear");

    // Using printf and C style to hold the place of element symbol
    printf("\n");
    printf("                     YOUR SHIPS                                                  YOUR SHOTS/MISSES\n");
    printf(" ╔══╗                                               ╔══╗      ╔══╗                                               ╔══╗\n"); 
    printf("1║%s║                                               ║%s║     1║%s║                                               ║%s║ \n", ship_status[1], ship_status[2], shot_status[1], shot_status[2]);
    printf(" ╠══╬══╗                             ╔══╦══╦══╦══╦══╬══╣      ╠══╬══╗                             ╔══╦══╦══╦══╦══╬══╣\n");
    printf("2║%s║%s║                             ║%s║%s║%s║%s║%s║%s║     2║%s║%s║                             ║%s║%s║%s║%s║%s║%s║\n", ship_status[3], ship_status[4], ship_status[5], ship_status[6], ship_status[7], ship_status[8], ship_status[9], ship_status[10], shot_status[3], shot_status[4], shot_status[5], shot_status[6], shot_status[7], shot_status[8], shot_status[9], shot_status[10]);
    printf(" ╠══╬══╣                             ╠══╬══╬══╬══╬══╬══╣      ╠══╬══╣                             ╠══╬══╬══╬══╬══╬══╣\n");
    printf("3║%s║%s║                             ║%s║%s║%s║%s║%s║%s║     3║%s║%s║                             ║%s║%s║%s║%s║%s║%s║\n", ship_status[11], ship_status[12], ship_status[13], ship_status[14], ship_status[15], ship_status[16], ship_status[17], ship_status[18], shot_status[11], shot_status[12], shot_status[13], shot_status[14], shot_status[15], shot_status[16], shot_status[17], shot_status[18]);
    printf(" ╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣      ╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣\n");
    printf("4║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     4║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", ship_status[19], ship_status[20], ship_status[21], ship_status[22], ship_status[23], ship_status[24], ship_status[25], ship_status[26], ship_status[27], ship_status[28], ship_status[29], ship_status[30], ship_status[31], ship_status[32], ship_status[33], ship_status[34], ship_status[35], ship_status[36], shot_status[19], shot_status[20], shot_status[21], shot_status[22], shot_status[23], shot_status[24], shot_status[25], shot_status[26], shot_status[27], shot_status[28], shot_status[29], shot_status[30], shot_status[31], shot_status[32], shot_status[33], shot_status[34], shot_status[35], shot_status[36]);
    printf(" ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣      ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("5║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     5║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", ship_status[37], ship_status[38], ship_status[39], ship_status[40], ship_status[41], ship_status[42], ship_status[43], ship_status[44], ship_status[45], ship_status[46], ship_status[47], ship_status[48], ship_status[49], ship_status[50], ship_status[51], ship_status[52], ship_status[53], ship_status[54], shot_status[37], shot_status[38], shot_status[39], shot_status[40], shot_status[41], shot_status[42], shot_status[43], shot_status[44], shot_status[45], shot_status[46], shot_status[47], shot_status[48], shot_status[49], shot_status[50], shot_status[51], shot_status[52], shot_status[53], shot_status[54]);
    printf(" ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣      ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("6║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     6║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", ship_status[55], ship_status[56], ship_status[71], ship_status[72], ship_status[73], ship_status[74], ship_status[75], ship_status[76], ship_status[77], ship_status[78], ship_status[79], ship_status[80], ship_status[81], ship_status[82], ship_status[83], ship_status[84], ship_status[85], ship_status[86], shot_status[55], shot_status[56], shot_status[71], shot_status[72], shot_status[73], shot_status[74], shot_status[75], shot_status[76], shot_status[77], shot_status[78], shot_status[79], shot_status[80], shot_status[81], shot_status[82], shot_status[83], shot_status[84], shot_status[85], shot_status[86]);
    printf(" ╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣      ╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("7║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     7║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", ship_status[87], ship_status[88], ship_status[103], ship_status[104], ship_status[105], ship_status[106], ship_status[107], ship_status[108], ship_status[109], ship_status[110], ship_status[111], ship_status[112], ship_status[113], ship_status[114], ship_status[115], ship_status[116], ship_status[117], ship_status[118], shot_status[87], shot_status[88], shot_status[103], shot_status[104], shot_status[105], shot_status[106], shot_status[107], shot_status[108], shot_status[109], shot_status[110], shot_status[111], shot_status[112], shot_status[113], shot_status[114], shot_status[115], shot_status[116], shot_status[117], shot_status[118]);
    printf(" ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝      ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝\n");
    printf("       ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗                  ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗\n");
    printf("       ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║                  ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", ship_status[57], ship_status[58], ship_status[59], ship_status[60], ship_status[61], ship_status[62], ship_status[63], ship_status[64], ship_status[65], ship_status[66], ship_status[67], ship_status[68], ship_status[69], ship_status[70], shot_status[57], shot_status[58], shot_status[59], shot_status[60], shot_status[61], shot_status[62], shot_status[63], shot_status[64], shot_status[65], shot_status[66], shot_status[67], shot_status[68], shot_status[69], shot_status[70]);
    printf("       ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣                  ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("       ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║                  ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", ship_status[89], ship_status[90], ship_status[91], ship_status[92], ship_status[93], ship_status[94], ship_status[95], ship_status[96], ship_status[97], ship_status[98], ship_status[99], ship_status[100], ship_status[101], ship_status[102], shot_status[89], shot_status[90], shot_status[91], shot_status[92], shot_status[93], shot_status[94], shot_status[95], shot_status[96], shot_status[97], shot_status[98], shot_status[99], shot_status[100], shot_status[101], shot_status[102]);
    printf("       ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝                  ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝\n");

    /* Uncomment if you want to see AI's possibilities
    update_possibilities_periodic_table();
    print_AI_possibilities();
    */

    cout << "                      X-BOMBS: " << player1_pointer->get_X_bombs() << endl
         << "             SHORT-FORM BONUS: ";
    if (player1_pointer->get_consecutive_correct_configs() >= 3){
        cout << "on" << endl;
    } else {
        cout << "off" << endl;
    }
    cout << " CORRECT CONFIGURATION STREAK: " 
         << player1_pointer->get_consecutive_correct_configs() << endl
         << "CORRECT IDENTIFICATION STREAK: " 
         << player1_pointer->get_correct_guesses() << endl;

    if (!player1_pointer->get_name().empty()){    
        cout << endl 
             << "            " << player1_pointer->get_name() << "    " << player2_pointer->get_name() << endl 
             << "  ACCURACY: " << player1_pointer->get_accuracy() << "%    " << player2_pointer->get_accuracy() << "%" << endl
             << "SHIPS LEFT: " << player1_pointer->ships_left() << "     " << player2_pointer->ships_left() << endl;    
    } else {
        cout << "\n\n\n\n";
    }
    
    cout << "******************************************************************************************************************" << endl;
    saved_game_text = game_text;
    cout << game_text;
}


void display_driver::place_ship(const vector<string>& ship_symbols){
    // convert symbols to ship emoji 
    for (int i = 0; i != ship_symbols.size(); ++i){
        int atomic_number = atomic_number_from_symbol[ship_symbols[i]];
        
        ship_status[atomic_number] = &ship_emoji[0];
    }
    print_periodic_tables(saved_game_text);
}

void display_driver::place_ship_enemy_debug(const vector<int>& atomic_numbers){
    // convert symbols to ship emoji 
    for (int i = 0; i != atomic_numbers.size(); ++i){
        shot_status[atomic_numbers[i]] = &ship_emoji[0];
    }
    print_periodic_tables(saved_game_text);
}

void display_driver::player_shot(int atomic_number, bool hit){
    if (hit){
        shot_status[atomic_number] = &hit_emoji[0];
    } else {
        shot_status[atomic_number] = &miss_emoji[0];
    }
    print_periodic_tables(saved_game_text);
}

void display_driver::enemy_shot(int atomic_number, bool hit){
    if (hit){
        ship_status[atomic_number] = &hit_emoji[0];
    } else {
        ship_status[atomic_number] = &miss_emoji[0];
    }
    print_periodic_tables(saved_game_text);
}

void display_driver::enemy_ship_sunk(const string& electron_config){
    int atomic_number = atomic_number_from_config[electron_config];

    for (int i = 0; i != player2_pointer->ships.size(); ++i){
        if (player2_pointer->ships[i].find(electron_config) != player2_pointer->ships[i].end()){
            // correct map found, flip it to sunk emoji
            for (auto j = player2_pointer->ships[i].begin(); j != player2_pointer->ships[i].end(); ++j){
                string ship_configs = j->first;
                int ship_atomic_nums = atomic_number_from_config[ship_configs];
                shot_status[ship_atomic_nums] = &sunk_emoji[0];
            }
        }
    }
    print_periodic_tables(saved_game_text);
}

void display_driver::player_ship_sunk(const string& electron_config){
    int atomic_number = atomic_number_from_config[electron_config];

    for (int i = 0; i != player1_pointer->ships.size(); ++i){
        if (player1_pointer->ships[i].find(electron_config) != player1_pointer->ships[i].end()){
            // correct map found, flip it to sunk emoji
            for (auto j = player1_pointer->ships[i].begin(); j != player1_pointer->ships[i].end(); ++j){
                string ship_configs = j->first;
                int ship_atomic_nums = atomic_number_from_config[ship_configs];
                ship_status[ship_atomic_nums] = &sunk_emoji[0];
            }
        }
    }
    print_periodic_tables(saved_game_text);
}

void display_driver::welcome_and_place_ships(string& game_text, const string& size){
    game_text.clear();    
    game_text.append("Welcome, ").append(player1_pointer->get_name())
             .append(", to the Periodic Table Battleship.")
             .append("\n\n")
             .append("PLACING ")
             .append(size).append(" BLOCK SHIPS: \n");
    print_periodic_tables(game_text);
}

void display_driver::ship_placed (string& game_text, const vector<string>& elements, int ship_number, int ship_size){
    game_text.append("Ship #").append(to_string(ship_number))
             .append(" of size ")
             .append(to_string(ship_size))
             .append(" placed at ")
             .append(elements[0]);
    for (int i = 1; i != ship_size; ++i){
        game_text.append(", ");
        if (i == ship_size - 1){
            game_text.append("and ");
        } 
        game_text.append(elements[i]);
    }
    game_text.append(". \n");
    place_ship(elements);
    print_periodic_tables(game_text);
}

void display_driver::set_possibilities_periodic_table(){
    for (int i = 1; i != 119; ++i){
        string temp = to_string(player2_pointer->AI_element_node_vector[i]->possibilities);
        if (temp.size() == 1){
            temp.push_back(' ');
        }
        possibilities_string.push_back(temp);
        possibilities_status.push_back(&possibilities_string[i][0]);
    }

}

void display_driver::update_possibilities_periodic_table(){
    for (int i = 1; i != 119; ++i){
        string temp = to_string(player2_pointer->AI_element_node_vector[i]->possibilities);
        if (temp.size() > 2){
            temp = "--";
        } else if (temp.size() == 1){
            temp.push_back(' ');
        }

        possibilities_string[i] = temp;
    }    
}

void display_driver::print_AI_possibilities(){

    printf("                   AI's THOUGHTS                         \n");
    printf(" ╔══╗                                               ╔══╗\n"); 
    printf("1║%s║                                               ║%s║\n", possibilities_status[1], possibilities_status[2]);
    printf(" ╠══╬══╗                             ╔══╦══╦══╦══╦══╬══╣\n");
    printf("2║%s║%s║                             ║%s║%s║%s║%s║%s║%s║\n", possibilities_status[3], possibilities_status[4], possibilities_status[5], possibilities_status[6], possibilities_status[7], possibilities_status[8], possibilities_status[9], possibilities_status[10]);
    printf(" ╠══╬══╣                             ╠══╬══╬══╬══╬══╬══╣\n");
    printf("3║%s║%s║                             ║%s║%s║%s║%s║%s║%s║\n", possibilities_status[11], possibilities_status[12], possibilities_status[13], possibilities_status[14], possibilities_status[15], possibilities_status[16], possibilities_status[17], possibilities_status[18]);
    printf(" ╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣\n");
    printf("4║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", possibilities_status[19], possibilities_status[20], possibilities_status[21], possibilities_status[22], possibilities_status[23], possibilities_status[24], possibilities_status[25], possibilities_status[26], possibilities_status[27], possibilities_status[28], possibilities_status[29], possibilities_status[30], possibilities_status[31], possibilities_status[32], possibilities_status[33], possibilities_status[34], possibilities_status[35], possibilities_status[36]);
    printf(" ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("5║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", possibilities_status[37], possibilities_status[38], possibilities_status[39], possibilities_status[40], possibilities_status[41], possibilities_status[42], possibilities_status[43], possibilities_status[44], possibilities_status[45], possibilities_status[46], possibilities_status[47], possibilities_status[48], possibilities_status[49], possibilities_status[50], possibilities_status[51], possibilities_status[52], possibilities_status[53], possibilities_status[54]);
    printf(" ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("6║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", possibilities_status[55], possibilities_status[56], possibilities_status[71], possibilities_status[72], possibilities_status[73], possibilities_status[74], possibilities_status[75], possibilities_status[76], possibilities_status[77], possibilities_status[78], possibilities_status[79], possibilities_status[80], possibilities_status[81], possibilities_status[82], possibilities_status[83], possibilities_status[84], possibilities_status[85], possibilities_status[86]);
    printf(" ╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("7║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", possibilities_status[87], possibilities_status[88], possibilities_status[103], possibilities_status[104], possibilities_status[105], possibilities_status[106], possibilities_status[107], possibilities_status[108], possibilities_status[109], possibilities_status[110], possibilities_status[111], possibilities_status[112], possibilities_status[113], possibilities_status[114], possibilities_status[115], possibilities_status[116], possibilities_status[117], possibilities_status[118]);
    printf(" ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝\n");
    printf("       ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗      \n");
    printf("       ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║      \n", possibilities_status[57], possibilities_status[58], possibilities_status[59], possibilities_status[60], possibilities_status[61], possibilities_status[62], possibilities_status[63], possibilities_status[64], possibilities_status[65], possibilities_status[66], possibilities_status[67], possibilities_status[68], possibilities_status[69], possibilities_status[70]);
    printf("       ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣      \n");
    printf("       ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║      \n", possibilities_status[89], possibilities_status[90], possibilities_status[91], possibilities_status[92], possibilities_status[93], possibilities_status[94], possibilities_status[95], possibilities_status[96], possibilities_status[97], possibilities_status[98], possibilities_status[99], possibilities_status[100], possibilities_status[101], possibilities_status[102]);
    printf("       ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝      \n");   
}

/**************************NONMEMBER FUNCTION***************************/

void my_wait(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms)); 
}