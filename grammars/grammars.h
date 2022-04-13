#ifndef GRAMMARS_H__
#define GRAMMARS_H__

#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <istream>

#include "grammar_types.h"

namespace grammars {
    using std::string;
    using std::set;
    using std::vector;
    
    class Symbol {
        string str;
    public:
        Symbol(const string& s = "") : str(s) { };
        Symbol(const char* s) : str(s) { };
        string name() const { return str; }

        friend bool operator==(const Symbol &s1, const Symbol &s2);
        friend bool operator<(const Symbol &s1, const Symbol &s2);
    };

    class Rule {
        vector<Symbol> left, right;
        string default_arrow = "->";
        char default_delim = '.';

    public:
        Rule(const vector<Symbol> &l, const vector<Symbol> &r) : left(l), right(r) { };
        Rule(string s, char sym_delim = '.', const string &arrow = "->", const Symbol &eps = "@");
        
        bool verify(const set<Symbol> &terminals, 
            const set<Symbol> &non_terminals) const;
        
        Rule() { };

        const vector<Symbol>& getLeft() const;
        const vector<Symbol>& getRight() const;

        string getDefaultArrow() const;
        char getDefaultDelim() const;

        int lenLeft() const { return left.size(); };
        int lenRight() const { return right.size(); };
        Symbol symLeft(int i) const { return left[i]; };
        Symbol symRight(int i) const { return right[i]; };

        Symbol frontLeft() const { return left.front(); };
        Symbol backLeft() const { return left.back(); };
        
        Symbol frontRight() const { return right.front(); };
        Symbol backRight() const { return right.back(); };

        string to_string(bool use_delim = false) const;
        string to_string(const string& arrow, bool use_delim = false) const;
        string to_string(const string& arrow, char delim, bool use_delim = false, const Symbol &eps = "@") const;
        friend std::ostream &operator<<(std::ostream &out, const Rule &r);
    };

    class Grammar {
        Symbol eps;
        set<Symbol> terminals, non_teminals;
        vector<Rule> rules;
        Symbol start;

        int32_t info = 0 || GR_BIT(TYPE_0);
        int32_t inf_valid = 0 || GR_BIT(TYPE_0);
    public:
        Grammar(const set<Symbol> &t, 
        const set<Symbol> &nt, 
        const vector<Rule> &r, 
        const Symbol &s, 
        const Symbol &eps_arg = "@");
        
        Grammar() { };

        void setEps(const Symbol &s) { eps = s; }

        Symbol replaceEps(const Symbol &s);
    
        friend std::ostream &operator<<(std::ostream &out, const Grammar &g);

        bool check_if_type_zero();
        bool check_if_context_sensitive();
        bool check_if_noncontracting();
        bool check_if_context_free();
        bool check_if_regular();
        bool check_if_regular_left();
        bool check_if_regular_right();
        bool check_if_automatic();
    };
}

#endif