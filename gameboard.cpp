#include <chrono> // chrono::milliseconds(ms)
#include <thread> // this_thread::sleep_for

#include "AI.h"
#include "gameboard.h"
#include "periodic_table.h"
#include "player.h"

using namespace std;
/*
void Game::print_periodic_tables(){
    attron(A_UNDERLINE);
    mvprintw(0, 40, "WELCOME TO THE PERIODIC TABLE BATTLESHIP");
    mvprintw(3, 23, "YOUR SHIPS");
    mvprintw(3, 81, "YOUR SHOTS AND MISSES");
    attroff(A_UNDERLINE);

    // spaces 0 to 56 is the first periodic table
    mvprintw(4, 1,  " +--+              __                               +--+");
    mvprintw(5, 1,  "1|H |              \\ \\___     .__                   |He|");
    mvprintw(6, 1,  " +--+--+         .--\"\"___\\..--\"/     +--+--+--+--+--+--+");
    mvprintw(7, 1,  "2|Li|Be|     .__.|-\"\"\"..... \' /      |B |C |N |O |F |Ne|");
    mvprintw(8, 1,  " +--+--+_____\\_______________/______ +--+--+--+--+--+--+");
    mvprintw(9, 1,  "3|Na|Mg|    ~       ~        ~       |Al|Si|P |S |Cl|Ar|");
    mvprintw(10, 1,  " +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(11, 1,  "4|K |Ca|Sc|Ti|V |Cr|Mn|Fe|Co|Ni|Cu|Zn|Ga|Ge|As|Se|Br|Kr|");
    mvprintw(12, 1,  " +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(13, 1,  "5|Rb|Sr|Y |Zr|Nb|Mo|Tc|Ru|Rh|Pd|Ag|Cd|In|Sn|Sb|Te|I |Xe|");
    mvprintw(14, 1, " +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(15, 1, "6|Cs|Ba+Lu|Hf|Ta|W |Re|Os|Ir|Pt|Au|Hg|Tl|Pb|Bi|Po|At|Rn|");
    mvprintw(16, 1, " +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(17, 1, "7|Fr|Ra+Lr|Rf|Db|Sg|Bh|Hs|Mt|Ds|Rg|Cn|Nh|Fl|Mc|Lv|Ts|Og|");
    mvprintw(18, 1, " +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(19, 1, "      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(20, 1, "      +La|Ce|Pr|Nd|Pm|Sm|Eu|Gd|Tb|Dy|Ho|Er|Tm|Yb|");
    mvprintw(21, 1, "      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(22, 1, "      +Ac|Th|Pa|U |Np|Pu|Am|Cm|Bk|Cf|Es|Fm|Md|No|");
    mvprintw(23, 1, "      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+");


    // spaces 63 to 119 is the second periodic table
    mvprintw(4, 63,  " +--+              __                               +--+");
    mvprintw(5, 63,  "1|H |              \\ \\___     .__                   |He|");
    mvprintw(6, 63,  " +--+--+         .--\"\"___\\..--\"/     +--+--+--+--+--+--+");
    mvprintw(7, 63,  "2|Li|Be|     .__.|-\"\"\"..... \' /      |B |C |N |O |F |Ne|");
    mvprintw(8, 63,  " +--+--+_____\\_______________/______ +--+--+--+--+--+--+");
    mvprintw(9, 63,  "3|Na|Mg|    ~       ~        ~       |Al|Si|P |S |Cl|Ar|");
    mvprintw(10, 63,  " +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(11, 63,  "4|K |Ca|Sc|Ti|V |Cr|Mn|Fe|Co|Ni|Cu|Zn|Ga|Ge|As|Se|Br|Kr|");
    mvprintw(12, 63,  " +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(13, 63,  "5|Rb|Sr|Y |Zr|Nb|Mo|Tc|Ru|Rh|Pd|Ag|Cd|In|Sn|Sb|Te|I |Xe|");
    mvprintw(14, 63, " +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(15, 63, "6|Cs|Ba+Lu|Hf|Ta|W |Re|Os|Ir|Pt|Au|Hg|Tl|Pb|Bi|Po|At|Rn|");
    mvprintw(16, 63, " +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(17, 63, "7|Fr|Ra+Lr|Rf|Db|Sg|Bh|Hs|Mt|Ds|Rg|Cn|Nh|Fl|Mc|Lv|Ts|Og|");
    mvprintw(18, 63, " +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(19, 63, "      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(20, 63, "      +La|Ce|Pr|Nd|Pm|Sm|Eu|Gd|Tb|Dy|Ho|Er|Tm|Yb|");
    mvprintw(21, 63, "      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    mvprintw(22, 63, "      +Ac|Th|Pa|U |Np|Pu|Am|Cm|Bk|Cf|Es|Fm|Md|No|");
    mvprintw(23, 63, "      +--+--+--+--+--+--+--+--+--+--+--+--+--+--+");
    move(25,0);
}
*/

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
}

