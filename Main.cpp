#include "IECreator.h"
#include "Distributor.h"

//#define DEBUG

using namespace std;

#ifdef DEBUG

#include "Model.h"
#include "IE.h"
#include "Parser.h"
#include "print_node.h"

#ifdef NODE_DEBUG
// Define a function that prints out the number of Node instances created throughout the program, just to check whether there are redundant Node instances that should have been deleted or not.
void print_nodes_creations()
{
    std::cout << "Nodes created: " << Node::instance_created << std::endl;
    std::cout << "Nodes deleted: " << Node::instance_deleted << std::endl;
    std::cout << "Nodes remaining: " << Node::instance_created - Node::instance_deleted << std::endl;
}
#endif

void test_parser(string& input, string& query)
{
    cout << "INPUT:\n";

    cout << input << endl;
    cout << query << endl;
    cout << endl;

    //cout << "KB:\n\n";
    //Parser parser(input);
    //print_node_bracket_style(parser.get_tree());
    //print_node_bracket_style(parser.get_cnf_tree());
    //cout << endl;

    cout << "QUERY:\n\n";
    Parser parser_q(query);
    //print_node_bracket_style(parser_q.get_tree());
    print_node_bracket_style(parser_q.get_cnf_tree());
    cout << endl;

    string sentence = input + "~(" + query + ");";

    cout << "KB & ~QUERY:\n\n";
    Parser parser_x(sentence);
    print_node_bracket_style(parser_x.get_tree());
    print_node_bracket_style(parser_x.get_cnf_tree());
    cout << endl;
}

void test_horn(string& KB, string& query, bool quick_test = true)
{
    cout << "KB: " << KB << "\nquery: " << query << endl;

    TT ie_tt = TT(KB, query);
    FC ie_fc = FC(KB, query);
    BC ie_bc = BC(KB, query);
    
    bool result_tt = ie_tt.get_result();
    bool result_fc = ie_fc.get_result();
    bool result_bc = ie_bc.get_result();

    if (result_tt == result_fc && result_tt == result_bc)
    {
        cout << "All got the same results.\n";
    }
    else
    {
        cout << "Not all got the same results.\n";
    }

    cout << "TT: " << result_tt <<
        " FC: " << result_fc <<
        " BC: " << result_bc << "\n";

    if (quick_test)
    {
        
    }
    else
    {
        cout << "TT: "; ie_tt.print_result();
        cout << "FC: "; ie_fc.print_result();
        cout << "BC: "; ie_bc.print_result();
    }
}

void test_horn_general(string& KB, string& query, bool quick_test = true)
{
    cout << "KB: " << KB << "\nquery: " << query << endl;

    TT ie_tt = TT(KB, query);
    FC ie_fc = FC(KB, query);
    BC ie_bc = BC(KB, query);
    Resolution ie_resolution = Resolution(KB, query);
    DPLL ie_dpll = DPLL(KB, query);

    bool result_tt = ie_tt.get_result();
    bool result_fc = ie_fc.get_result();
    bool result_bc = ie_bc.get_result();
    bool result_resolution = ie_resolution.get_result();
    bool result_dpll = ie_tt.get_result();

    if (result_tt == result_fc && result_tt == result_bc && result_tt == result_resolution && result_tt == result_dpll)
    {
        cout << "All got the same results.\n";
    }
    else
    {
        cout << "Not all got the same results.\n";
    }

    cout << "TT: " << result_tt <<
        " FC: " << result_fc <<
        " BC: " << result_bc <<
        " RESOLUTION: " << result_resolution <<
        " DPLL: " << result_dpll << "\n";

    if (quick_test)
    {
        
    }
    else
    {
        cout << "TT: "; ie_tt.print_result();
        cout << "FC: "; ie_fc.print_result();
        cout << "BC: "; ie_bc.print_result();
        cout << "RESOLUTION: "; ie_resolution.print_result();
        cout << "DPLL: "; ie_dpll.print_result();
    }
}

