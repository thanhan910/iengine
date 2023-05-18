#pragma once
#include "Node.h"
#include <vector>
#include <set>

typedef std::set<std::string> Clause;

// Convert a tree in CNF form to a vector of clauses
std::vector<Clause> convert_root_node_to_clauses(Node* cnf_node);

// Print Clause, a list of strings
void print_clause(Clause& clause, std::string delimiter, std::string left, std::string right);

