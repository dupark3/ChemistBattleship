#include "gameboard.h"

void Display::print_periodic_tables(){
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

}