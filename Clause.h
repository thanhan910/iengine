#pragma once
#include "Node.h"
#include <vector>
#include <set>

typedef std::set<std::string> Clause;

// Convert a tree in CNF form to a vector of clauses
std::vector<Clause> convert_root_node_to_clauses(Node* cnf_node);

