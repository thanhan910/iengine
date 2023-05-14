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

std::set<std::string> get_symbols(Node* node)
{
    std::set<std::string> sequence;

    if (node->type == VARIABLE)
    {
        sequence.insert(node->value);

        return sequence;
    }

    for (Node* child : node->children)
    {
        std::set<std::string> child_symbols = get_symbols(child);

        for (const std::string symbol : child_symbols)
        {
            sequence.insert(symbol);
        }
    }

    return sequence;
}


int pl_true(std::unordered_map<std::string, bool>& model, Node* node)
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

        int child_result = pl_true(model, node->children[0]);

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
            int child_result = pl_true(model, child);

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
            int child_result = pl_true(model, child);

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
        int ant = pl_true(model, node->children[0]);
        int con = pl_true(model, node->children[1]);

        if (ant == 0 || con == 1) return 1;
        if (ant == 0 && con == 1) return 0;
        return 2;

    }

    case BICONDITIONAL: {
        int ant = pl_true(model, node->children[0]);
        int con = pl_true(model, node->children[1]);

        if (ant == 2 || con == 2) return 2;
        if (ant == con) return 1;
        if (ant != con) return 0;
    }

    default: {
        return 2;
    }
    }
}