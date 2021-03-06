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
    for (int i = 0; i != 4; ++i){    
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
    for (int i = 0; i != 3; ++i){
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
    for (int i = 0; i != 2; ++i){
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
