#include <map>
#include <string>
#include <vector>

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

void print_periodic_table(){
                                   
                                   
                                   


    cout << 
    " ╔══╗              __                               ╔══╗" << endl <<
    "1║H ║              \\ \\___     .__                   ║He║" << endl <<
    " ╠══╬══╗         .--\"\"___\\..--\"/     ╔══╦══╦══╦══╦══╬══╣" << endl <<
    "2║Li║Be║     .__.|-\"\"\"..... \' /      ║B ║C ║N ║O ║F ║Ne║" << endl <<
    " ╠══╬══╣_____\\_______________/______ ╠══╬══╬══╬══╬══╬══╣" << endl <<
    "3║Na║Mg║    ~       ~        ~       ║Al║Si║P ║S ║Cl║Ar║" << endl <<
    " ╠══╬══╬══╦══╦══╦══╦══╦══╦══╦══╦══╦══╬══╬══╬══╬══╬══╬══╣" << endl <<
    "4║K ║Ca║Sc║Ti║V ║Cr║Mn║Fe║Co║Ni║Cu║Zn║Ga║Ge║As║Se║Br║Kr║" << endl <<
    " ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣" << endl <<
    "5║Rb║Sr║Y ║Zr║Nb║Mo║Tc║Ru║Rh║Pd║Ag║Cd║In║Sn║Sb║Te║I ║Xe║" << endl <<
    " ╠══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣" << endl <<
    "6║Cs║Ba░Lu║Hf║Ta║W ║Re║Os║Ir║Pt║Au║Hg║Tl║Pb║Bi║Po║At║Rn║" << endl <<
    " ╠══╬══░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣" << endl <<
    "7║Fr║Ra░Lr║Rf║Db║Sg║Bh║Hs║Mt║Ds║Rg║Cn║Nh║Fl║Mc║Lv║Ts║Og║" << endl <<
    " ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝" << endl <<
    "      ╔══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╦══╗" << endl <<
    "      ░La║Ce║Pr║Nd║Pm║Sm║Eu║Gd║Tb║Dy║Ho║Er║Tm║Yb║" << endl <<
    "      ░══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╬══╣" << endl <<
    "      ░Ac║Th║Pa║U ║Np║Pu║Am║Cm║Bk║Cf║Es║Fm║Md║No║" << endl <<
    "      ╚══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╩══╝" << endl;

}