#include "FC.h"
#include <unordered_map>
#include "Node.h"
#include <queue>
#include <iostream>
#include "Model.h"
#include "ParseTree.h"
#include "Lexer.h"

FC::FC(std::string& kb_, std::string& query_) :
    query(query_)
{
    ParseTree tree_kb(Lexer(kb_).fToken);
    tree_kb.parse();
    kb = tree_kb.root_node;
}

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

        else if (premise->type == VARIABLE)
        {
            return premise->value == symbol;
        }

        else return false;
    }

    return false;
}

bool FC::check()
{
    std::set<std::string> symbols = get_symbols(kb);

    std::unordered_map<std::string, bool> inferred;
    std::queue<std::string> agenda;
    std::unordered_map<Node*, size_t> count;

    // Initialize inferred symbols to false

    for (auto& symbol : symbols)
    {
        inferred[symbol] = false;
    }

    for (Node* clause : kb->children)
    {
        if (clause->type == IMPLIES)
        {
            Node* premise = clause->children[0];

            if (premise->type == AND)
            {
                count[clause] = premise->children.size();
            }

            else if (premise->type == VARIABLE)
            {
                count[clause] = 1;
            }
        }

        else if (clause->type == VARIABLE)
        {
            agenda.push(clause->value);
        }
    }

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

        
        for (Node* clause : kb->children)
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
