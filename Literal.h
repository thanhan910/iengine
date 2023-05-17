#pragma once
#include "Node.h"
#include <string>


// Function to check if literal is a negation of a symbol or not
bool is_negation(const std::string& literal);

// Function to get the reverse of literal
std::string reverse(const std::string& literal);

// Function to get symbol from literal
std::string get_symbol(const std::string& literal);

// Convert literal-type node to string
std::string convert_literal_node_to_string(Node* literal_node);

