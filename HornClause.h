#pragma once

#include <utility>
#include <string>
#include <set>
#include "Node.h"

using HornClause = std::pair<std::set<std::string>, std::string>;

std::vector<HornClause> convert_root_node_to_horn_clauses(Node* root);


