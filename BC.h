#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Node.h"

class BC
{
public:

	std::vector<std::string> sequence;

	BC(std::string& kb_, std::string& query_);
	
	bool check();
private:
	Node* KB;
	std::string query;
	std::unordered_map<std::string, bool> facts;
	bool ask(const std::string& query);
};
