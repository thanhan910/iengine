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
	std::vector<Model> models; // save the models just for printint to the console
	size_t model_count;

	bool check_all(std::vector<std::string> symbols, Model model);

public:

	TT(std::string& kb_, std::string& query_);

	void print_result() override;
};

