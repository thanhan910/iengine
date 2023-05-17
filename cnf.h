#pragma once
#include "Node.h"
#include <string>
#include <vector>
#include <set>

typedef std::set<std::string> Clause;

// Define a function to convert a node to CNF form
Node* cnf(Node* node);

// Convert a formula to a vector of clauses
std::vector<Clause> convert_root_node_to_clauses(Node* cnf_node);
