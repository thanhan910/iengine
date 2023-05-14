#pragma once
#include "Node.h"

// Define a function for recursively printing the node hierarchy
void print_node(Node* node, std::string prefix = "", std::string child_prefix = "");
