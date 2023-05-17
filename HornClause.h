#pragma once

#include <utility>
#include <string>
#include <set>
#include "Node.h"

typedef std::pair<std::set<std::string>, std::string> HornClause;

std::vector<HornClause> convert_root_node_to_horn_clauses(Node* root);


