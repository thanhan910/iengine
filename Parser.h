#pragma once
#include "Token.h"
#include "Node.h"
#include "HornClause.h"
#include "cnf.h"
#include <string>
#include <vector>
#include <set>


class Parser
{
private:

	std::string input;
	std::set<std::string> symbols;
	std::vector<Token> tokens;
	Node* root;

	void tokenize();
	void create_tree();
	void convert_to_cnf();

	bool tokenized, tree_created, converted_to_cnf;

public:
	
	Parser(std::string& input_);

	std::vector<Token> get_tokens();

	std::set<std::string> get_symbols();
	
	Node* get_tree();

	Node* get_cnf_tree();

	std::vector<Clause> get_cnf_clauses();
	
	std::vector<HornClause> get_horn_clauses();
};

