#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

#include "TT.h"
#include "FC.h"
#include "BC.h"
#include "DPLL.h"
#include "Resolution.h"

#define DEBUG

using namespace std;

#ifdef DEBUG

#include "Model.h"
#include "IE.h"
#include "Parser.h"
#include "print_node.h"

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

    cout << "KB:\n\n";
    Parser parser(input);
    print_node_bracket_style(parser.get_tree());
    cout << endl;

    cout << "QUERY:\n\n";
    Parser parser_q(query);
    print_node_bracket_style(parser_q.get_tree());
    cout << endl;
}

void test_horn(string& KB, string& query)
{
    cout << KB << endl << query << endl;
    cout << "TT:\n"; TT(KB, query).print_result();
    cout << "FC:\n"; FC(KB, query).print_result();
    cout << "BC:\n"; BC(KB, query).print_result();
}

void test_general(string& KB, string& query)
{
    cout << KB << endl << query << endl;
    cout << "TT:\n"; TT(KB, query).print_result();
    cout << "RESOLUTION:\n"; Resolution(KB, query).print_result();
    cout << "DPLL:\n"; DPLL(KB, query).print_result();
}

int main()
{
    string KB, query;

    KB = "p2=> p3; p3 => p1; c => e; b&e => f; f&g => h; p1=>d; p1&p3 => c; a; b; p2;";
    query = "d";
    test_horn(KB, query);

    query = "a";
    test_horn(KB, query);


    KB = "(a <=> (c => ~d)) & t & (t => a); c; ~f || g;";

    query = "d";
    test_general(KB, query);

    query = "x";
    test_general(KB, query);

    query = "c & d";
    test_general(KB, query);

    query = "f";
    test_general(KB, query);

    query = "a";
    test_general(KB, query);

    cout << Model::instanceCreated << " " << Model::instanceDeleted;

    return 0;
}

#else

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Command should be: " << argv[0] << " <method> <filename>\n";
        return 0;
    }

    string method = argv[1], filename = argv[2];

    // Open and read file
    ifstream input_file(argv[2]);
    if (!input_file.is_open())
    {
        std::cerr << "Could not open file " << argv[2] << endl;
        return 0;
    }

    // Read each line in file
    string TELL, KB, ASK, query;
    getline(input_file, TELL); // Read "TELL"
    getline(input_file, KB); // Read Knowledge Base
    getline(input_file, ASK); // Read "ASK"
    getline(input_file, query); // Read query


    // Convert method to uppercase
    for (char& c : method)
    {
        c = toupper(c);
    }
    // Create and run IE
    if (method == "TT")
    {
        TT(KB, query).print_result();
    }
    else if (method == "FC")
    {
        FC(KB, query).print_result();
    }
    else if (method == "BC")
    {
        BC(KB, query).print_result();
    }
    else if (method == "DPLL")
    {
        DPLL(KB, query).print_result();
    }
    else if (method == "RESOLUTION")
    {
        Resolution(KB, query).print_result();
    }
    else if (method == "HORN")
    {
        TT(KB, query).print_result();
        FC(KB, query).print_result();
        BC(KB, query).print_result();
    }
    else if (method == "GENERIC")
    {
        TT(KB, query).print_result();
        Resolution(KB, query).print_result();
        DPLL(KB, query).print_result();
    }
    else
    {
        // If method is not available, exit
        std::cerr << "<method> when in uppercase should be TT, FC, BC, DPLL, RESOLUTION, HORN, or GENERIC\n";
        return 0;
    }
    return 0;
}
#endif // DEBUG