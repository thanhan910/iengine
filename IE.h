#pragma once
#include <string>

class IE
{
protected:
	bool KB_entails_query;
public:
	IE(std::string& KB_, std::string& query_) :
		KB_entails_query(false) { }
	virtual void print_result() = 0;
};

