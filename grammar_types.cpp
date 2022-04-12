#include "grammar_types.h"

namespace grammars {
    const char* NAMES[] = {
        [RECUR_ENUM] = "Recursively enumerable",

        [CONT_SENS] = "Context-sensitive",
        
        [NONCONTR] = "Noncontracting",

        [CONT_FREE] = "Context-free",

        [REGULAR] = "Regular",
        [REGULAR_LEFT] = "Regular-left",
        [REGULAR_RIGHT] = "Regular-right",

        [AUTOMATIC] = "Automatic"
    };
}