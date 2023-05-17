#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Node.h"
#include "IE.h"
#include "HornClause.h"

class BC : public IE
{
public:
	BC(std::string& kb_, std::string& query_);
	void print_result() override;

private:
	std::vector<std::string> sequence;

	std::vector<HornClause> KB;
	std::unordered_map<std::string, bool> facts;
	bool ask(const std::string& query);
};
