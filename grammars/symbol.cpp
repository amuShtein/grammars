#include "grammars.h"

namespace grammars {
    bool operator==(const Symbol &s1, const Symbol &s2) {
        return s1.name() == s2.name();
    }

    bool operator<(const Symbol &s1, const Symbol &s2) {
        return s1.name() < s2.name();
    }
}