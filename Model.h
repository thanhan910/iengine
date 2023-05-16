#pragma once
#include "Node.h"

#include <string>
#include <unordered_map>

void print_model(std::unordered_map<std::string, bool>& model);


int pl_value(std::unordered_map<std::string, bool>& model, Node* node);

