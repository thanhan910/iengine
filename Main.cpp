#include <iostream>

#include "TT.h"
#include "FC.h"
#include "BC.h"
#include "DPLL.h"
#include "Resolution.h"

#include "Lexer.h"
#include "ParseTree.h"
#include "print_node.h"

using namespace std;

// Define a function that prints out the number of Node instances created throughout the program, just to check whether there are redundant Node instances that should have been deleted or not.
void print_nodes_creations()
{
    std::cout << "Nodes created: " << Node::instance_created << std::endl;
    std::cout << "Nodes deleted: " << Node::instance_deleted << std::endl;
    std::cout << "Nodes remaining: " << Node::instance_created - Node::instance_deleted << std::endl;
}

void test(string& input, string& query)
{
    cout << "INPUT:\n";

    cout << input << endl;
    cout << query << endl;
    cout << endl;

    cout << "TREE KB:\n\n";
    ParseTree tree(Lexer(input).fToken);
    tree.parse();
    print_node(tree.root_node);
    cout << endl;

    cout << "QUERY TREE :\n\n";
    ParseTree treeq(Lexer(query).fToken);
    treeq.parse();
    print_node(treeq.root_node);
    cout << endl;

    // Test inference engines
    bool result;

    // TEST TT

    TT ie_tt = TT(input, query);

    result = ie_tt.check();

    if (result)
    {
        cout << "YES: " << ie_tt.model_count << endl;
    }

    else
    {
        cout << "NO\n";
    }

    // TEST FC

    FC ie_fc = FC(input, query);

    result = ie_fc.check();

    if (result)
    {
        cout << "YES:";

        for (int i = 0; i < ie_fc.sequence.size(); i++)
        {
            cout << " " << ie_fc.sequence[i];

            if (i < ie_fc.sequence.size() - 1)
            {
                cout << ",";
            }
        }

        cout << endl;
    }

    else
    {
        cout << "NO\n";
    }

    // TEST BC

    BC ie_bc = BC(input, query);

    result = ie_bc.check();

    if (result)
    {
        cout << "YES:";

        for (int i = 0; i < ie_bc.sequence.size(); i++)
        {
            cout << " " << ie_bc.sequence[i];

            if (i < ie_bc.sequence.size() - 1)
            {
                cout << ",";
            }
        }

        cout << endl;
    }

    else
    {
        cout << "NO\n";
    }
}

void test_general(string& input, string& query)
{
    cout << "INPUT:\n";

    cout << input << endl;
    cout << query << endl;
    cout << endl;

    cout << "TREE KB:\n\n";
    ParseTree tree(Lexer(input).fToken);
    tree.parse();
    print_node(tree.root_node);
    cout << endl;

    cout << "QUERY TREE :\n\n";
    ParseTree treeq(Lexer(query).fToken);
    treeq.parse();
    print_node(treeq.root_node);
    cout << endl;

    // Test inference engines
    bool result;

    // TEST TT

    TT ie_tt = TT(input, query);

    result = ie_tt.check();

    if (result)
    {
        cout << "YES: " << ie_tt.model_count << endl;
    }

    else
    {
        cout << "NO\n";
    }

    // TEST DPLL

    result = dpll_prove(input, query);

    cout << (result ? "YES" : "NO") << endl;

    // TEST RESOLUTION

    result = resolution_prove(input, query);

    cout << (result ? "YES" : "NO") << endl;
    
}



// Example usage
int main()
{

    // Read input from standard input
    string input, query;
    input = "p2=> p3; p3 => p1; c => e; b&e => f; f&g => h; p1=>d; p1&p3 => c; a; b; p2;";
    query = "d";

    test(input, query);
    

    input = "(a <=> (c => ~d)) & b & (b => a); c; ~f || g;";
    query = "d";

    test_general(input, query);

    query = "c";
    test_general(input, query);

    query = "c & d";
    test_general(input, query);


    query = "f";
    test_general(input, query);
    
    return 0;
}