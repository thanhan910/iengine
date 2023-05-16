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


int pl_value(std::unordered_map<std::string, bool>& model, Node* node)
{
    switch (node->type)
    {
    case BOOLEAN: {
        return node->value == "1" ? 1 : 0;
    }
    case VARIABLE: {

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

        int sequence = 1;

        for (Node* child : node->children)
        {
            int child_result = pl_value(model, child);

            if (child_result == 0)
            {
                return 0;
            }

            else if (child_result == 2)
            {
                sequence = 2;
            }
        }

        return sequence;
    }
    case OR: {
        int sequence = 2;

        for (Node* child : node->children)
        {
            int child_result = pl_value(model, child);

            if (child_result == 1)
            {
                return 1;
            }

            else if (child_result == 0)
            {
                sequence = 0;
            }
        }

        return sequence;
    }

    case IMPLIES: {
        int ant = pl_value(model, node->children[0]);
        int con = pl_value(model, node->children[1]);

        if (ant == 0 || con == 1) return 1;
        if (ant == 0 && con == 1) return 0;
        return 2;

    }

    case BICONDITIONAL: {
        int ant = pl_value(model, node->children[0]);
        int con = pl_value(model, node->children[1]);

        if (ant == 2 || con == 2) return 2;
        if (ant == con) return 1;
        if (ant != con) return 0;
    }

    default: {
        return 2;
    }
    }
}