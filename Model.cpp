#include "Model.h"
#include <iostream>

// DEBUG: Function to print the model
void print_model(std::unordered_map<std::string, bool>& model)
{
    std::cout << "Model\n";
    for (auto& entry : model)
    {
        std::cout << entry.first << " " << entry.second << std::endl;
    }
}

size_t Model::instanceCreated = 0;
size_t Model::instanceDeleted = 0;


int pl_value(Model& model, Node* node)
{
    if (node == nullptr)
    {
        return 2;
    }

    switch (node->type)
    {
    case TRUE: {
        return true;
    }
    case FALSE: {
        return false;
    }
    case SYMBOL: {

        if (model.find(node->value) == model.end())
        {
            return 2;
        }

        return model[node->value] ? 1 : 0;
    }

    case NOT: {

        int child_result = pl_value(model, node->children[0]);

        switch (child_result)
        {
        case 0:
            return 1;
        case 1:
            return 0;
        case 2:
            return 2;
        default:
            return 2;
        }

    }

    case AND: {

        int result = 1;

        for (Node* child : node->children)
        {
            int child_result = pl_value(model, child);

            if (child_result == 0)
            {
                return 0;
            }

            else if (child_result == 2)
            {
                result = 2;
            }
        }

        return result;
    }
    case OR: {
        int result = 2;

        for (Node* child : node->children)
        {
            int child_result = pl_value(model, child);

            if (child_result == 1)
            {
                return 1;
            }

            else if (child_result == 0)
            {
                result = 0;
            }
        }
        
        return result;
    }

    case IMPLIES: {
        int left = pl_value(model, node->children[0]);
        int right = pl_value(model, node->children[1]);

        if (left == 0 || right == 1) return 1;
        if (left == 1 && right == 0) return 0;
        return 2;

    }

    case BICONDITIONAL: {
        int left = pl_value(model, node->children[0]);
        int right = pl_value(model, node->children[1]);

        if (left == 2 || right == 2) return 2;
        if (left == right) return 1;
        if (left != right) return 0;
    }

    default: {
        return 2;
    }
    }
}