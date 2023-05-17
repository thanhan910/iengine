#pragma once
#include "Node.h"

#include <string>
#include <unordered_map>

class Model : public std::unordered_map<std::string, bool>
{
private:
	// The underlying unordered_map



public:
	// Static member variable to keep track of the instance count
	static size_t instanceCreated;
	static size_t instanceDeleted;

	Model()
	{
		// Increment the count when a new instance is created
		++instanceCreated;
	}

	Model(const Model& other) : std::unordered_map<std::string, bool>(other)
	{
		// Increment the count when the copy constructor is called
		++instanceCreated;
	}

	~Model()
	{
		// Decrement the count when an instance is destroyed
		++instanceDeleted;
	}
};


void print_model(std::unordered_map<std::string, bool>& model);


int pl_value(Model& model, Node* node);

