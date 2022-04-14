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

        set<Symbol> new_nt = { start };
        int prev_size = 0, cur_size = 1;

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

        std::erase_if(rules, [&unparsed](Rule &r) {
            if(unparsed.count(&r) != 0) {
                return true;
            }

            return false;
        });

        non_teminals = std::set<grammars::Symbol>(new_nt.begin(), new_nt.end());
    }

    void Grammar::remove_unreachable_characters() {
        // if(!check_if_context_free()) {
        //     throw std::logic_error("can't apply remove_barren_characters: grammar is not context-free");
        // }

        // set<std::reference_wrapper<const Rule>> unparsed(rules.begin(), rules.end());

        // set<Symbol> new_nt = { start };
        // int prev_size = 0, cur_size = 1;

        // auto &all_nt = non_teminals;

        // while(prev_size != cur_size) {
        //     auto er_it = std::remove_if(unparsed.begin(), unparsed.end(), [&all_nt ,&new_nt](const Rule &r) {
        //         if(new_nt.count(r.frontLeft())) {
        //             for(const auto &s : r.getRight()) {
        //                 if(all_nt.count(s) != 0) {
        //                     new_nt.insert(s);
        //                 }
        //             }

        //             return true;
        //         } else {
        //             return false;
        //         }
        //     });

        //     unparsed.erase(er_it);
            
        //     prev_size = cur_size;
        //     cur_size = new_nt.size();
        // }
    }
}