#ifndef AUTOMATA_H__
#define AUTOMATA_H__

#include "grammars.h"
#include <set>
#include <map>

namespace grammars {
    using std::map;
    class Automatic {
        bool is_deterministic = false;
        bool deterministic_valid = false;

        typedef std::set<Symbol> state_t;

        // const state_t DEFAULT_FIN = { "[FIN]" };
        const state_t DEFAULT_START = { "[START]" };

        set<state_t> states = { DEFAULT_START };
        set<Symbol> terminals;

        map<state_t, map<Symbol, set<state_t>>> rules;
        
        set<state_t> start = { /* DEFAULT_START */ };
        set<state_t> fin = { /* DEFAULT_FIN */ };

    public:
        Automatic(const Grammar& g);
        Automatic();
        
        //not implemented yet
        //bool check_if_deterministic() const;
        
        void make_deterministic();

        friend std::ostream &operator<<(std::ostream &out, const Automatic &g);
    };
}  // namespace grammars
#endif