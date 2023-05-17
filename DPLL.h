#pragma once
#include <string>
#include <set>

typedef std::set<std::string> Clause;

// Wrapper function to call the DPLL algorithm
bool dpll_satisfiable(std::string& sentence);

// Wrapper function to check if KB entails query using DPLL
bool dpll_prove(std::string& KB, std::string& query);



