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
    return set_.count(element) > 0;
}



Resolution::Resolution(std::string& KB, std::string& query) :
    IE(KB, query)
{
    string sentence = KB + "~(" + query + ");";

    vector<Clause> cnf_clauses = Parser(sentence).get_cnf_clauses();

    clauses = set<Clause>(cnf_clauses.begin(), cnf_clauses.end());
    kb_entails_query = check();
}


// Prove a theorem using resolution
bool Resolution::check()
{
    while (true)
    {
        std::set<Clause> new_clauses;

        for (auto it1 = clauses.begin(); it1 != clauses.end(); ++it1)
        {
            for (auto it2 = std::next(it1); it2 != clauses.end(); ++it2)
            {
                Clause c1 = *it1, c2 = *it2;

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
                        if (resolvent.empty())
                        {
                            return true;
                        }
                        new_clauses.insert(resolvent);
                    }
                }
            }
        }
        if (contains(clauses, new_clauses))
        {
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
    if (kb_entails_query)
    {
        std::cout << "YES";
    }

    else
    {
        std::cout << "NO";
    }

    std::cout << '\n';
}