void test_all_except_tt(string& KB, string& query, bool quick_test = true)
{
    cout << "KB: " << KB << "\nquery: " << query << endl;
    FC ie_fc = FC(KB, query);
    BC ie_bc = BC(KB, query);
    Resolution ie_resolution = Resolution(KB, query);
    DPLL ie_dpll = DPLL(KB, query);

    bool result_fc = ie_fc.get_result();
    bool result_bc = ie_bc.get_result();
    bool result_resolution = ie_resolution.get_result();
    bool result_dpll = ie_dpll.get_result();

    if (result_fc == result_bc && result_fc == result_resolution && result_fc == result_dpll)
    {
        cout << "All got the same results.\n";
    }
    else
    {
        cout << "Not all got the same results.\n";
    }

    cout << "FC: " << result_fc <<
        " BC: " << result_bc <<
        " RESOLUTION: " << result_resolution <<
        " DPLL: " << result_dpll << "\n";

    if (quick_test)
    {
        
    }
    else
    {
        cout << "FC: "; ie_fc.print_result();
        cout << "BC: "; ie_bc.print_result();
        cout << "RESOLUTION: "; ie_resolution.print_result();
        cout << "DPLL: "; ie_dpll.print_result();
    }
}


void test_general(string& KB, string& query, bool quick_test = true)
{
    cout << "KB: " << KB << "\nquery: " << query << endl;
    
    TT ie_tt = TT(KB, query);
    Resolution ie_resolution = Resolution(KB, query);
    DPLL ie_dpll = DPLL(KB, query);
    
    bool result_tt = ie_tt.get_result();
    bool result_resolution = ie_resolution.get_result();
    bool result_dpll = ie_tt.get_result();

    if (result_tt == result_resolution && result_tt == result_dpll)
    {
        cout << "All got the same results.\n";
    }
    else
    {
        cout << "Not all got the same results.\n";
    }

    cout << "TT: " << result_tt <<
        " RESOLUTION: " << result_resolution <<
        " DPLL: " << result_dpll << "\n";

    if (quick_test)
    {
        
    }
    else
    {
        cout << "TT: "; ie_tt.print_result();
        cout << "RESOLUTION: "; ie_resolution.print_result();
        cout << "DPLL: "; ie_dpll.print_result();
    }
}

