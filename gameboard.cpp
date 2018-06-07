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
display_driver::display_driver() {
    // reserve enough space to prevent reallocation
    symbols.reserve(119);
    boat_status.reserve(119);
    shot_status.reserve(119);

    // off set index by one to match atomic number
    symbols.push_back("");
    boat_status.push_back(&symbols[0][0]);
    shot_status.push_back(&symbols[0][0]);

    // store element symbols in the vectors
    for (int i = 1; i != 119; ++i){
        string temp = element_node_vector[i]->get_element_symbol();
        if (temp.size() == 1){
            temp.push_back(' ');
        }
        symbols.push_back(temp);
        boat_status.push_back(&symbols[i][0]);
        shot_status.push_back(&symbols[i][0]);
    }
}

void display_driver::print_periodic_tables(){
    
    // Using printf and C style to hold the place of element symbol
    printf("\n");
    printf("                     YOUR SHIPS                                                  YOUR SHOTS/MISSES\n");
    printf(" ╔══╗                                               ╔══╗      ╔══╗                                               ╔══╗\n"); 
    printf("1║%s║                                               ║%s║     1║%s║                                               ║%s║ \n", boat_status[1], boat_status[2], shot_status[1], shot_status[2]);
    printf(" ╠══╬══╗                             ╔══╦══╦══╦══╦══╬══╣      ╠══╬══╗                             ╔══╦══╦══╦══╦══╬══╣\n");
    printf("2║%s║%s║                             ║%s║%s║%s║%s║%s║%s║     2║%s║%s║                             ║%s║%s║%s║%s║%s║%s║\n", boat_status[3], boat_status[4], boat_status[5], boat_status[6], boat_status[7], boat_status[8], boat_status[9], boat_status[10], shot_status[3], shot_status[4], shot_status[5], shot_status[6], shot_status[7], shot_status[8], shot_status[9], shot_status[10]);
    printf(" ╠══╬══╣                             ╠══╬══╬══╬══╬══╬══╣      ╠══╬══╣                             ╠══╬══╬══╬══╬══╬══╣\n");
    printf("3║%s║%s║                             ║%s║%s║%s║%s║%s║%s║     3║%s║%s║                             ║%s║%s║%s║%s║%s║%s║\n", boat_status[11], boat_status[12], boat_status[13], boat_status[14], boat_status[15], boat_status[16], boat_status[17], boat_status[18], shot_status[11], shot_status[12], shot_status[13], shot_status[14], shot_status[15], shot_status[16], shot_status[17], shot_status[18]);
    printf(" ╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣      ╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣\n");
    printf("4║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     4║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", boat_status[19], boat_status[20], boat_status[21], boat_status[22], boat_status[23], boat_status[24], boat_status[25], boat_status[26], boat_status[27], boat_status[8], boat_status[29], boat_status[30], boat_status[31], boat_status[32], boat_status[33], boat_status[34], boat_status[35], boat_status[36], shot_status[19], shot_status[20], shot_status[21], shot_status[22], shot_status[23], shot_status[24], shot_status[25], shot_status[26], shot_status[27], shot_status[28], shot_status[29], shot_status[30], shot_status[31], shot_status[32], shot_status[33], shot_status[34], shot_status[35], shot_status[36]);
    printf(" ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣      ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("5║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     5║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", boat_status[37], boat_status[38], boat_status[39], boat_status[40], boat_status[41], boat_status[42], boat_status[43], boat_status[44], boat_status[45], boat_status[46], boat_status[47], boat_status[48], boat_status[49], boat_status[50], boat_status[51], boat_status[52], boat_status[53], boat_status[54], shot_status[37], shot_status[38], shot_status[39], shot_status[40], shot_status[41], shot_status[42], shot_status[43], shot_status[44], shot_status[45], shot_status[46], shot_status[47], shot_status[48], shot_status[49], shot_status[50], shot_status[51], shot_status[52], shot_status[53], shot_status[54]);
    printf(" ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣      ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("6║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     6║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", boat_status[55], boat_status[56], boat_status[71], boat_status[72], boat_status[73], boat_status[74], boat_status[75], boat_status[76], boat_status[77], boat_status[78], boat_status[79], boat_status[80], boat_status[81], boat_status[82], boat_status[83], boat_status[84], boat_status[85], boat_status[86], shot_status[55], shot_status[56], shot_status[71], shot_status[72], shot_status[73], shot_status[74], shot_status[75], shot_status[76], shot_status[77], shot_status[78], shot_status[79], shot_status[80], shot_status[81], shot_status[82], shot_status[83], shot_status[84], shot_status[85], shot_status[86]);
    printf(" ╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣      ╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("7║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║     7║%s║%s░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", boat_status[87], boat_status[88], boat_status[103], boat_status[104], boat_status[105], boat_status[106], boat_status[107], boat_status[108], boat_status[109], boat_status[110], boat_status[111], boat_status[112], boat_status[113], boat_status[114], boat_status[115], boat_status[116], boat_status[117], boat_status[118], shot_status[87], shot_status[88], shot_status[103], shot_status[104], shot_status[105], shot_status[106], shot_status[107], shot_status[108], shot_status[109], shot_status[110], shot_status[111], shot_status[112], shot_status[113], shot_status[114], shot_status[115], shot_status[116], shot_status[117], shot_status[118]);
    printf(" ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝      ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝\n");
    printf("       ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗                  ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗\n");
    printf("       ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║                  ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", boat_status[57], boat_status[58], boat_status[59], boat_status[60], boat_status[61], boat_status[62], boat_status[63], boat_status[64], boat_status[65], boat_status[66], boat_status[67], boat_status[68], boat_status[69], boat_status[70], shot_status[57], shot_status[58], shot_status[59], shot_status[60], shot_status[61], shot_status[62], shot_status[63], shot_status[64], shot_status[65], shot_status[66], shot_status[67], shot_status[68], shot_status[69], shot_status[70]);
    printf("       ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣                  ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣\n");
    printf("       ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║                  ░%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║%s║\n", boat_status[89], boat_status[90], boat_status[91], boat_status[92], boat_status[93], boat_status[94], boat_status[95], boat_status[96], boat_status[97], boat_status[98], boat_status[99], boat_status[100], boat_status[101], boat_status[102], shot_status[89], shot_status[90], shot_status[91], shot_status[92], shot_status[93], shot_status[94], shot_status[95], shot_status[96], shot_status[97], shot_status[98], shot_status[99], shot_status[100], shot_status[101], shot_status[102]);
    printf("       ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝                  ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝\n");
}

void display_driver::place_boat(int atomic_number){

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