#pragma once
#include "Node.h"


class CNF
{
public:
	CNF(Node* node);

	Node* get_root();
private:
	
	Node* root;

	// Define a function to convert a node to CNF form
	Node* cnf(Node* node);
	
	Node* cnf_implication(Node* node);
	Node* cnf_biconditional(Node* node);
	Node* cnf_disjunction(Node* node);
	Node* cnf_conjunction(Node* node);
	Node* cnf_negation(Node* node);
};