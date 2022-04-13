#ifndef GRAMMAR_TYPES_H__
#define GRAMMAR_TYPES_H__

#define GR_BIT(x) (1 << (x))

namespace grammars {
    enum GrammarType {
        RECUR_ENUM = 0,
        TYPE_0 = 0,

        CONT_SENS = 1,
        
        NONCONTR = 2,

        CONT_FREE = 3,

        REGULAR = 4,
        REGULAR_LEFT = 5,
        REGULAR_RIGHT = 6,

        AUTOMATIC = 7
    };

    // const char** NAMES;
}

#endif