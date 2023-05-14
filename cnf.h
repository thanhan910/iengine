#pragma once
#include <string>
#include <vector>
#include <set>

// Wrapper function to convert a formula in string format to a vector of clauses
std::vector<std::set<std::string>> cnf(const std::string& input);
