#include "Resolution.h"
#include <iostream>
#include <vector>
#include <set>
#include "Parser.h"
#include "literal_symbols.h"

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

// DEBUG: Set helper: Print set
void print_set(const set<string>& s)
{
    for (auto& e : s)
    {
        cout << e << " ";
    }
    cout << endl;
}

// DEBUG: Set helper: Print set
void print_set(const set<set<string>>& s)
{
    for (auto& ss : s)
    {
        print_set(ss);
    }
    cout << endl;
}




// Apply the resolution rule to two clauses
set<set<string>> resolve(const set<string>& c1, const set<string>& c2)
{
    set<set<string>> resolvents;

    for (const auto& lit1 : c1)
    {
        string neg_lit1 = reverse(lit1);
        if (contains(c2, neg_lit1))
        {
            set<string> resolvent;
            for (const auto& lit2 : c2)
            {
                if (lit2 != neg_lit1)
                {
                    resolvent.insert(lit2);
                }
            }
            for (const auto& lit3 : c1)
            {
                if (lit3 != lit1)
                {
                    resolvent.insert(lit3);
                }
            }
            resolvents.insert(resolvent);
        }
    }
    return resolvents;
}




// Prove a theorem using resolution
bool resolution_prove(const string& KB, const string& query)
{
    string sentence = KB + "~(" + query + ");";
    
    Parser parser(sentence);

    vector<set<string>> cnf_clauses = parser.get_cnf_clauses();

    set<set<string>> clauses(cnf_clauses.begin(), cnf_clauses.end());

    set<set<string>> new_clauses;

    while (true)
    {
        for (auto it1 = clauses.begin(); it1 != clauses.end(); ++it1)
        {
            for (auto it2 = std::next(it1); it2 != clauses.end(); ++it2)
            {
                set<string> c1 = *it1, c2 = *it2;

                set<set<string>> resolvents = resolve(c1, c2);

                for (auto& resolvent : resolvents)
                {
                    if (resolvent.empty())
                    {
                        return true;
                    }
                    new_clauses.insert(resolvent);
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




