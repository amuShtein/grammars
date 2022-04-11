#include "grammars.h"
#include <sstream>
#include <exception>
#include <algorithm>

namespace grammars {

    static vector<Symbol> parse_to_vector (
        const string &s,
        char sym_delim
    )
    {   
        vector<Symbol> ret;
        int delim_len = 1; // 1 = length of char
        auto start = 0U;
        auto end = s.find(sym_delim);
        
        while(end != string::npos) {
            Symbol cur(s.substr(start, end - start));
            start = end + delim_len;
            ret.push_back(cur);

            auto end = s.find(sym_delim, start);
        }

        return ret;
    }

    Rule::Rule(string s,
        char sym_delim, 
        const string &arrow
        )
    {   
        s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
        string l, r;
        auto mid = s.find(arrow);
        if(mid == std::string::npos) {
            throw std::logic_error("cannon find arrow " + arrow + " in " + s);
        } else {
            l = s.substr(0, mid);
            r = s.substr(mid + arrow.length());
        }

        left = parse_to_vector(l, sym_delim);
        right = parse_to_vector(r, sym_delim);
    }

    bool Rule::verify(const set<Symbol> &terminals, 
        const set<Symbol> &non_terminals, 
        const Symbol &eps) const 
    {
        for(auto &e: left) {
            if(terminals.count(e) == 0 && non_terminals.count(e) == 0 && !(e == eps)) {
                return false;
            }
        }

        for(auto &e: right) {
            if(terminals.count(e) == 0 && non_terminals.count(e) == 0 && !(e == eps)) {
                return false;
            }
        }
        return true;
    }

    const vector<Symbol> & Rule::getLeft() const {
        return left;
    }

    const vector<Symbol> & Rule::getRight() const {
        return right;
    }

    string Rule::to_string(const string& arrow, char delim, bool use_delim) const {
        using std::stringstream;
        
        stringstream ss;
        auto lit = left.begin();
        if(lit != left.end()) {
            ss << lit->name();

            for(lit++; lit != left.end(); lit++) {
                if(use_delim) {
                    ss << delim;
                }
                ss << lit->name();
            }
        };

        ss << " " << arrow << " ";

        auto rit = right.begin();
        if(rit != right.end()) {
            ss << rit->name();

            for(rit++; rit != right.end(); rit++) {
                if(use_delim) {
                    ss << delim;
                }
                ss << rit->name();
            }
        };

        return ss.str();
    }
    string Rule::to_string(const string& arrow, bool use_delim) const {
        return to_string(arrow, default_delim, use_delim);
    }
    string Rule::to_string(bool use_delim) const {
        return to_string(default_arrow, default_delim, use_delim);
    }

    std::ostream &operator<<(std::ostream &out, const Rule &r) {
        return out << r.to_string();
    }
}