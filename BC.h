#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Node.h"
#include "IE.h"

class BC : public IE
{
public:

	std::vector<std::string> sequence;

	BC(std::string& kb_, std::string& query_);
	
private:
	Node* KB;
	std::unordered_map<std::string, bool> facts;
	bool ask(const std::string& query);
};
