// Contians two maps that store the periodic table's info 
// with each element's electron configuration

#ifndef GUARD_answerkey_h
#define GUARD_answerkey_h

#include <map>
#include <string>

static std::map<std::string, int> atomic_numbers;
static std::map<int, std::string> electron_configs;

void load_periodic_table();

#endif