void display_driver::set_players(const player& player1, const player& player2){
    player1_pointer = &player1;
    player2_pointer = &player2;
}

void display_driver::print_periodic_tables(){
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

    if (!player1_pointer->get_name().empty()){
        cout << "                     X-BOMBS: " << player1_pointer->get_X_bombs() << endl
             << "CORRECT CONFIGURATION STREAK: " 
             << player1_pointer->get_consecutive_correct_configs() << endl
             << "            SHORT-FORM BONUS: ";
        if (player1_pointer->get_consecutive_correct_configs() >= 3){
            cout << "on" << endl;
        } else {
            cout << "off" << endl;
        }
    
        cout << endl 
             << player1_pointer->get_name() << "\'s ACCURACY: "
             << player1_pointer->get_accuracy()
             << "%     " 
             << player2_pointer->get_name() << "\'s ACCURACY: "
             << player2_pointer->get_accuracy() << "%" << endl;    
    }
    
    cout << "******************************************************************************************************************" << endl;
}


void display_driver::place_ship(const std::vector<std::string>& ship_symbols){
    // convert symbols to ship emoji 
    for (int i = 0; i != ship_symbols.size(); ++i){
        int atomic_number = atomic_number_from_symbol[ship_symbols[i]];
        
        ship_status[atomic_number] = &ship_emoji[0];
    }
    print_periodic_tables();
}

void display_driver::player_shot(int atomic_number, bool hit){
    if (hit){
        shot_status[atomic_number] = &hit_emoji[0];
    } else {
        shot_status[atomic_number] = &miss_emoji[0];
    }
    print_periodic_tables();
}

void display_driver::enemy_shot(int atomic_number, bool hit){
    if (hit){
        ship_status[atomic_number] = &hit_emoji[0];
    } else {
        ship_status[atomic_number] = &miss_emoji[0];
    }
    print_periodic_tables();
}



/*
    cout << 
    printf("                     YOUR SHIPS                           printf("
    printf(" ╔══╗              __                               ╔══╗\n", ); 
    printf("1║H ║              \\ \\___     .__                   ║He║\n", );
    printf(" ╠══╬══╗         .--\"\"___\\..--\"/     ╔══╦══╦══╦══╦══╬══╣\n");
    printf("2║Li║Be║     .__.|-\"\"\"..... \' /      ║B ║C ║N ║O ║F ║Ne║\n", );
    printf(" ╠══╬══╣_____\\_______________/______ ╠══╬══╬══╬══╬══╬══╣\n");
    printf("3║Na║Mg║    ~       ~        ~       ║Al║Si║P ║S ║Cl║Ar║\n", );
    printf(" ╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣\n");
    printf("4║K ║Ca║Sc║Ti║V ║Cr║Mn║Fe║Co║Ni║Cu║Zn║Ga║Ge║As║Se║Br║Kr║\n", );
    printf(" ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("5║Rb║Sr║Y ║Zr║Nb║Mo║Tc║Ru║Rh║Pd║Ag║Cd║In║Sn║Sb║Te║I ║Xe║\n", );
    printf(" ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("6║Cs║Ba░Lu║Hf║Ta║W ║Re║Os║Ir║Pt║Au║Hg║Tl║Pb║Bi║Po║At║Rn║\n", );
    printf(" ╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("7║Fr║Ra░Lr║Rf║Db║Sg║Bh║Hs║Mt║Ds║Rg║Cn║Nh║Fl║Mc║Lv║Ts║Og║\n", );
    printf(" ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝\n", );
    printf("      ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗\n", );
    printf("      ░La║Ce║Pr║Nd║Pm║Sm║Eu║Gd║Tb║Dy║Ho║Er║Tm║Yb║\n", );
    printf("      ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("      ░Ac║Th║Pa║U ║Np║Pu║Am║Cm║Bk║Cf║Es║Fm║Md║No║\n", );
    printf("      ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝" << endl;*/