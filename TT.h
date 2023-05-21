#pragma once
#include "Node.h"
#include "IE.h"
#include "Model.h"
#include <string>
#include <vector>



class TT : public IE
{
private:

	Node* KB;
	Node* query;
	std::vector<Model> models;
	
	bool check_all(std::vector<std::string> symbols, Model model);

public:
	size_t model_count;

	TT(std::string& kb_, std::string& query_);

	void print_result() override;
};

