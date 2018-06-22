#include <fstream> // ifstream
#include <iostream> // cerr

#include "game.h"

using namespace std;

Game::Game() : player1(), player2(), player1name(""), player2name(""), display(), game_text(""){
    cout << "CHECK" << endl;
    // seed rand() with time
    srand(time(0));
    
    // load periodictable.txt into answer key data structures
    load_periodic_table(element_node_vector);
    cout << "display setting players" << endl;
    display.set_players(player1, player2);
}

void Game::setup(){
    /* Uncomment if you want to see AI's possibilities shown on console
    Also, uncomment two lines in print_periodic_table() in gameboard.cpp
    display.set_possibilities_periodic_table();
    */

    // SET UP PLAYER 1 (player class)
    game_text.append("Enter your name: ");
    display.print_periodic_tables(game_text);
    cin >> player1name;
    game_text.append(player1name);
    player1.set_name(player1name);

    // SET UP PLAYER 2 (AI derived class from player)
    player2name = "AI";
    player2.set_name(player2name);
}

void Game::run(){
    display.welcome_and_place_ships(game_text, "THREE");

    // Ask player 1 to place four 3-block ship until successful
    for (int i = 0; i != 1; ++i){    
        cout << "\nPlace a 3-block ship #" << i + 1 
             << " by writing the element's symbols, separated by spaces: ";
        string element1, element2, element3;
        cin >> element1 >> element2 >> element3;
        vector<string> elements = {element1, element2, element3};
        if (player1.place_ship(elements)){
            display.ship_placed(game_text, elements, i + 1, 3);
        } else {
            display.print_periodic_tables(game_text);
            cout << "IMPOSSIBLE! Try again and ensure that your elements are horizontal or vertical." << endl;
            --i;
        }
        cin.clear();
    }

    my_wait(1000);
    display.welcome_and_place_ships(game_text, "FOUR");

    // Ask player 1 to place three 4-block ship until successful
    for (int i = 0; i != 0; ++i){
        cout << "\nPlace a 4-block ship #" << i + 1 
             << " by writing the element's symbols, separated by spaces: ";
        string element1, element2, element3, element4;
        cin >> element1 >> element2 >> element3 >> element4;
        vector<string> elements = {element1, element2, element3, element4};
        if (player1.place_ship(elements)){
            display.ship_placed(game_text, elements, i + 1, 4);
        } else {
            display.print_periodic_tables(game_text);
            cout << "IMPOSSIBLE! Try again and ensure that your elements are horizontal or vertical." << endl;
            --i;
        }
        cin.clear();
    }

    my_wait(1000);
    display.welcome_and_place_ships(game_text, "FIVE");

    // Ask player 1 to place two 5-block ship until successful
    for (int i = 0; i != 0; ++i){
        cout << "\nPlace a 5-block ship #" << i + 1 
             << " by writing the element's symbols, separated by spaces: ";
        string element1, element2, element3, element4, element5;
        cin >> element1 >> element2 >> element3 >> element4 >> element5;
        vector<string> elements = {element1, element2, element3, element4, element5};
        if (player1.place_ship(elements)){
            display.ship_placed(game_text, elements, i + 1, 5);
        } else {
            display.print_periodic_tables(game_text);
            cout << "IMPOSSIBLE! Try again and ensure that your elements are horizontal or vertical." << endl;
            --i;
        }
        cin.clear();
    }

    my_wait(1000);
    game_text.clear();
    game_text.append(player2name).append(" is placing his ships...\n");
    display.print_periodic_tables(game_text);

    // Set up AI's ships in reverse order to put the 5-block ship anywhere
    for(int i = 0; i != 2; ++i){
        player2.place_ship_randomly(5);
        my_wait(150);
    }
    for(int i = 0; i != 3; ++i){
        player2.place_ship_randomly(4);
        my_wait(150);
    }
    for(int i = 0; i != 4; ++i){
        player2.place_ship_randomly(3);
        my_wait(150);
    }

    my_wait(300);

    /**********************************game START*********************************************/
    int round = 1;

    // game loop, break points within when all ships of a player has been sunk
    while (true){
        game_text.clear();
        game_text.append("ROUND ").append(to_string(round++)).append("\n\n");

        
        // PLAYER 1's TURN
        game_text.append(player1name).append("\'s turn take a shot with an electron configuration: ");
        display.print_periodic_tables(game_text);
        string electron_config;
        cin >> electron_config;
        game_text.append(electron_config).append("\n");
        
        // check the use of X-bomb. Check only the four corners of the X. 
        // Leave center element for check_shot() in the following if statement
        if (electron_config == "X" && player1.get_X_bombs() > 0){
            player1.lose_X_bomb();
            game_text.append("X-Bomb Activated! Enter the electron configuration of the center of your X-Bomb: ");
            display.print_periodic_tables(game_text);
            cin >> electron_config;
            game_text.append(electron_config).append("\n");

            // pass config through conversion. will not change it if it was long form already.
            if (player1.short_form_allowed()){
                electron_config = convert_to_long_form(electron_config);
            }

            vector< pair<string, bool> > X_bomb_result = player2.check_X_bomb(electron_config);

            for (int i = 0; i != X_bomb_result.size(); ++i){
                int atomic_number = atomic_number_from_config[X_bomb_result[i].first];
                string element_symbol = element_node_vector[atomic_number]->get_element_symbol();
                string corner_electron_config = X_bomb_result[i].first;
                bool hit = X_bomb_result[i].second;
                
                if (hit){
                    player1.hit();
                    game_text.append(player1name).append(" HIT! Element ")
                             .append(element_symbol).append(" has been shot down.\n");
                    display.store_game_text(game_text);
                    display.player_shot(atomic_number, true);
                    if (player2.ship_sunk(corner_electron_config)){                    
                        game_text.append("SHIP SUNK at ").append(element_symbol)
                                 .append("!\n");
                        display.store_game_text(game_text);
                        display.enemy_ship_sunk(corner_electron_config);
                    }
                    if (player2.check_game_over()){
                        my_wait(300);
                        cout << "******************** GAME OVER, " << player1name << " IS VICTORIOUS ********************" << endl;
                        system("exit");
                    } 
                } else {
                    player1.missed();
                    game_text.append(player1name).append(" MISSED! Element " )
                             .append(element_symbol).append(" is open waters.\n");
                    display.store_game_text(game_text);
                    display.player_shot(atomic_number, false);
                }
            }
        }
        
        // if no X-bomb was used, we must check for short form
        if (player1.short_form_allowed()){
            electron_config = convert_to_long_form(electron_config);
        }

        int atomic_number = atomic_number_from_config[electron_config];
        string element_symbol;

        // check_shot is called on the opponent's player object to see if it's a hit
        if(player2.check_shot(electron_config)){
            player1.hit(); // for calculating accuracy. increments number of hits
            element_symbol = element_node_vector[atomic_number]->get_element_symbol();
            game_text.append(player1name).append(" HIT! Element " )
                     .append(element_symbol).append(" has been shot down.\n");
            display.store_game_text(game_text);
            display.player_shot(atomic_number, true);
            if (player2.ship_sunk(electron_config)){
                game_text.append("SHIP SUNK!\n");
                display.store_game_text(game_text);
                display.enemy_ship_sunk(electron_config);
            }
            if (player2.check_game_over()){
                my_wait(300);
                cout << "******************** GAME OVER, " << player1name << " IS VICTORIOUS ********************" << endl;
                system("exit");
            } 
        } else if (atomic_number == 0) {
            player1.misfire();
            game_text.append(player1name).append(" MISFIRED! Electron configuration ")
                     .append(electron_config).append(" is incorrect.\n");
            display.print_periodic_tables(game_text);
        } else {
            player1.missed();
            element_symbol = element_node_vector[atomic_number]->get_element_symbol();
            game_text.append(player1name).append(" MISSED! Element ")
                     .append(element_symbol).append(" is open waters.\n");
            display.store_game_text(game_text);
            display.player_shot(atomic_number, false);
        }

        my_wait(300);

        // player2's turn
        game_text.append("\n").append(player2name)
                 .append("\'s turn to take a shot with an electron configuration: ");        
        my_wait(200);

        // take an educated shot
        electron_config = player2.take_educated_shot();
        atomic_number = atomic_number_from_config[electron_config];
        element_symbol = element_node_vector[atomic_number]->get_element_symbol();
        game_text.append(electron_config).append("\n");
        display.print_periodic_tables(game_text);
        my_wait(300);

        // ask user to identify this electron config
        game_text.append("\nIdentify the element: ");
        display.print_periodic_tables(game_text);
        string element_symbol_guess;
        cin >> element_symbol_guess;
        game_text.append(element_symbol_guess).append("\n");

        if (element_symbol == element_symbol_guess){
            player1.correct_guess();
            game_text.append("Correct! You have identified ")
                     .append(to_string(player1.get_correct_guesses()))
                     .append(" in a row. \n");
            
            if (player1.get_correct_guesses() != 0 && player1.get_correct_guesses() % 5 == 0){
                player1.earn_X_bomb();
                game_text.append("FIVE CORRECT IDENTIFICATIONS IN A ROW! You have earned an X-bomb. Write X to use.\n");
            }
        } else {
            player1.reset_guesses();
            game_text.append("Incorrect. Number of correct guesses have been reset to zero.\n");
        }

        display.print_periodic_tables(game_text);
        my_wait(300);

        if (player1.check_shot(electron_config)){
            game_text.append("\n").append(player2name).append(" HIT! element ")
                     .append(element_symbol)
                     .append(" has been shot down.\n");
            player2.hit(player1, atomic_number);
            display.store_game_text(game_text);
            display.enemy_shot(atomic_number, true);
            if (player1.ship_sunk(electron_config)){
                game_text.append("SHIP SUNK!\n");
                display.store_game_text(game_text);
                display.player_ship_sunk(electron_config);
            }
            if (player1.check_game_over()){
                my_wait(300);
                cout << "******************** GAME OVER, " << player2name << " IS VICTORIOUS ********************" << endl;
                break;
            }
        } else {
            player2.missed(player1, atomic_number);
            game_text.append("\n").append(player2name).append(" MISSED! Element ")
                     .append(element_symbol)
                     .append(" is open waters.\n");
            display.store_game_text(game_text);
            display.enemy_shot(atomic_number, false);
        }
    cout << "\nPress enter to continue.";
    cin.get();
    cin.get();

    }
}

 
int next_rows_atomic_number(int atomic_number){
    if (atomic_number == 1){
        return atomic_number + 2;
    } else if (atomic_number >= 2 && atomic_number <= 12){
        return atomic_number + 8;
    } else if (atomic_number >= 13 && atomic_number <= 38){
        return atomic_number + 18;
    } else if (atomic_number >= 39 && atomic_number <= 86){
        return atomic_number + 32;
    } else {
        return 0;
    }
}

