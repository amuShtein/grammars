#include "grammars.h"
#include "automata.h"
#include "functional"

namespace grammars {
    // constructors
    
    /* @throws logical_error */
    Automatic::Automatic(const Grammar& g) {
        if(!g.check_if_automatic()) {
            throw std::logic_error("can't make automata: grammar is not automatic");
        }
        
        bool is_left = g.check_if_regular_left();

        fin.insert({ g.getStart() });
        for(const auto& rule : g.getRules()) {
            state_t left_state = { rule.frontLeft() };
            
            switch(rule.lenRight()) {
                case 0:
                    start.insert({rule.frontLeft()});
                    break;
                case 1: {
                    states.insert(left_state);
                    terminals.insert(rule.frontRight());

                    rules[DEFAULT_START][rule.frontRight()].insert(left_state);
                    states.insert(DEFAULT_START);
                    start.insert(DEFAULT_START);

                    break;
                }
                case 2: {
                    state_t right_state;
                    Symbol term;

                    if(is_left) {
                        right_state = { rule.frontRight() };
                        term = rule.backRight();
                    } else {
                        right_state = { rule.backRight() };
                        term = rule.frontRight();
                    }

                    rules[right_state][term].insert(left_state);
                    break;
                }
                default:
                    throw std::logic_error("automatic grammar has too large rule");
                    break;
            }
            
        }
    }

    Automatic::Automatic() {
        states = {};
        fin = {};
    };
    /* not implemented
    bool Automatic::check_if_deterministic() const {
        return false;
    };
    */
    void Automatic::make_deterministic() {
        if(deterministic_valid && is_deterministic) {
            return;
        }

        set<state_t> unparsed;

        set<state_t> new_states;

        map<state_t, map<Symbol, set<state_t>>> new_rules;
        
        set<state_t> new_fin;

        state_t new_start_state;
        
        for(const auto& e : start) {
            new_start_state.insert(e.begin(), e.end());
        }

        set<state_t> new_start = { new_start_state };

        unparsed.insert(new_start_state);
        new_states.insert(new_start_state);

        while (!unparsed.empty()) {
            set<state_t> to_insert;

            for(const auto& unparsed_state : unparsed) {
                for(const auto &sym : unparsed_state) {
                    auto rsym_it = rules.find({ sym });
                    if(rsym_it != rules.end()) {
                        for(const auto &by_nt : rsym_it->second) {
                            new_rules[unparsed_state][by_nt.first].insert(by_nt.second.begin(), by_nt.second.end());
                        }
                    }
                }

                auto state_it = new_rules.find(unparsed_state);
                if(state_it != new_rules.end()) {
                    for(const auto& by_nt : state_it->second) {
                        state_t inner_state;
                        bool is_fin = false;
                        for(const auto& inner_states : by_nt.second) {
                            if(!is_fin && fin.count(inner_states)) {
                                is_fin = true;
                            }
                            inner_state.insert(inner_states.begin(), inner_states.end());
                        }


                        new_rules[unparsed_state][by_nt.first] = { inner_state };
                        if(is_fin) {
                            new_fin.insert(inner_state);
                        }

                        if(new_states.insert(inner_state).second) {
                            to_insert.insert(inner_state);
                        }
                    }
                }

            }

            unparsed = to_insert;
        }

        states = new_states;
        rules = new_rules;
        start = new_start;
        fin = new_fin;
    };


    std::ostream &operator<<(std::ostream &out, const Automatic &a) {
        out << "STATES: {\n";
        for(const auto &e : a.states) {
            out << "    ";
            for(const auto &sym : e) {
                out << "[" << sym.name() << "]"; 
            }
            out << "\n";
        }
        out << "}\n" << "TERMINALS: { ";
        
        for(const auto &e : a.terminals) {
            out << e.name() << ", ";
        }

        out << "}\n" << "RULES: {\n";

        for(const auto &nt_line : a.rules) {
            for(const auto &t_line : nt_line.second) {
                for(const auto& state : t_line.second) {
                    out << "    [";
                    for(const auto &sym : nt_line.first) {
                    out << sym.name(); 
                    }
                    out << "](" << t_line.first.name() << ") = ";
                    for(const auto &sym : state) {
                    out << sym.name(); 
                    }
                    
                    out << "\n";
                }
            }
        }

        out << "START: {\n";
        for(const auto &e : a.start) {
            out << "    ";
            for(const auto &sym : e) {
                out << "[" << sym.name() << "]"; 
            }
            out << "\n";
        }
        out << "}\n";

        out << "FINAL: {\n";
        for(const auto &e : a.fin) {
            out << "    ";
            for(const auto &sym : e) {
                out << "[" << sym.name() << "]"; 
            }
            out << "\n";
        }
        out << "}";

        return out;
    }
}