#include "grammars.h"
#include <exception>

namespace grammars {
    Grammar::Grammar(const set<Symbol> &t, 
        const set<Symbol> &nt, 
        const vector<Rule> &r, 
        const Symbol &s, 
        const Symbol &eps_arg) : terminals(t), non_teminals(nt), rules(r), start(s) 
    {   
        eps = eps_arg;
        if(non_teminals.count(s) == 0) {
            throw std::logic_error("start symbol " + start.name() + " isn't non-terminal");
        }

        for(const auto &e : r) {
            if(!e.verify(t, nt, eps)) {
                throw std::logic_error("verify error for " + e.to_string(true));
            }
        }
    }

    std::ostream &operator<<(std::ostream &out, const Grammar &g) {
        
        out << "T: { ";
        for(const auto &e : g.terminals) {
            out << e.name() << " ";
        }

        out << "}\n" << "N: { ";
        
        for(const auto &e : g.non_teminals) {
            out << e.name() << " ";
        }

        out << "}\n" << "P: { ";

        for(const auto &e : g.rules) {
            out << "\n    " << e;
        }

        out << "\n    }\n" << "S = " << g.start.name() << "\n}";

        return out;
    }

    Symbol Grammar::replaceEps(const Symbol &s) {
        Symbol ret = eps;
        setEps(s);
        return ret;
    }
}