#pragma once
#include <string>

class IE
{
protected:
	bool kb_entails_query;
public:
	IE(std::string& KB_, std::string& query_) :
		kb_entails_query(false) { }
	virtual void print_result() = 0;
	bool get_result();
};

