#include <string>
#include <iostream>
#include "grammars/grammars.h"
#include "grammars/automata.h"

using namespace std;

namespace grammars {
    extern const char* NAMES[];
}

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
    // Grammar g1(
    //     { "a", "b", "c", "d" },
    //     { "A", "B", "C", "D", "AB", s_sym },
    //     {   
    //         r1, r2,
    //         r,
    //         { {"A"}, {"B"} },
    //         { { s_sym }, { "B" } },
    //         { { "A" }, { "B", s_sym, "A" } },
    //         string("A.B -> B.A"),
    //         string("A.B -> @"),
    //         string("A.B -> AB"),
    //         { { s_sym }, { } },
    //     },
    //     s_sym
    // );

    // Grammar g1(
    //     { "a", "b", "c" },
    //     { "S", "B", "C", "D" },
    //     {   
    //         string("S -> a.S.B.C"),
    //         string("S -> a.b.C"),
    //         string("C.B -> C.D"),
    //         string("C.D -> B.D"),
    //         string("B.D -> B.C"),
    //         string("b.B -> b.b"),
    //         string("b.C -> b.c"),
    //         string("c.C -> c.c"),
    //     },
    //     "S"
    // );

    // Grammar g1(
    //     { "a", "b"},
    //     { "S", "A", "C", "B" },
    //     {   
    //         string("S -> a.S"),
    //         string("S -> S.a"),
    //         string("S -> C"),
    //         string("C -> C.C"),
    //         string("C -> b.A"),
    //         string("C -> @"),
    //         string("A -> a.B"),
    //         string("A -> @"),
    //         string("B -> a.A"),
    //         string("B -> a"),
    //     },

    //     "S"
    // );

    // Grammar g1(
    //     { "a", "b", "c", "d"},
    //     { "S", "A", "C", "B" },
    //     {   
    //         string("S -> a.B.S"),
    //         string("S -> b.C.A.C.d"),
    //         string("A -> b.A.B"),
    //         string("A -> c.S.A"),
    //         string("A -> c.C.C"),
    //         string("B -> b.A.B"),
    //         string("B -> c.S.B"),
    //         string("C -> c.S"),
    //         string("C -> c"),
    //     },

    //     "S"
    // );
    // Grammar g1(
    //     { "a", "b", "c", "d", "e", "f", "g"},
    //     { "S", "A", "B", "C", "E", "D" },
    //     {   
    //         string("S -> a.A.B"),
    //         string("S -> E"),
    //         string("A -> d.D.A"),
    //         string("A -> @"),
    //         string("B -> b.E"),
    //         string("B -> f"),
    //         string("C -> c.A.B"),
    //         string("C -> d.S.D"),
    //         string("C -> a"),
    //         string("D -> e.A"),
    //         string("E -> f.A"),
    //         string("E -> g"),
    //     },

    //     "S"
    // );
    
    Grammar g1(
        { "a", "b" },
        { "A", "B", "S"},
        {   
            string("S -> a"),
            string("S -> a.A"),
            string("S -> a.B"),

            string("A -> a.A"),
            string("A -> a.B"),

            string("B -> a.B"),
            string("B -> a"),
        },

        "S"
    );
    
    cout << "parsed" << endl;

    cout << "gramm g1: " << endl << g1 << endl;

    cout << NAMES[TYPE_0] << " :" << g1.check_if_type_zero() << endl;
    cout << NAMES[NONCONTR] << " :" << g1.check_if_noncontracting() << endl;
    cout << NAMES[CONT_SENS] << " :" << g1.check_if_context_sensitive() << endl;
    cout << NAMES[CONT_FREE] << " :" << g1.check_if_context_free() << endl;
    cout << NAMES[REGULAR] << " :" << g1.check_if_regular() << endl;
    cout << NAMES[REGULAR_RIGHT] << " :" << g1.check_if_regular_right() << endl;
    cout << NAMES[REGULAR_LEFT] << " :" << g1.check_if_regular_left() << endl;
    cout << NAMES[AUTOMATIC] << " :" << g1.check_if_automatic() << endl;

    auto a1 = Automatic(g1);
    cout << "automata: " << endl << a1 << endl;
    a1.make_deterministic();
    cout << "automata: " << endl << a1 << endl;

    // cout << "make_noncontracting" << endl;
    // g1.remove_barren_characters();
    // g1.remove_unreachable_characters();

    // cout << "gramm g1: " << endl << g1 << endl;

    // cout << NAMES[TYPE_0] << " :" << g1.check_if_type_zero() << endl;
    // cout << NAMES[NONCONTR] << " :" << g1.check_if_noncontracting() << endl;
    // cout << NAMES[CONT_SENS] << " :" << g1.check_if_context_sensitive() << endl;
    // cout << NAMES[CONT_FREE] << " :" << g1.check_if_context_free() << endl;
    // cout << NAMES[REGULAR] << " :" << g1.check_if_regular() << endl;
    // cout << NAMES[REGULAR_RIGHT] << " :" << g1.check_if_regular_right() << endl;
    // cout << NAMES[REGULAR_LEFT] << " :" << g1.check_if_regular_left() << endl;
    // cout << NAMES[AUTOMATIC] << " :" << g1.check_if_automatic() << endl;
}