#pragma once
#include <string>
#include <set>
#include <unordered_set>
#include <tuple>
#include <unordered_map>
#include "IE.h"
#include "Clause.h"


// Prove a theorem using resolution
class Resolution : public IE
{
public:
	Resolution(std::string& KB, std::string& query);
	void print_result() override;
private:
	bool check();
	std::set<Clause> clauses;
	std::set<Clause> new_clauses;
	std::set<Clause> original_clauses;

	using Resolvent = std::tuple<Clause, Clause, Clause>;
	std::vector<Resolvent> sequence;
};