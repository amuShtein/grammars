#include "grammars.h"
#include "grammar_types.h"

namespace grammars {
    bool Grammar::check_if_type_zero() {
        const int32_t current_bit =  GR_BIT(TYPE_0);

        if(inf_valid & current_bit) {
            return info & current_bit; // always true
        }

        info |= current_bit;
        inf_valid |= current_bit;

        return true;
    };

    bool Grammar::check_if_context_sensitive() {
        const int32_t current_bit =  GR_BIT(CONT_SENS);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        inf_valid |= current_bit;
        if(!check_if_noncontracting()) {
            info &= ~current_bit;
            return false;
        }

        bool good_rule;
        for(const auto &rule : rules) {
            good_rule = false;
            auto it_l = rule.getLeft().begin();
            auto end_l = rule.getLeft().end();
            
            auto rit_l = rule.getLeft().rbegin();
            auto rend_l = rule.getLeft().rend();
            
            auto it_r = rule.getRight().begin();
            auto end_r = rule.getRight().end();

            auto rit_r = rule.getRight().rbegin();
            auto rend_r = rule.getRight().rend();

            for(; it_l != end_l && it_r != end_r && *it_l == *it_r; it_l++, it_r++) { };
            for(; rit_l != rend_l && rit_r != rend_r && *rit_l == *rit_r; rit_l++, rit_r++) { };

            if(rit_l != rend_l) {
                rit_l++;
            }

            auto res_it = rit_l.base();
            
            if(it_l != end_l) {
                it_l++;
            }

            for(; res_it < it_l; res_it++) {
                if(non_teminals.count(*res_it) != 0) {
                    good_rule = true;
                    break;
                }
            }

            if(!good_rule) {
                info &= ~current_bit;
                return false;
            }
        }


        info |= current_bit;
        return true;
    };

    bool Grammar::check_if_noncontracting() {
        const int32_t current_bit =  GR_BIT(NONCONTR);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        inf_valid |= current_bit;

        bool eps_rule = false;
        bool s_in_right = false;

        for(const auto &e : rules) {
            if(e.getLeft().size() > e.getRight().size()) {
                if(e.getLeft().size() == 1 && e.getLeft().front() == start && e.getRight().empty()) {
                    // S -> eps
                    eps_rule = true;
                } else {
                    info &= ~current_bit;
                    return false;
                }
            }

            for(const auto &r_sym : e.getRight()) {
                if(r_sym == start) {
                    s_in_right = true;
                }
            }
        }

        if(eps_rule && s_in_right) {
            info &= ~current_bit;
            return false;
        }

        info |= current_bit;
        return true;
    };

    bool Grammar::check_if_context_free() {
        const int32_t current_bit =  GR_BIT(CONT_FREE);
        
        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        inf_valid |= current_bit;
        for(const auto &rule : rules) {
            if(rule.getLeft().size() == 1 && non_teminals.count(rule.getLeft().front())) {
                // rule allowed
            } else {
                info &= ~current_bit;
                return false;
            }
        }

        info |= current_bit;
        return true;
    };

    bool Grammar::check_if_regular_right() {
        const int32_t current_bit =  GR_BIT(REGULAR_RIGHT);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        inf_valid |= current_bit;
        if(!check_if_context_free()) {
            info &= ~current_bit;
            return false;
        };

        for(const auto &rule : rules) {
            int len = rule.lenRight();

            for(int i = 0; i < len - 1; i++) {
                if(non_teminals.count(rule.symRight(i))) {
                    // bad rule
                    info &= ~current_bit;
                    return false;
                }
            }
        }

        info |= current_bit;
        return true;
    };

    bool Grammar::check_if_regular_left() {
        const int32_t current_bit =  GR_BIT(REGULAR_LEFT);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        inf_valid |= current_bit;
        if(!check_if_context_free()) {
            info &= ~current_bit;
            return false;
        };

        for(const auto &rule : rules) {
            int len = rule.lenRight();

            for(int i = len - 1; i > 0; i--) {
                if(non_teminals.count(rule.symRight(i))) {
                    // bad rule
                    info &= ~current_bit;
                    return false;
                }
            }
        }

        info |= current_bit;
        return true;
    };

    bool Grammar::check_if_regular() {
        const int32_t current_bit =  GR_BIT(REGULAR);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        inf_valid |= current_bit;
        if(check_if_regular_left() || check_if_regular_right()) {
            info |= current_bit;
            return true;
        }

        info &= ~current_bit;
        return false;
    };

    bool Grammar::check_if_automatic() {
        const int32_t current_bit =  GR_BIT(AUTOMATIC);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }
        
        inf_valid |= current_bit;
        if(check_if_regular_right()) {
            for(const auto &rule : rules) {
                int r_len = rule.lenRight();
                bool ends_by_non_term = r_len == 0 ? true : non_teminals.count(rule.backRight());
                
                if(r_len == 0 || // A -> eps
                    r_len == 1 && !ends_by_non_term || // A -> a
                    r_len == 2 && ends_by_non_term  // A -> aA
                ) {
                    // good rule
                } else {
                    info &= ~current_bit;
                    return false;
                }
            }
        } else if(check_if_regular_left()) {
            for(const auto &rule : rules) {
                int r_len = rule.lenRight();
                bool starts_by_non_term = r_len == 0 ? true : non_teminals.count(rule.frontRight());
                
                if(r_len == 0 || // A -> eps
                    r_len == 1 && !starts_by_non_term || // A -> a
                    r_len == 2 && starts_by_non_term  // A -> Aa
                ) {
                    // good rule
                } else {
                    info &= ~current_bit;
                    return false;
                }
            }
        } else {
            info &= ~current_bit;
            return false;
        }

        info |= current_bit;
        return true;
    };
}