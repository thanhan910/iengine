#pragma once
#include <string>
#include "IE.h"
#include "Clause.h"
#include "Model.h"

class DPLL : public IE
{
private:
	bool dpll(std::vector<Clause> clauses, std::set<std::string> symbols, Model model);
public:
	DPLL(std::string& KB_, std::string& query_);
	void print_result() override;
};