void load_periodic_table(std::vector<element_node*>& node_vector){
    std::ifstream PeriodicTableFileStream;
    PeriodicTableFileStream.open("periodictable.txt");

    if (!PeriodicTableFileStream){
        std::cerr << "Unable to open periodic table file";
        std::exit(1); // throw exception here instead?
    }

    // insert empty node into index 0 since there is no element at atomic number 0
    element_node* empty_element_node = new element_node;
    node_vector.push_back(empty_element_node);

    // read and load info
    int atomic_number;

    while(PeriodicTableFileStream >> atomic_number){
        // allocate memory for an element_node. 
        element_node* new_element_node = new element_node;
        node_vector.push_back(new_element_node);
        node_vector[atomic_number]->atomic_number = atomic_number;

        // read symbol and store into element_node and atomic_numbers_from_symbol hashmap
        std::string element_symbol;
        PeriodicTableFileStream >> element_symbol;
        node_vector[atomic_number]->element_symbol = element_symbol;
        atomic_number_from_symbol[element_symbol] = atomic_number;

        // read name and store into element_node 
        std::string element_name;
        PeriodicTableFileStream >> element_name;
        node_vector[atomic_number]->element_name = element_name;

        // read config and store into element_node and atomic_numbers_from_config hashmap
        std::string electron_config;
        PeriodicTableFileStream >> electron_config;
        node_vector[atomic_number]->electron_config = electron_config;
        atomic_number_from_config[electron_config] = atomic_number;
    }

    // set correct pointers to adjacent nodes to the right, left, below, above
    for(int i = 1; i != MAX_ELEMENT + 1; ++i){
        
        // four types resulting from the possibility of a valid/invalid right/down neighbors
        // hard coding necessary here to represent the unique shape of the periodic table
        std::map<int, bool> both_valid  = { {3, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1},
        {9, 1}, {11, 1}, {13, 1}, {14, 1}, {15, 1}, {16, 1}, {17, 1}, {19, 1}, 
        {20,1}, {21, 1}, {22, 1}, {23, 1}, {24, 1}, {25, 1}, {26, 1}, {27, 1}, 
        {28, 1},{29, 1}, {30, 1}, {31, 1}, {32, 1}, {33, 1}, {34, 1}, {35, 1}, 
        {37, 1}, {38,1}, {39, 1}, {40, 1}, {41, 1}, {42, 1}, {43, 1}, {44, 1}, 
        {45, 1}, {46, 1},{47, 1}, {48, 1}, {49, 1}, {50, 1}, {51, 1}, {52, 1}, 
        {53, 1}, {55, 1}, {56,1}, {71, 1}, {72, 1}, {73, 1}, {74, 1}, {75, 1}, 
        {76, 1}, {77, 1}, {78, 1},{79, 1}, {80, 1}, {81, 1}, {82, 1}, {83, 1}, 
        {84, 1}, {85, 1}, {57, 1}, {58, 1}, {59,1}, {60, 1}, {61, 1}, {62, 1}, 
        {63, 1}, {64, 1}, {65, 1}, {66, 1}, {67, 1},{68, 1}, {69, 1} };

        std::map<int, bool> right_valid = { {87, 1}, {88, 1}, {103, 1}, {104, 1 },
        {105, 1}, {106, 1}, {107, 1}, {108, 1}, {109, 1}, {110, 1}, {111, 1}, 
        {112, 1}, {113, 1}, {114, 1}, {115, 1}, {116, 1}, {117, 1}, {89, 1 }, 
        {90, 1}, {91,1}, {92, 1}, {93, 1}, {94, 1}, {95, 1}, {96, 1}, {97, 1}, 
        {98, 1}, {99, 1},{100, 1}, {101, 1} };

        std::map<int, bool> down_valid  = { {1, 1}, {2, 1}, {4, 1}, {10, 1}, {12,1},
        {18, 1}, {36, 1}, {54, 1}, {86, 1}, {70, 1} } ;

        std::map<int, bool> no_valid    = { {118, 1}, {102, 1} };
        
        int next_row = next_rows_atomic_number(i);

        if (both_valid[i]) {
            node_vector[i]->right_ship = node_vector[i + 1];
            node_vector[i + 1]->left_ship = node_vector[i];
            node_vector[i]->below_ship = node_vector[next_row];
            node_vector[next_row]->above_ship = node_vector[i];
        } else if (right_valid[i]) {
            node_vector[i]->right_ship = node_vector[i + 1];
            node_vector[i + 1]->left_ship = node_vector[i];
            node_vector[i]->below_ship = 0;
        } else if (down_valid[i]) {
            node_vector[i]->right_ship = 0;
            node_vector[i]->below_ship = node_vector[next_row];
            node_vector[next_row]->above_ship = node_vector[i];
        } else if (no_valid[i]) {
            node_vector[i]->right_ship = 0;
            node_vector[i]->below_ship = 0;
        }
    }
    
    // fix transition from 6s/7s to 5d/6d
    node_vector[56]->right_ship = node_vector[71];
    node_vector[71]->left_ship = node_vector[56];
    node_vector[88]->right_ship = node_vector[103];
    node_vector[103]->left_ship = node_vector[88];
    
}