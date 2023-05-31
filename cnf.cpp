#include "CNF.h"
#include "print_node.h"
#include "Distributor.h"
#include <iostream>

//#define CNF_DEBUG


CNF::CNF(Node* node) :
    root(node)
{
    root = cdnf(root);
#ifdef CNF_DEBUG
    std::cout << "CDNF\n";
    print_node_infix(root);
    std::cout << '\n';
    print_node_bracket_style(root);
    std::cout << '\n';
#endif // CNF_DEBUG
    root = cnf(root);
#ifdef CNF_DEBUG
    std::cout << "CNF\n";
    print_node_infix(root);
    std::cout << '\n';
#endif // CNF_DEBUG
}

Node* CNF::get_root()
{
    return root;
}

Node* CNF::cnf(Node* node)
{
#ifdef CNF_DEBUG

    std::cout << "Current root node\n";
    print_node_infix(node);
    std::cout << '\n';
#endif // CNF_DEBUG


    if (node == nullptr)
    {
        return nullptr;
    }

    // Recursively convert children to CNF form
    for (auto& child : node->children)
    {
        child = cnf(child);
    }

    // Convert node to CNF form
    switch (node->type)
    {
    case AND: {
        return cnf_conjunction(node);
    }
    case OR: {
        return cnf_disjunction(node);
    }
    case NOT: {
        return cnf_negation(node);
    }
    case SYMBOL:

    default: {
        // Do nothing
#ifdef CNF_DEBUG
        //// std::cout << "Do nothing\n";
        //// print_node_infix(node);
        //// std::cout << '\n';
#endif // CNF_DEBUG

        return node;
    }
    }
}


Node* CNF::cdnf(Node* node)
{
#ifdef CNF_DEBUG

    std::cout << "Current root node\n";
    print_node_infix(node);
    std::cout << '\n';
#endif // CNF_DEBUG


    if (node == nullptr)
    {
        return nullptr;
    }

    /*if (node->type == IMPLIES)
    {
        return cnf_implication(node);
    }

    else if (node->type == BICONDITIONAL)
    {
        return cnf_biconditional(node);
    }*/

    // Recursively convert children to CNF form
    for (auto& child : node->children)
    {
        child = cdnf(child);
    }

    // Convert node to CNF form
    switch (node->type)
    {
    case IMPLIES: {
        return cnf_implication(node);
    }
    case BICONDITIONAL: {
        return cnf_biconditional(node);
    }
    case AND: {
        return cnf_conjunction(node);
    }
    case OR: {
        return dnf_disjunction(node);
    }
    case NOT: {
        return cnf_negation(node);
    }
    case SYMBOL:

    default: {
        // Do nothing
#ifdef CNF_DEBUG
        //// std::cout << "Do nothing\n";
        //// print_node_infix(node);
        //// std::cout << '\n';
#endif // CNF_DEBUG

        return node;
    }
    }
}

Node* CNF::cnf_implication(Node* node)
{
    // Convert A => B to ~A | B

#ifdef CNF_DEBUG
    
    std::cout << "Curent node\n";
    print_node_infix(root);
    std::cout << '\n';

#endif // CNF_DEBUG

    Node* left = new Node{ NOT, { node->children[0] } };
    Node* right = node->children[1];
    Node* disj_node = new Node{ OR, "||", { left, right } };


#ifdef CNF_DEBUG

    std::cout << "Convert A => B to ~A | B\n";
    print_node_infix(root);
    std::cout << '\n';

#endif // CNF_DEBUG
    
    return cdnf(disj_node);
}

Node* CNF::cnf_biconditional(Node* node)
{
    // Convert A <=> B to (A | ~B) & (~A | B)
    
#ifdef CNF_DEBUG
    std::cout << "Curent node\n";
    print_node_infix(node);
    std::cout << '\n';
#endif // CNF_DEBUG
    
    Node* left = node->children[0];
    Node* right = node->children[1];
    Node* not_left = new Node{ NOT, { left } };
    Node* not_right = new Node{ NOT, { right } };
    Node* disj_node1 = new Node{ OR, "||", { left, not_right } };
    Node* disj_node2 = new Node{ OR, "||", { not_left, right } };
    Node* cnf_node = new Node{ AND, "&", { disj_node1, disj_node2 } };
    
#ifdef CNF_DEBUG

    std::cout << "A <=> B to (A | ~B) & (~A | B)\n";
    print_node_infix(cnf_node);
    std::cout << '\n';
    
#endif // CNF_DEBUG

    return cdnf(cnf_node);
}

