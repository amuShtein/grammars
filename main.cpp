#include <string>
#include <iostream>
#include "grammars.h"

using namespace std;
using namespace grammars;

int main() {
    Grammar g(
        { "a", "b", "c" },
        { "A", "B", "C", "S" },
        { Rule() },
        "S"
    );


    Rule r1 = Rule(
        {"A", "B", "C"},
        {"a", "b", "c"}
    );

    Rule r2 = Rule(
        {"D", "B", "A"},
        {"d", "b", "a"}
    );

    // cout << r1 << endl;

    // cout << r2.to_string("-->", '.', true) << endl;
    Symbol s_sym = "[START]";
    Grammar g1(
        { "a", "b", "c", "d" },
        { "A", "B", "C", "D", s_sym },
        {   r1, r2,
            { {"A"}, {"B"} },
            { {s_sym}, {"B"} },
            { {"A"}, {"B", s_sym, "A"} },
        },
        s_sym
    );

    cout << "gramm g1: " << endl << g1 << endl;
}