#pragma once
#include <string>
#include <set>
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
};