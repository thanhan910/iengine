#pragma once
#include "Node.h"
#include <string>
#include <vector>
#include <set>

// Define a function to convert a node to CNF form
Node* cnf(Node* node);


// Convert a formula to a vector of clauses
std::vector<std::set<std::string>> convert_cnf_node_to_string_sets(Node* cnf_node);
