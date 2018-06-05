#include "periodic_table.h"

using namespace std;

// global map objects defined here and externally linked
map<string, int> atomic_number_from_symbol;
map<string, int> atomic_number_from_config;
vector<element_node*> element_node_vector;

// load_periodic_table() defined in header file to avoid linker error

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


    /*mvprintw(1, 1,  " ╔══╗              __                               ╔══╗");
    mvprintw(1, 1,  "1║H ║              \\ \\___     .__                   ║He║");
    mvprintw(2, 1,  " ╠══╬══╗         .--\"\"___\\..--\"/     ╔══╦══╦══╦══╦══╬══╣");
    mvprintw(3, 1,  "2║Li║Be║     .__.|-\"\"\"..... \' /      ║B ║C ║N ║O ║F ║Ne║");
    mvprintw(4, 1,  " ╠══╬══╣_____\\_______________/______ ╠══╬══╬══╬══╬══╬══╣");
    mvprintw(5, 1,  "3║Na║Mg║    ~       ~        ~       ║Al║Si║P ║S ║Cl║Ar║");
    mvprintw(6, 1,  " ╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣");
    mvprintw(7, 1,  "4║K ║Ca║Sc║Ti║V ║Cr║Mn║Fe║Co║Ni║Cu║Zn║Ga║Ge║As║Se║Br║Kr║");
    mvprintw(8, 1,  " ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣");
    mvprintw(9, 1,  "5║Rb║Sr║Y ║Zr║Nb║Mo║Tc║Ru║Rh║Pd║Ag║Cd║In║Sn║Sb║Te║I ║Xe║");
    mvprintw(10, 1, " ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣");
    mvprintw(11, 1, "6║Cs║Ba░Lu║Hf║Ta║W ║Re║Os║Ir║Pt║Au║Hg║Tl║Pb║Bi║Po║At║Rn║");
    mvprintw(12, 1, " ╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣");
    mvprintw(13, 1, "7║Fr║Ra░Lr║Rf║Db║Sg║Bh║Hs║Mt║Ds║Rg║Cn║Nh║Fl║Mc║Lv║Ts║Og║");
    mvprintw(14, 1, " ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝");
    mvprintw(15, 1, "      ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗");
    mvprintw(16, 1, "      ░La║Ce║Pr║Nd║Pm║Sm║Eu║Gd║Tb║Dy║Ho║Er║Tm║Yb║");
    mvprintw(17, 1, "      ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣");
    mvprintw(18, 1, "      ░Ac║Th║Pa║U ║Np║Pu║Am║Cm║Bk║Cf║Es║Fm║Md║No║");
    mvprintw(19, 1, "      ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝");*/