#pragma once
#include <string>


// Function to check if literal is a negation of a symbol or not
bool is_negation(const std::string& literal);

// Function to get the reverse of literal
std::string reverse(const std::string& literal);

// Function to get symbol from literal
std::string atom(const std::string& literal);

