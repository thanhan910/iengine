#include "CNF.h"
#include "print_node.h"
#include <iostream>

CNF::CNF(Node* node) :
    root(node)
{
    root = cnf(root);
}

Node* CNF::get_root()
{
    return root;
}

Node* CNF::cnf(Node* node)
{
    // std::cout << "Current root node\n";
    // print_node_parentheses_style(node);
    // std::cout << '\n';

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
        return cnf_disjunction(node);
    }
    case NOT: {
        return cnf_negation(node);
    }
    case SYMBOL:

    default: {
        // Do nothing
        //// std::cout << "Do nothing\n";
        //// print_node_parentheses_style(node);
        //// std::cout << '\n';
        return node;
    }
    }
}

Node* CNF::cnf_implication(Node* node)
{
    // Convert A => B to ~A | B
    // std::cout << "Curent node\n";
    // print_node_parentheses_style(root);
    // std::cout << '\n';
    Node* left = new Node{ NOT, { node->children[0] } };
    Node* right = node->children[1];
    Node* disj_node = new Node{ OR, "OR", { left, right } };
    // std::cout << "Convert A => B to ~A | B\n";
    // print_node_parentheses_style(root);
    // std::cout << '\n';
    return cnf(disj_node);
}

Node* CNF::cnf_biconditional(Node* node)
{
    // Convert A <=> B to (A | ~B) & (~A | B)
    // std::cout << "Curent node\n";
    // print_node_parentheses_style(root);
    // std::cout << '\n';
    Node* left = node->children[0];
    Node* right = node->children[1];
    Node* not_left = new Node{ NOT, { left } };
    Node* not_right = new Node{ NOT, { right } };
    Node* disj_node1 = new Node{ OR, "OR", { left, not_right } };
    Node* disj_node2 = new Node{ OR, "OR", { not_left, right } };
    Node* cnf_node = new Node{ AND, "AND", { disj_node1, disj_node2 } };
    // std::cout << "A <=> B to (A | ~B) & (~A | B)\n";
    // print_node_parentheses_style(root);
    // std::cout << '\n';
    return cnf(cnf_node);
}

Node* CNF::cnf_negation(Node* node)
{
    // std::cout << "Current node\n";
    // print_node_parentheses_style(node);
    // std::cout << '\n';
    Node* child = node->children[0];
    if (child->type == SYMBOL)
    {
        // Do nothing
        //// std::cout << "Do nothing\n";
        //// print_node_parentheses_style(node);
        //// std::cout << '\n';
        return node;
    }
    else if (child->type == NOT)
    {
        // Double negation
        Node* cnf_node = child->children[0];
        delete node;
        // std::cout << "Double negation\n";
        // print_node_parentheses_style(root);
        // std::cout << '\n';
        return cnf(cnf_node);
    }
    else if (child->type == AND)
    {
        // De Morgan's law: ~(A & B) = ~A | ~B
        Node* cnf_node = new Node{ OR, "OR" };
        for (auto& grandchild : child->children)
        {
            Node* not_node = new Node{ NOT, { grandchild } };
            cnf_node->children.push_back(not_node);
        }
        delete node;
        // std::cout << "De Morgan's law: ~(A & B) = ~A | ~B\n";
        // print_node_parentheses_style(root);
        // std::cout << '\n';
        return cnf(cnf_node);
    }
    else if (child->type == OR)
    {
        // De Morgan's law: ~(A | B) = ~A & ~B
        Node* cnf_node = new Node{ AND, "AND" };
        for (auto& grandchild : child->children)
        {
            Node* not_node = new Node{ NOT, { grandchild } };
            cnf_node->children.push_back(not_node);
        }
        delete node;
        // std::cout << "De Morgan's law: ~(A | B) = ~A & ~B\n";
        // print_node_parentheses_style(root);
        // std::cout << '\n';
        return cnf(cnf_node);
    }
    else
    {
        std::cerr << "Unexpected token after negation: " << (int)(child->type) << std::endl;
        exit(1);
    }
}

Node* CNF::cnf_conjunction(Node* node)
{
    // Flatten conjunctions: (A & B) & C = A & B & C
    std::vector<Node*> flattened;
    //if (node == root)
    //{
    //    std::cout << "Flatten conjunctions: (A & B) & C = A & B & C\n";
    //    print_node_bracket_style(node);
    //    std::cout << "\n";
    //}
    for (auto& child : node->children)
    {
        if (child->type == AND)
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


    for (auto& child : node->children)
    {
        if (child->type == AND)
        {
            return cnf_conjunction(node);
        }
    }

    // std::cout << "Flatten conjunctions\n";
    // print_node_parentheses_style(root);
    // std::cout << '\n';
    return node;
}

Node* CNF::cnf_disjunction(Node* node)
{
    // Flatten disjunctions

    std::vector<Node*> flattened;

    Node* conjunction_node = nullptr; // Store conjunction if encountered in loop

    for (auto& child : node->children)
    {
        if (child->type == OR)
        {
            flattened.insert(flattened.end(), child->children.begin(), child->children.end());
            delete child;
        }
        else if (child->type == AND && conjunction_node == nullptr)
        {
            conjunction_node = child;
        }
        else
        {
            flattened.push_back(child);
        }
    }



    if (conjunction_node != nullptr)
    {
        // Distribute disjunctions over conjunctions
        
        // std::cout << "Distributing disjunctions over conjunctions\n";
        // print_node_parentheses_style(root);
        // std::cout << '\n';

        Node* cnf_node = new Node(AND, "AND");

        for (auto& child : conjunction_node->children)
        {
            Node* disj_node = new Node(OR, "OR", flattened);

            disj_node->children.push_back(child);

            disj_node = cnf(disj_node);

            cnf_node->children.push_back(disj_node);
        }

        delete node;
        // std::cout << "Distribute disjunctions over conjunctions\n";
        // print_node_parentheses_style(root);
        // std::cout << '\n';
        for (auto& child : cnf_node->children)
        {
            if (child->type == AND)
            {
                return cnf_conjunction(cnf_node);
            }
        }

        return cnf_node;
    }

    else
    {
        node->children = flattened;
        // std::cout << "Flatten disjunctions\n";
        // print_node_parentheses_style(root);
        // std::cout << "\n";
        for (auto& child : node->children)
        {
            if (child->type == OR)
            {
                return cnf_disjunction(node);
            }
        }
        return node;
    }
}

