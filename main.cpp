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

    Rule r = Rule(
        { Symbol("A"), "A" },
        {  }
    );

    cout << r << endl;
    // cout << r1 << endl;

    // cout << r2.to_string("-->", '.', true) << endl;
    Symbol s_sym = "[START]";
    Grammar g1(
        { "a", "b", "c", "d" },
        { "A", "B", "C", "D", s_sym },
        {   r1, r2, r,
            { {"A"}, {"B"} },
            { { s_sym }, { "B" } },
            { { "A" }, { "B", s_sym, "A" } },
            string("A.B -> A.B"),
            // string("A.B -> @"),
            // string("A.B -> @"),
            { { s_sym }, { } },
            // Rule( { "D", "B" }, {  } )
        },
        s_sym
    );
    cout << "parsed" << endl;

    cout << "gramm g1: " << endl << g1 << endl;

    cout << g1.check_if_type_zero() << endl;
    cout << g1.check_if_noncontracting() << endl;
}