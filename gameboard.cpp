#include <chrono> // chrono::milliseconds(ms)
#include <thread> // this_thread::sleep_for

#include "AI.h"
#include "gameboard.h"
#include "periodic_table.h"
#include "player.h"

using namespace std;

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

void Game::set_up_player(){
    mvprintw(25, 0, "Enter your name: ");
    string player1name;
    wait();
    cin >> player1name;
    mvprintw(26, 0, "Welcome, %s, to the Periodic Table Battleship.", player1name);
    player player1(player1name);
}

void Game::set_up_ships(int, int){

}

void Game::set_up_AI(){

}

void print_periodic_tables(){
    vector<string> symbols;
    vector<char*> status;
    
    symbols.reserve(119);
    status.reserve(119);
    
    // off set index by one to match atomic number
    symbols.push_back("");
    status.push_back(&symbols[0][0]);

    for (int i = 1; i != 119; ++i){
        string temp = element_node_vector[i]->get_element_symbol();
        if (temp.size() == 1){
            temp.push_back(' ');
        }
        symbols.push_back(temp);
        status.push_back(&symbols[i][0]);
    }

    // Using printf and C style to hold the place of element symbol
    printf("                     YOUR SHIPS                                                  YOUR SHOTS/MISSES\n");
    printf(" ╔══╗                                               ╔══╗      ╔══╗                                               ╔══╗\n"); 
    printf("1║%s║                                               ║%s║     1║%s║                                               ║%s║ \n", status[1], status[2], status[1], status[2]);
    printf(" ╠══╬══╗                             ╔══╦══╦══╦══╦══╬══╣      ╠══╬══╗                             ╔══╦══╦══╦══╦══╬══╣\n");
    printf("2║%s║%s║                             ║%s║%s║%s║%s║%s║%s║     2║%s║%s║                             ║%s║%s║%s║%s║%s║%s║\n", status[3], status[4], status[5], status[6], status[7], status[8], status[9], status[10], status[3], status[4], status[5], status[6], status[7], status[8], status[9], status[10]);
    printf(" ╠══╬══╣                             ╠══╬══╬══╬══╬══╬══╣      ╠══╬══╣                             ╠══╬══╬══╬══╬══╬══╣\n");
    printf("3║%s║%s║                             ║%s║%s║%s║%s║%s║%s║     3║%s║%s║                             ║%s║%s║%s║%s║%s║%s║\n", status[11], status[12], status[13], status[14], status[15], status[16], status[17], status[18], status[11], status[12], status[13], status[14], status[15], status[16], status[17], status[18]);
    printf(" ╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣      ╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣\n");
    printf("4║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     4║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", status[19], status[20], status[21], status[22], status[23], status[24], status[5], status[6], status[27], status[8], status[29], status[30], status[31], status[32], status[33], status[34], status[35], status[36], status[19], status[20], status[21], status[22], status[23], status[24], status[25], status[26], status[27], status[28], status[29], status[30], status[31], status[32], status[33], status[34], status[35], status[36]);
    printf(" ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣      ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("5║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     5║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", status[37], status[38], status[39], status[40], status[41], status[42], status[43], status[44], status[45], status[46], status[47], status[48], status[49], status[50], status[51], status[52], status[53], status[54], status[37], status[38], status[39], status[40], status[41], status[42], status[43], status[44], status[45], status[46], status[47], status[48], status[49], status[50], status[51], status[52], status[53], status[54]);
    printf(" ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣      ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("6║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     6║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", status[55], status[56], status[71], status[72], status[73], status[74], status[75], status[76], status[77], status[78], status[79], status[80], status[81], status[82], status[83], status[84], status[85], status[86], status[55], status[56], status[71], status[72], status[73], status[74], status[75], status[76], status[77], status[78], status[79], status[80], status[81], status[82], status[83], status[84], status[85], status[86]);
    printf(" ╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣      ╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("7║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     7║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", status[87], status[88], status[103], status[104], status[105], status[106], status[107], status[108], status[109], status[110], status[111], status[112], status[113], status[114], status[115], status[116], status[117], status[118], status[87], status[88], status[103], status[104], status[105], status[106], status[107], status[108], status[109], status[110], status[111], status[112], status[113], status[114], status[115], status[116], status[117], status[118]);
    printf(" ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝      ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝\n");
    printf("       ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗                  ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗\n");
    printf("       ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║                  ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", status[57], status[58], status[59], status[60], status[61], status[62], status[63], status[64], status[65], status[66], status[67], status[68], status[69], status[70], status[57], status[58], status[59], status[60], status[61], status[62], status[63], status[64], status[65], status[66], status[67], status[68], status[69], status[70]);
    printf("       ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣                  ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("       ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║                  ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", status[89], status[90], status[91], status[92], status[93], status[94], status[95], status[96], status[97], status[98], status[99], status[100], status[101], status[102], status[89], status[90], status[91], status[92], status[93], status[94], status[95], status[96], status[97], status[98], status[99], status[100], status[101], status[102]);
    printf("       ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝                  ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝\n");
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