#pragma once
#include <string>
#include "IE.h"
#include "Clause.h"
#include "Model.h"

class DPLL : public IE
{
private:
	using Sequence = std::tuple<Clause, std::string, bool>;
	std::vector<Sequence> sequence;
	std::vector<Clause> clauses;
	bool dpll(std::set<std::string> symbols, Model model);
public:
	DPLL(std::string& KB_, std::string& query_);
	void print_result() override;
};