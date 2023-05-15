#pragma once
#include <string>
#include <vector>
#include <set>

// Wrapper function to convert a formula in string format to a vector of clauses
std::vector<std::set<std::string>> cnf(const std::string& input);

std::vector<std::set<std::string>> convert_cnf_node_to_string_sets(Node* cnf_node);
