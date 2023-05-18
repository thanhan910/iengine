#include "Resolution.h"
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <utility>
#include "Parser.h"
#include "Literal.h"


using namespace std;


// Set helper: Check if a set contains a set
template <typename SetType>
bool contains(const SetType& set1, const SetType& set2)
{
    for (const auto& elem : set2)
    {
        if (set1.find(elem) == set1.end())
        {
            return false;
        }
    }
    return true;
}

// Set helper: Check if a set contains an element
template <typename T>
bool contains(const set<T>& set_, const T& element)
{
    return set_.find(element) != set_.end();
}



Resolution::Resolution(std::string& KB, std::string& query) :
    IE(KB, query)
{
    string sentence = KB + "~(" + query + ");";

    vector<Clause> cnf_clauses = Parser(sentence).get_cnf_clauses();

    clauses = set<Clause>(cnf_clauses.begin(), cnf_clauses.end());
    original_clauses = set<Clause>(cnf_clauses.begin(), cnf_clauses.end());
    kb_entails_query = check();
}

bool is_tautology(Clause clause)
{
    set<string> symbols;

    for (auto& lit : clause)
    {
        string s = get_symbol(lit);
        if (symbols.count(s))
        {
            return true;
        }
        symbols.insert(s);
    }

    return false;
}


// Prove a theorem using resolution
bool Resolution::check()
{
    while (true)
    {
        bool new_clause_derived = false;

        // For each pair of clauses
        for (auto it1 = clauses.begin(); it1 != clauses.end(); ++it1)
        {
            Clause c1 = *it1;
            if (is_tautology(c1)) continue; // skip if is a tautology
            
            for (auto it2 = std::next(it1); it2 != clauses.end(); ++it2)
            {
                Clause c2 = *it2;
                if (is_tautology(c2)) continue; // skip if is a tautology

                for (const auto& lit : c1)
                {
                    string neg_lit = reverse(lit);
                    if (c2.count(neg_lit))
                    {
                        Clause resolvent;
                        for (const auto& lit2 : c2)
                        {
                            if (lit2 != neg_lit)
                            {
                                resolvent.insert(lit2);
                            }
                        }
                        for (const auto& lit1 : c1)
                        {
                            if (lit1 != lit)
                            {
                                resolvent.insert(lit1);
                            }
                        }
                        if (!is_tautology(resolvent))
                        {                            
                            if (resolvent.empty()) 
                            {
                                // Contradiction reached
                                sequence.emplace_back(resolvent, c1, c2);
                                return true; 
                            }
                            
                            if (!contains(clauses, resolvent))
                            {
                                // Add new resolvent clause only if it is not in clauses
                                new_clause_derived = true;
                                sequence.emplace_back(resolvent, c1, c2);
                                clauses.insert(resolvent);
                                new_clauses.insert(resolvent);
                            }
                        }
                        break;
                    }
                }
            }
        }
        if (!new_clause_derived)
        {
            // If no new clauses derived, then the sentence is satisfiable, i.e.
            return false;
        }
        for (const auto& clause : new_clauses)
        {
            clauses.insert(clause);
        }
    }
}

void Resolution::print_result()
{
    cout << (kb_entails_query ? "YES" : "NO");
    cout << endl;
    cout << "Sentence in CNF form:\n";
    for (Clause clause : original_clauses)
    {
        print_clause(clause, " ", "{ ", " }");
        cout << "; ";
    }
    cout << endl;
    cout << "All clauses:\n";
    for (Clause clause : clauses)
    {
        print_clause(clause, " ", "{ ", " }");
        cout << "; ";
    }
    cout << endl;
    cout << "New clauses:\n";
    for (Clause clause : new_clauses)
    {
        print_clause(clause, " ", "{ ", " }");
        cout << "; ";

    }
    cout << endl;
    if (kb_entails_query)
    {
        cout << "Sequence:\n";
        for (auto& clauses : sequence)
        {
            Clause resolvent = get<0>(clauses);
            Clause c1 = get<1>(clauses);
            Clause c2 = get<2>(clauses);

            print_clause(c1, " ", "{ ", " }");
            cout << " & ";
            print_clause(c2, " ", "{ ", " }");
            cout << " => ";
            print_clause(resolvent, " ", "{ ", " }");
            cout << endl;
        }
    }
}
