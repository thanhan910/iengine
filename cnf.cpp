#include "cnf.h"
#include "convert_to_cnf.h"
#include "Node.h"
#include "ParseTree.h"
#include "Lexer.h"

std::string convert_literal_node_to_string(Node* literal_node)
{
    if (literal_node->type == NOT)
    {
        return "~" + literal_node->children[0]->value;
    }

    else
    {
        return literal_node->value;
    }
}

std::set<std::string> convert_clause_node_to_string_sets(Node* clause_node)
{
    if (clause_node->type == NOT || clause_node->type == VARIABLE)
    {
        std::string l = convert_literal_node_to_string(clause_node);

        return { l };
    }

    else
    {
        std::set<std::string> sequence;

        for (auto& literal_node : clause_node->children)
        {
            std::string l = convert_literal_node_to_string(literal_node);

            sequence.insert(l);
        }

        return sequence;
    }
}

std::vector<std::set<std::string>> convert_cnf_node_to_string_sets(Node* cnf_node)
{
    if (cnf_node->type == NOT || cnf_node->type == VARIABLE)
    {
        std::string l = convert_literal_node_to_string(cnf_node);

        return { { l } };
    }

    else if (cnf_node->type == OR)
    {
        std::set<std::string> clause = convert_clause_node_to_string_sets(cnf_node);

        return { clause };
    }

    else
    {
        std::vector<std::set<std::string>> sequence;

        for (auto& clause_node : cnf_node->children)
        {
            std::set<std::string> clause = convert_clause_node_to_string_sets(clause_node);

            sequence.push_back(clause);
        }

        return sequence;
    }
}



std::vector<std::set<std::string>> cnf(const std::string& input)
{
    std::vector<Token> tokens = Lexer(input).fToken;

    ParseTree parser(tokens);

    parser.parse();

    Node* cnf_root = convert_to_cnf(parser.root_node);

    return convert_cnf_node_to_string_sets(cnf_root);
}

