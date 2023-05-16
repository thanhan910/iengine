#include <iostream>

#include "TT.h"
#include "FC.h"
#include "BC.h"
#include "DPLL.h"
#include "Resolution.h"

#include "Parser.h"
#include "print_node.h"

using namespace std;

// Define a function that prints out the number of Node instances created throughout the program, just to check whether there are redundant Node instances that should have been deleted or not.
void print_nodes_creations()
{
    std::cout << "Nodes created: " << Node::instance_created << std::endl;
    std::cout << "Nodes deleted: " << Node::instance_deleted << std::endl;
    std::cout << "Nodes remaining: " << Node::instance_created - Node::instance_deleted << std::endl;
}

void test_parser(string& input, string& query)
{
    cout << "INPUT:\n";

    cout << input << endl;
    cout << query << endl;
    cout << endl;

    cout << "TREE KB:\n\n";
    Parser parser(input);
    print_node(parser.get_tree());
    cout << endl;

    cout << "QUERY TREE :\n\n";
    Parser parser_q(query);
    print_node(parser_q.get_tree());
    cout << endl;
}

void tt(string& input, string& query)
{
    // TEST TT

    TT ie_tt = TT(input, query);

    if (ie_tt.check())
    {
        cout << "YES: " << ie_tt.model_count << endl;
    }

    else
    {
        cout << "NO\n";
    }
}

void fc(string& input, string& query)
{
    // TEST FC

    FC ie_fc = FC(input, query);

    if (ie_fc.check())
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
}

void bc(string& input, string& query)
{
    // TEST BC

    BC ie_bc = BC(input, query);

    if (ie_bc.check())
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

void dpll(string& input, string& query)
{
    cout << (dpll_prove(input, query) ? "YES" : "NO") << endl;
}

void res(string& input, string& query)
{
    cout << (resolution_prove(input, query) ? "YES" : "NO") << endl;
}

void test_horn(string& input, string& query)
{
    tt(input, query);

    fc(input, query);

    bc(input, query);


}

void test_general(string& input, string& query)
{

    tt(input, query);

    dpll(input, query);

    res(input, query);
    
}



// Example usage
int main()
{

    // Read input from standard input
    string input, query;
    input = "p2=> p3; p3 => p1; c => e; b&e => f; f&g => h; p1=>d; p1&p3 => c; a; b; p2;";
    //query = "d";
    //test_horn(input, query);
    
    query = "a";
    test_horn(input, query);


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