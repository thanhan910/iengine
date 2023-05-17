#pragma once
#include <string>
#include <set>
#include "IE.h"
#include "Model.h"

typedef std::set<std::string> Clause;

class DPLL : public IE
{
private:
	bool dpll(std::vector<Clause> clauses, std::set<std::string> symbols, Model model);
public:
	DPLL(std::string& KB_, std::string& query_);
	void print_result() override;
};