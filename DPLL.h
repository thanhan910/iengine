#pragma once
#include <string>
#include <set>
#include "Model.h"

typedef std::set<std::string> Clause;

class DPLL
{
	bool result;
	bool dpll(std::vector<Clause> clauses, std::set<std::string> symbols, Model model);
public:
	DPLL(std::string& KB_, std::string& query_);
	bool& get_result();
};