int main()
{
    string KB, query;
    
    /*KB = "a <=> (b <=> (c <=> ~d)); a; c <=> ~d; b;";
    query = "(a & b) <=> (c || d)";
    test_parser(KB, query);
    test_general(KB, query, false);
    
    KB = "a <=> (b <=> (c <=> ~d)); a; c <=> ~d; b";
    query = "(a <=> b) <=> ((a & b) <=> (a || b))";
    test_general(KB, query, false);
    
    KB = "a <=> (b <=> (c <=> ~d)); a; c <=> ~d; b";
    query = "a <=> (a<=>b)";
    test_general(KB, query, false);

    KB = "a <=> (b <=> (c <=> ~d)); a; c <=> ~d; b";
    query = "(a <=> b) <=> a";
    test_general(KB, query, false);

    KB = "(a <=> (c => ~d)) & b & (b => a); c; ~f || g;";
    query = "(a <=> b) <=> a";
    test_general(KB, query, false);

    KB = "(a <=> (c => ~d)) & b & (b => a); c; ~f || g;";
    query = "a <=> (a<=>b)";
    test_general(KB, query, false);
    
    KB = "(a <=> (c => ~d)) & b & (b => a); c; ~f || g;";
    query = "(g || ~b) => ((d => a) => (d => a))";
    test_general(KB, query, false);*/
    
    /*KB = "(a <=> (c => ~d)) & b & (b => a); c; ~f || g;";
    query = "(g & ~b) => ((d => a) => (d => a))";
    test_general(KB, query);

    KB = "a <=> (b <=> (c <=> ~d)); a; c <=> ~d; b";
    query = "(a & b) <=> (c || d)";
    test_general(KB, query);*/

    KB = "p => q; l& m => p; a& b& l => m; a& p => l; a& b => l; a; b;";
    query = "q";
    test_horn_general(KB, query);
    
    KB = "a=>b; b=>c; c&d=>a; d; c; b;";
    query = "a";
    test_horn_general(KB, query);
    
    KB = "~A; (B => C) => A & B; C; C & D; A <=> D;";
    query = "D";
    test_general(KB, query);

    KB = "a & b => a;";
    query = "a";
    test_horn_general(KB, query);

    KB = "(((a & b) & (a1 & b1)) & (a2 & b2) & (a12 & b12)) & (((a3 & b3) & (a13 & b13)) & (a23 & b23) & (a123 & b123));";
    query = "d";
    test_general(KB, query);

    KB = "a <=> (b <=> (c => ~d));";
    query = "d";
    test_general(KB, query);

    KB = "p2=> p3; p3 => p1; c => e; b&e => f; f&g => h; p1=>d; p1&p3 => c; a; b; p2;";
    query = "d";
    test_horn_general(KB, query);

    query = "a";
    test_horn_general(KB, query);


    KB = "(a <=> (c => ~d)) & b & (b => a); c; ~f || g;";
    query = "d";
    test_general(KB, query);

    query = "x";
    test_general(KB, query);

    query = "~d & (~g => ~f)";
    test_general(KB, query);

    query = "c & d";
    test_general(KB, query);

    query = "f";
    test_general(KB, query);

    query = "a";
    test_general(KB, query);

    KB = "a || ~a; d;";

    query = "d";
    test_general(KB, query);

    query = "a";
    test_general(KB, query);

    KB = "a & ~a; d;";
    query = "a";
    test_general(KB, query);

    KB = "a & ~a; b;";
    query = "b";
    test_general(KB, query);

    query = "x";
    test_general(KB, query);

    KB = "p2=> p3; p3 => p1; c => e; b&e => f; f&g => h; p1=>d; p1&p3 => c; a; b; p2; p21=> p13; p13 => p11; c1 => e1; b1&e1 => f1; f1&g1 => h1; p11=>d; p11&p31 => c1; a2; b2; p21;p12&p32 => c2; a3; b3; p332; p321=> p313; p313 => p311; c31 => e1; b13&e31 => f31; f31&g31 => h31; p131=>d; p311&p31 => c13; a23; b23; p321;p1&p3 => c43; a43; b43; p42; p21=> p413; p413 => p11; c1 => e1; b1&e1 => f1; f1&g1 => h1; p11=>d4; p11&p341 => c1; a42; q42; p241;";
    query = "d4";
    test_parser(KB, query);
    test_all_except_tt(KB, query);
    
    KB = "p2=>p3; p3 => p1; p4 => p5; p6&p5 => p7; p7&p8 => p9; p1=>p10; p1&p3 => p4; p11; p6; p2; p14=> p13; p13 => p11; p12 => p13; p14&p13 => p15; p15&p16 => p17; p11=>p10; p11&p18 => p12; p18; p2; p19;p12&p20 =>p2; p23; p22; p21; p24=> p25; p26 => p27; p28 => p29; p30&p31 => p32; p33&p34 => p31; p35=>p10; p36&p31 => p13; p23; p37; p38;p1p3 =>p40; p39; p43; p42; p21=> p41; p44 => p11; p12 => p13; p14&p13 => p15; p15&p16 => p17; p11=>p4; p11&p45 => p12; p46;p47; p48;";
    query = "p4";
    test_parser(KB, query);
    test_all_except_tt(KB, query, false);

#ifdef MODEL_DEBUG
    cout << Model::instanceCreated << " " << Model::instanceDeleted;
#endif // MODEL_DEBUG


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
    /*if (method == "TT")
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
    }*/
    IECreator myFactory;
    IE* mySearch = myFactory.GetIEType(method, KB, query);
    mySearch->print_result();

    return 0;
}
#endif // DEBUG