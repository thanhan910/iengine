#pragma once
#include <string>
#include <vector>
#include "Node.h"

class FC
{
public:

	FC(std::string& kb_, std::string& query_);
	std::vector<std::string> sequence;
	bool check();
private:
	Node* kb;
	std::string query;
};



