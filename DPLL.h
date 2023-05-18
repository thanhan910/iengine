#pragma once
#include <string>
#include <unordered_set>
#include "IE.h"
#include "Clause.h"
#include "Model.h"

class DPLL : public IE
{
private:
	using Sequence = std::tuple<Clause, std::string, bool>;
	std::vector<Sequence> sequence;
	std::vector<Clause> clauses;
	std::vector<bool> clause_is_true;
	bool dpll(std::set<std::string> symbols, Model model);
public:
	DPLL(std::string& KB_, std::string& query_);
	void print_result() override;
};