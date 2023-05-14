#pragma once
#include "Node.h"
#include <set>
#include <string>
#include <unordered_map>

void print_model(std::unordered_map<std::string, bool>& model);

std::set<std::string> get_symbols(Node* node);

int pl_true(std::unordered_map<std::string, bool>& model, Node* node);

