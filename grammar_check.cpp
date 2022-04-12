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
        const int32_t current_bit =  GR_BIT(TYPE_0);
        
        if(inf_valid & current_bit) {
            return info & current_bit; // always true
        }

        return false;
    };

    bool Grammar::check_if_noncontracting() {
        const int32_t current_bit =  GR_BIT(NONCONTR);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        inf_valid |= current_bit;

        for(const auto &e : rules) {
            if(e.getLeft().size() > e.getRight().size()) {
                if(e.getLeft().size() == 1 && e.getLeft().front() == start && e.getRight().empty()) {
                    // S -> eps
                } else {
                    info &= ~current_bit;
                    return false;
                }
            }
        }

        info |= current_bit;
        return true;
    };

    bool Grammar::check_if_context_free() {
        const int32_t current_bit =  GR_BIT(TYPE_0);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        return false;
    };

    bool Grammar::check_if_regular() {
        const int32_t current_bit =  GR_BIT(TYPE_0);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        return false;
    };

    bool Grammar::check_if_regular_left() {
        const int32_t current_bit =  GR_BIT(TYPE_0);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        return false;
    };

    bool Grammar::check_if_regular_right() {
        const int32_t current_bit =  GR_BIT(TYPE_0);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        return false;
    };

    bool Grammar::check_if_automatic() {
        const int32_t current_bit =  GR_BIT(TYPE_0);

        if(inf_valid & current_bit) {
            return info & current_bit;
        }

        return true;
    };
}