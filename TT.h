#pragma once
#include "Node.h"

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

#include <iostream>
#include <unordered_map>
#include "Model.h"



class TT
{
private:

	Node* KB;
	Node* query;

	std::set<std::string> symbols_set;

	bool check_all(std::vector<std::string> symbols, Model model);

public:
	size_t model_count;

	TT(std::string& kb_, std::string& query_);

	bool check();
};

