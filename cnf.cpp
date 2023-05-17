#include "cnf.h"
#include <iostream>



Node* cnf_implication(Node* node)
{
    // Convert A => B to ~A | B
    Node* left = new Node{ NOT, { node->children[0] } };
    Node* right = node->children[1];
    Node* disj_node = new Node{ OR, "OR", { left, right } };
    return cnf(disj_node);
}

Node* cnf_biconditional(Node* node)
{
    // Convert A <=> B to (A | ~B) & (~A | B)
    Node* left = node->children[0];
    Node* right = node->children[1];
    Node* not_left = new Node{ NOT, { left } };
    Node* not_right = new Node{ NOT, { right } };
    Node* disj_node1 = new Node{ OR, "OR", { left, not_right } };
    Node* disj_node2 = new Node{ OR, "OR", { not_left, right } };
    Node* cnf_node = new Node{ AND, "AND", { disj_node1, disj_node2 } };
    return cnf(cnf_node);
}

Node* cnf_negation(Node* node)
{
    Node* child = node->children[0];
    if (child->type == SYMBOL)
    {
        // Do nothing
        return node;
    }
    else if (child->type == NOT)
    {
        // Double negation
        Node* cnf_node = child->children[0];
        delete node;
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
        return cnf(cnf_node);
    }
    else
    {
        std::cerr << "Unexpected token after negation: " << (int)(child->type) << std::endl;
        exit(1);
    }
}

Node* cnf_conjunction(Node* node)
{
    // Flatten conjunctions: (A & B) & C = A & B & C
    std::vector<Node*> flattened;
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
    return node;
}

Node* cnf_disjunction(Node* node)
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

        Node* cnf_node = new Node(AND, "AND");

        for (auto& child : conjunction_node->children)
        {
            Node* disj_node = new Node(OR, "OR", flattened);

            disj_node->children.push_back(child);

            disj_node = cnf(disj_node);

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

Node* cnf(Node* node)
{
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
    case NOT: {
        return cnf_negation(node);
    }
    case AND: {
        return cnf_conjunction(node);
    }
    case OR: {
        return cnf_disjunction(node);
    }

    case SYMBOL:

    default: {
        // Do nothing
        return node;
    }
    }
}