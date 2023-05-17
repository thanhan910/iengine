#include "FC.h"
#include <unordered_map>
#include "Node.h"
#include <queue>
#include <iostream>
#include "Model.h"
#include "Parser.h"

FC::FC(std::string& kb_, std::string& query_) :
    KB(kb_),
    query(query_)
{ }

bool is_in_premise(Node* horn_clause, std::string& symbol)
{
    if (horn_clause->type == IMPLIES)
    {
        Node* premise = horn_clause->children[0];
        
        if (premise->type == AND)
        {
            for (Node* child : premise->children)
            {
                if (child->value == symbol)
                {
                    return true;
                }
            }

            return false;
        }

        else if (premise->type == SYMBOL)
        {
            return premise->value == symbol;
        }

        else return false;
    }

    return false;
}

bool FC::check()
{
    Parser parser_kb(KB);

    std::set<std::string> symbols = parser_kb.get_symbols();

    std::vector<Node*> clauses = parser_kb.get_tree()->children;

    std::unordered_map<std::string, bool> inferred;

    std::queue<std::string> agenda;
    
    std::unordered_map<Node*, size_t> count;

    // Initialize inferred symbols to false

    for (auto& symbol : symbols)
    {
        inferred[symbol] = false;
    }

    // Initialize agenda and count

    for (Node* clause : clauses)
    {
        if (clause->type == IMPLIES)
        {
            Node* premise = clause->children[0];

            if (premise->type == AND)
            {
                count[clause] = premise->children.size();
            }

            else if (premise->type == SYMBOL)
            {
                count[clause] = 1;
            }
        }

        else if (clause->type == SYMBOL)
        {
            agenda.push(clause->value);
        }
    }

    // Perform Forward Chaining

    while (!agenda.empty())
    {
        std::string symbol = agenda.front();
        agenda.pop();

        
        if (inferred[symbol])
        {
            continue;
        }

        sequence.push_back(symbol);

        // If the symbol is the query symbol, return true
        if (symbol == query)
        {
            return true;
        }

        // Infer the symbol's truth value
        inferred[symbol] = true;

        
        for (Node* clause : clauses)
        { 
            // for each Horn clause c in whose premise p appears do

            if (is_in_premise(clause, symbol))
            {
                count[clause] -= 1;

                if (count[clause] == 0)
                {
                    std::string con = clause->children[1]->value;

                    if (con == query)
                    {
                        sequence.push_back(con);

                        return true;
                    }

                    agenda.push(con);
                }
            }
        }
    }


    return false;
}
