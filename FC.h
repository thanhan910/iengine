#pragma once
#include "IE.h"
#include <vector>

class FC : public IE
{
private:
	std::vector<std::string> sequence;
	bool check(std::string& kb, std::string& query);
public:
	FC(std::string& kb_, std::string& query_);
	void print_result() override;
};



