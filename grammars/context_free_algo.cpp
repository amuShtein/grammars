#include "grammars.h"
#include <exception>
#include <set>
#include <algorithm>
#include <functional>

#include <iostream>
using namespace std;

namespace grammars {
    void Grammar::remove_barren_characters() {
        if(!check_if_context_free()) {
            throw std::logic_error("can't apply remove_barren_characters: grammar is not context-free");
        }

        set<Rule*> unparsed;

        for(auto &r : rules) {
            unparsed.insert(&r);
        }

        set<Symbol> new_nt = { };
        int prev_size = -1, cur_size = 0;

        auto &all_t = terminals;

        while(prev_size != cur_size) {
            std::erase_if(unparsed, [&all_t ,&new_nt](Rule* r) {
                bool is_barren = false;
                for(const auto &s : r->getRight()) {
                    if(all_t.count(s) == 0 && new_nt.count(s) == 0) {
                        is_barren = true;
                    }
                }

                if(!is_barren) {
                    new_nt.insert(r->frontLeft());

                    return true;
                } else {
                    return false;
                }
            });
            
            prev_size = cur_size;
            cur_size = new_nt.size();
        }


        if(new_nt.count(start) == 0) {
            rules = { };
            non_teminals = { start };
            return;
        }

        std::erase_if(rules, [&unparsed](Rule &r) {
            if(unparsed.count(&r) != 0) {
                return true;
            }

            return false;
        });

        non_teminals = std::set<grammars::Symbol>(new_nt.begin(), new_nt.end());
        inf_valid = GR_BIT(CONT_FREE) | GR_BIT(TYPE_0);
    }

    void Grammar::remove_unreachable_characters() {
        if(!check_if_context_free()) {
            throw std::logic_error("can't apply remove_unreachable_characters: grammar is not context-free");
        }

        set<Rule*> unparsed;

        for(auto &r : rules) {
            unparsed.insert(&r);
        }

        set<Symbol> new_nt = { start };
        set<Symbol> new_t;
        int prev_size = 0, cur_size = 1;

        auto &all_nt = non_teminals;

        while(prev_size != cur_size) {
            std::erase_if(unparsed, [&all_nt, &new_nt, &new_t](Rule *r) {
                if(new_nt.count(r->frontLeft())) {
                    for(const auto &s : r->getRight()) {
                        if(all_nt.count(s) != 0) {
                            new_nt.insert(s);
                        } else {
                            new_t.insert(s);
                        }
                    }

                    return true;
                } else {
                    return false;
                }
            });
            
            prev_size = cur_size;
            cur_size = new_nt.size() + new_t.size();
        }

        std::erase_if(rules, [&unparsed](Rule &r) {
            if(unparsed.count(&r) != 0) {
                return true;
            }

            return false;
        });

        non_teminals = std::set<grammars::Symbol>(new_nt.begin(), new_nt.end());
        terminals = std::set<grammars::Symbol>(new_t.begin(), new_t.end());
        inf_valid = GR_BIT(CONT_FREE) | GR_BIT(TYPE_0);
    }

    void Grammar::reduce_context_free() {
        // cout << *this << endl;
        remove_barren_characters();
        // cout << "barren_deleted" << endl;
        remove_unreachable_characters();
        // cout << "unreachable removed" << endl;
    }
    
    
    void Grammar::make_noncontracting() {
        if(!check_if_context_free()) {
            throw std::logic_error("can't apply make_noncontracting: grammar is not context-free");
        }

        vector<Rule> new_rules;
        set<Symbol> prod_eps;

        int cur_size = 0, prev_size = -1;
        while(cur_size != prev_size) {
            for(const auto &r : rules) {
                if(r.lenRight() == 0 ||
                    (r.lenRight() == 1 && prod_eps.count(r.backRight()))
                ) {
                    prod_eps.insert(r.frontLeft());
                }
            }

            prev_size = cur_size;
            cur_size = prod_eps.size();
        }
        
        if(prod_eps.count(start)) {
            Symbol new_s(start.name() + "'");
            int j = 0;
            while(terminals.count(new_s) || non_teminals.count(new_s)) {
                new_s = start.name() + "{" +to_string(j) + "}";
            }

            non_teminals.insert(new_s);
            rules.push_back(Rule({ new_s }, { start })); // add rule S' -> S
            start = new_s;
        }

        for(auto &r : rules) {
            if(r.lenRight() == 0) {
                continue;
            }
            
            int n = 0;
            bool other_syms = false;
            for(const auto & s : r.getRight()) {
                if(prod_eps.count(s)) {
                    n++;
                } else {
                    other_syms = true;
                }
            }

            if(n == 0) {
                new_rules.push_back(move(r));
                continue;
            }

            uint64_t num_of_new_rules = 1 << n;
            Symbol lsym = r.frontLeft();
            
            int start_pos = other_syms ? 0 : 1;
            int offset = new_rules.size() - start_pos;
            

            for(uint64_t i = start_pos; i < num_of_new_rules; i++) {
                new_rules.push_back(Rule({lsym}, {}));
            }

            uint64_t cur_mask = num_of_new_rules >> 1;
            for(const auto & s : r.getRight()) {
                if(prod_eps.count(s)) {
                    for(uint64_t i = start_pos; i < num_of_new_rules; i++) {
                        if(i & cur_mask) {
                            new_rules[i + offset].pushBackRight(s);
                        }
                    }
                    
                    cur_mask = cur_mask >> 1;
                } else {
                    for(uint64_t i = start_pos; i < num_of_new_rules; i++) {
                        new_rules[i + offset].pushBackRight(s);
                    }
                }
            }

            // for(uint64_t i = start_pos; i < num_of_new_rules; i++) {
            //     cout << "added " << new_rules[i + offset] << endl;
            // }
        }

        rules = new_rules;
        
        // cout << "made" << endl;
        inf_valid = GR_BIT(CONT_FREE) | GR_BIT(TYPE_0);
        reduce_context_free();
    }
}