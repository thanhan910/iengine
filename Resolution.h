#pragma once
#include <string>
#include "IE.h"

// Prove a theorem using resolution
class Resolution : public IE
{
public:
	Resolution(std::string& KB, std::string& query);
	void print_result() override;
};