Node* CNF::cnf_negation(Node* node)
{
#ifdef CNF_DEBUG
    
    std::cout << "Current node\n";
    print_node_infix(node);
    std::cout << '\n';

#endif // CNF_DEBUG
    
    Node* child = node->children[0];
    if (child->type == SYMBOL)
    {
        return node;
    }
    else if (child->type == NOT)
    {
        // Double negation
        Node* cnf_node = child->children[0];
        delete node;

#ifdef CNF_DEBUG
        std::cout << "Double negation\n";
        print_node_infix(cnf_node);
        std::cout << '\n';
#endif
      
        return cdnf(cnf_node);
    }
    else if (child->type == AND)
    {
        // De Morgan's law: ~(A & B) = ~A | ~B
        Node* cnf_node = new Node{ OR, "||" };
        for (auto& grandchild : child->children)
        {
            Node* not_node = new Node{ NOT, { grandchild } };
            cnf_node->children.push_back(not_node);
        }
        delete node;

#ifdef CNF_DEBUG
        std::cout << "De Morgan's law: ~(A & B) = ~A | ~B\n";
        print_node_infix(cnf_node);
        std::cout << '\n';

#endif // CNF_DEBUG

        return cdnf(cnf_node);
    }
    else if (child->type == OR)
    {
        // De Morgan's law: ~(A | B) = ~A & ~B
        Node* cnf_node = new Node{ AND, "&" };
        for (auto& grandchild : child->children)
        {
            Node* not_node = new Node{ NOT, { grandchild } };
            cnf_node->children.push_back(not_node);
        }
        delete node;

#ifdef CNF_DEBUG
        std::cout << "De Morgan's law: ~(A & B) = ~A | ~B\n";
        print_node_infix(cnf_node);
        std::cout << '\n';

#endif // CNF_DEBUG
        
        return cdnf(cnf_node);
    }
    else
    {
        std::cerr << "Unexpected token after negation: " << (int)(child->type) << child->value << std::endl;
        exit(1);
    }
}

Node* CNF::cnf_conjunction(Node* node)
{
    // Flatten conjunctions: (A & B) & C = A & B & C
    std::vector<Node*> flattened;

    for (auto& child : node->children)
    {
        if (child->type == AND)
        {
            flattened.insert(flattened.end(), child->children.begin(), child->children.end());
        }
        else
        {
            flattened.push_back(child);
        }
    }
    for (auto& child : node->children)
    {
        if (child->type == AND)
        {
            delete child;
        }
    }
    node->children = flattened;

#ifdef CNF_DEBUG

    std::cout << "Flatten conjunctions\n";
    print_node_infix(node);
    std::cout << '\n';

#endif // CNF_DEBUG
    
    return node;
}

Node* CNF::cnf_disjunction(Node* node)
{
    // Flatten disjunctions

    std::vector<Node*> others;

    std::vector<std::vector<Node*>> conjunctions_list;

    for (auto& child : node->children)
    {
        if (child->type == OR)
        {
            others.insert(others.end(), child->children.begin(), child->children.end());
            delete child;
        }
        else if (child->type == AND)
        {
            conjunctions_list.push_back(child->children);
            delete child;
        }
        else
        {
            others.push_back(child);
        }
    }



    if (conjunctions_list.size() > 0)
    {
        // Distribute disjunctions over conjunctions
        // A || (X1 & X2 & X3) = (A || X1) & (A || X2) & (A || X3)

#ifdef CNF_DEBUG
        std::cout << "Start distributing disjunctions over conjunctions\n";
        //print_node_infix(node);
        std::cout << '\n';
#endif // CNF_DEBUG


        Node* cnf_node = new Node{ AND, "AND" };

        // Distribute disjunctions
        std::vector<std::vector<Node*>> disjunctions_list_pre = Distributor<Node*>(conjunctions_list).get_result();
        
        // Flatten disjunctions

        std::vector<std::vector<Node*>> disjunctions_list;
        
        for (auto& disjunction_old : disjunctions_list_pre)
        {
            std::vector<Node*> disjunction_flattened;

            for (Node* child : disjunction_old)
            {
                if (child == nullptr)
                {
                    continue;
                }

                if (child->type == OR)
                {
                    disjunction_flattened.insert(disjunction_flattened.end(), child->children.begin(), child->children.end());
                }
                else
                {
                    disjunction_flattened.push_back(child);
                }
            }

            disjunctions_list.push_back(disjunction_flattened);
        }

        for (auto& disjunction_old : disjunctions_list_pre)
        {
            for (Node* child : disjunction_old)
            {
                if (child->type == OR)
                {
                    delete child;
                }
            }
        }

        disjunctions_list_pre.clear();

        for (auto& disjunction : disjunctions_list)
        {
            disjunction.insert(disjunction.end(), others.begin(), others.end());
            
            if (disjunction.size() == 0)
            {
                continue;
            }

            else if (disjunction.size() == 1)
            {
                Node* disj_node = disjunction[0];
                cnf_node->children.push_back(disj_node);
            }

            else
            {
                Node* disj_node = new Node{ OR, "OR", disjunction };
                cnf_node->children.push_back(disj_node);
            }
        }

        delete node;

#ifdef CNF_DEBUG
        
        std::cout << "Distribute disjunctions over conjunctions\n";
        print_node_infix(cnf_node);
        std::cout << '\n';

#endif // CNF_DEBUG

        return cnf_node;
    }

    else
    {
        node->children = others;

#ifdef CNF_DEBUG

        std::cout << "Flatten disjunctions\n";
        print_node_infix(node);
        std::cout << "\n";

#endif // CNF_DEBUG

        return node;
    }
}

Node* CNF::dnf_disjunction(Node* node)
{
    // Flatten disjunctions

    std::vector<Node*> flattened;

    for (auto& child : node->children)
    {
        if (child->type == OR)
        {
            flattened.insert(flattened.end(), child->children.begin(), child->children.end());
            delete child;
        }
        else
        {
            flattened.push_back(child);
        }
    }

    node->children = flattened;

#ifdef CNF_DEBUG

    std::cout << "Flatten disjunctions\n";
    print_node_infix(node);
    std::cout << "\n";

#endif // CNF_DEBUG

    return node;
}
