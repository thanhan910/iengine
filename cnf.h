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

	// Before converting to CNF form, convert node to C-D NF (and, or, and, or,...)
	Node* cdnf(Node* node);

	Node* cnf_implication(Node* node);
	
	Node* cnf_biconditional(Node* node);
	
	Node* cnf_conjunction(Node* node);

	Node* cnf_negation(Node* node);

	Node* cnf_disjunction(Node* node);
	
	Node* dnf_disjunction(Node* node);
};