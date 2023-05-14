#pragma once
#include "Node.h"

#include <string>
#include <vector>
#include <unordered_map>

class TT
{
private:

	Node* kb;
	Node* query;

	bool check_all(std::vector<std::string> symbols, std::unordered_map<std::string, bool> model);

public:

	TT(std::string& kb_, std::string& query_);

	bool check();

	size_t model_count;


};

