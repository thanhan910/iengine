#pragma once
#include "Node.h"

// Define a function for recursively printing the node hierarchy
void print_node_tree_style(Node* node, std::string prefix = "", std::string child_prefix = "");
void print_node_parentheses_style(Node* node);
void print_node_bracket_style(Node* node, std::string prefix = "");
void print_node_infix(Node* node);