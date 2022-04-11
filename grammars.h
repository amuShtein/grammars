#ifndef GRAMMARS_H__
#define GRAMMARS_H__
#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <istream>

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
        Rule(vector<Symbol> l, vector<Symbol> r) : left(l), right(r) { };
        Rule(string s, char sym_delim = '.', const string &arrow = "->");
        
        bool verify(const set<Symbol> &terminals, 
            const set<Symbol> &non_terminals, 
            const Symbol &eps) const;
        
        Rule() { };

        const vector<Symbol>& getLeft() const;
        const vector<Symbol>& getRight() const;

        string getDefaultArrow() const;
        char getDefaultDelim() const;

        string to_string(bool use_delim = false) const;
        string to_string(const string& arrow, bool use_delim = false) const;
        string to_string(const string& arrow, char delim, bool use_delim = false) const;
        friend std::ostream &operator<<(std::ostream &out, const Rule &r);
    };

    class Grammar {
        Symbol eps;
        set<Symbol> terminals, non_teminals;
        vector<Rule> rules;
        Symbol start;
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
    };
}

#endif