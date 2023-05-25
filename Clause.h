#pragma once
#include "Node.h"
#include <vector>
#include <set>

using Clause = std::set<std::string>;

// Check if a clause is a tautology
bool is_tautology(Clause clause);

// Convert a clause-type node to a set of strings
Clause convert_clause_node_to_set(Node* clause_node);

// Convert a tree in CNF form to a vector of clauses
std::vector<Clause> convert_root_node_to_clauses(Node* cnf_node);

// Print Clause, a list of strings
void print_clause(Clause& clause, std::string delimiter, std::string left, std::string right);

