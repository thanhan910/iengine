#include "convert_to_cnf.h"
#include <iostream>



Node* convert_to_cnf_implication(Node* node)
{
    // Convert A => B to ~A | B
    Node* left = new Node{ TokenType::NOT, { node->children[0] } };
    Node* right = node->children[1];
    Node* disj_node = new Node{ TokenType::OR, "OR", { left, right } };
    return convert_to_cnf(disj_node);
}

Node* convert_to_cnf_biconditional(Node* node)
{
    // Convert A <=> B to (A | ~B) & (~A | B)
    Node* left = node->children[0];
    Node* right = node->children[1];
    Node* not_left = new Node{ TokenType::NOT, { left } };
    Node* not_right = new Node{ TokenType::NOT, { right } };
    Node* disj_node1 = new Node{ TokenType::OR, "OR", { left, not_right } };
    Node* disj_node2 = new Node{ TokenType::OR, "OR", { not_left, right } };
    Node* cnf_node = new Node{ TokenType::AND, "AND", { disj_node1, disj_node2 } };
    return convert_to_cnf(cnf_node);
}

Node* convert_to_cnf_negation(Node* node)
{
    Node* child = node->children[0];
    if (child->type == TokenType::VARIABLE)
    {
        // Do nothing
        return node;
    }
    else if (child->type == TokenType::NOT)
    {
        // Double negation
        Node* cnf_node = child->children[0];
        delete node;
        return convert_to_cnf(cnf_node);
    }
    else if (child->type == TokenType::AND)
    {
        // De Morgan's law: ~(A & B) = ~A | ~B
        Node* cnf_node = new Node{ TokenType::OR, "OR" };
        for (auto& grandchild : child->children)
        {
            Node* not_node = new Node{ TokenType::NOT, { grandchild } };
            cnf_node->children.push_back(not_node);
        }
        delete node;
        return convert_to_cnf(cnf_node);
    }
    else if (child->type == TokenType::OR)
    {
        // De Morgan's law: ~(A | B) = ~A & ~B
        Node* cnf_node = new Node{ TokenType::AND, "AND" };
        for (auto& grandchild : child->children)
        {
            Node* not_node = new Node{ TokenType::NOT, { grandchild } };
            cnf_node->children.push_back(not_node);
        }
        delete node;
        return convert_to_cnf(cnf_node);
    }
    else
    {
        std::cerr << "Unexpected token after negation: " << (int)(child->type) << std::endl;
        exit(1);
    }
}

Node* convert_to_cnf_conjunction(Node* node)
{
    // Flatten conjunctions: (A & B) & C = A & B & C
    std::vector<Node*> flattened;
    for (auto& child : node->children)
    {
        if (child->type == TokenType::AND)
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
    return node;
}

Node* convert_to_cnf_disjunction(Node* node)
{
    // Flatten disjunctions
    std::vector<Node*> flattened;

    // Store conjunction if encountered
    Node* conjunction_node = nullptr;

    for (auto& child : node->children)
    {
        if (child->type == TokenType::OR)
        {
            flattened.insert(flattened.end(), child->children.begin(), child->children.end());
            delete child;
        }
        else if (child->type == TokenType::AND && conjunction_node == nullptr)
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

        Node* cnf_node = new Node(AND, "AND");

        for (auto& child : conjunction_node->children)
        {
            Node* disj_node = new Node(OR, "OR", flattened);

            disj_node->children.push_back(child);

            disj_node = convert_to_cnf(disj_node);

            cnf_node->children.push_back(disj_node);
        }

        delete node;

        return cnf_node;
    }

    else
    {
        node->children = flattened;

        return node;
    }
}

Node* convert_to_cnf(Node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    // Recursively convert children to CNF form
    for (auto& child : node->children)
    {
        child = convert_to_cnf(child);
    }

    // Convert node to CNF form
    switch (node->type)
    {
    case TokenType::IMPLIES: {
        return convert_to_cnf_implication(node);
    }
    case TokenType::BICONDITIONAL: {
        return convert_to_cnf_biconditional(node);
    }
    case TokenType::NOT: {
        return convert_to_cnf_negation(node);
    }
    case TokenType::AND: {
        return convert_to_cnf_conjunction(node);
    }
    case TokenType::OR: {
        return convert_to_cnf_disjunction(node);
    }

    case TokenType::VARIABLE:

    default: {
        // Do nothing
        return node;
    }
    }
}