#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <string>
#include <map>
#include <set>

using namespace std;

vector<string> spec = { "+", "-", "*", "/", "=", "<>", "<", ">", "<=", ">=", "?", ":", "(", ")", ",", ";" , ":=", "\n" };
vector<string> lex() {
    vector<string> s;
    string line;
    while (getline(cin, line)) {
        if (line == "stop") {
            break;
        }
        string s1 = ""; //строка из обычных букв/цифр
        int is_previous1 = 0; //является ли пред символ <
        int is_previous2 = 0; //является ли пред символ >
        int is_previous3 = 0; //является ли пред символ :
        for (char c : line) {
            string cur(1, c); //превратили char в string
            auto it = find(spec.begin(), spec.end(), cur);
            if (it != spec.end()) {  //если символ спец
                if (s1 != "") {
                    s.push_back(s1);
                    s1 = "";
                }
                if (is_previous1 + is_previous2 + is_previous3 > 0) {
                    //случай когда <

                    if ((is_previous1 == 1) && (cur == ">")) {
                        s.push_back("<>");
                        is_previous1 = 0;
                    }
                    if ((is_previous1 == 1) && (cur == "=")) {
                        s.push_back("<=");
                        is_previous1 = 0;
                    }
                    if ((is_previous1 == 1) && (cur != "=") && (cur != ">")) {
                        s.push_back("<");
                        is_previous1 = 0;
                    }

                    //случай когда >


                    if ((is_previous2 == 1) && (cur == "=")) {
                        s.push_back(">=");
                        is_previous2 = 0;
                    }
                    if ((is_previous2 == 1) && (cur != "=")) {
                        s.push_back(">");
                        is_previous2 = 0;
                    }

                    //случай когда :
                    if ((is_previous3 == 1) && (cur == "=")) {
                        s.push_back(":=");
                        is_previous3 = 0;
                    }
                    if ((is_previous3 == 1) && (cur != "=")) {
                        s.push_back(":");
                        is_previous3 = 0;
                    }
                }
                else {
                    if (c == '<') {
                        is_previous1 = 1;
                    }
                    else {
                        if (c == '>') {
                            is_previous2 = 1;
                        }
                        else {
                            if (c == ':') {
                                is_previous3 = 1;
                            }
                            else {
                                s.push_back(cur);
                            }
                        }
                    }
                }

            } // а если не спец
            else {
                if (is_previous1 == 1) {
                    s.push_back("<");
                }
                is_previous1 = 0;

                if (is_previous2 == 1) {
                    s.push_back(">");
                }
                is_previous2 = 0;

                if (is_previous3 == 1) {
                    s.push_back(":");
                }
                is_previous3 = 0;

                if (c == ' ') {
                    if (s1 != "") {
                        s.push_back(s1);
                        s1 = "";
                    }

                }
                else {
                    s1 += c;
                }
            }
        }
        if (s1 != "") { //вдруг что-то осталось
            s.push_back(s1);
        }

    }
    s.push_back("куку");
    return s;

}


//<program> :: = <function> <program>
//<function> :: = <ident> (<formal - args - list>) := <expr> ;
//<formal - args - list> :: = <ident - list> |
// <ident-list> ::= <ident> <ident-list-tail>
// <ident - list - tail> :: = , <ident> <ident - list - tail> |
//<expr> :: = <comparison - expr> <expr - tail>
// <expr - tail> :: = ? <comparison - expr> : <expr> | 
//<comparison - expr> :: = <arith - expr> <comparison - expr - tail>
//<comparison - expr - tail> :: = <comparison - op> <arith - expr> | 
// <comparison_op> :: = = | <> | < | > | <= | >= 
//<arith - expr> :: = <term> <arith - expr - tail>
//<arith - expr - tail> :: = +<term> <arith - expr - tail> | -<term> <arith - expr - tail> | 
//<term> :: = <factor> <term - tail>
//<term - tail> :: = *<factor> <term - tail> | / <factor> <term - tail> | 
//<factor> :: = <number> | <ident> <factor - tail> | (<expr>) | -<factor>
// <factor - tail> :: = (<actual_args_list>) | 
//<actual_args_list> :: = <expr - list> |
//<expr - list> :: = <expr> <expr - list - tail>
//<expr - list - tail> ::=, <expr> <expr - list - tail> |



string peek(vector<string>& lexems, int len);
void next(vector<string>& lexems, int len);
int is_ident(string s);
bool isNumber(string& str);
void program(vector<string>& lexems, int len);
void function1(vector<string>& lexems, int len);
set<string> formal_args_list(vector<string>& lexems, int len, set<string>& set1);
set<string> ident_list(vector<string>& lexems, int len, set<string>& set1);
void expr(vector<string>& lexems, int len, string name_func, set<string>& set1);
set<string> ident_list_tail(vector<string>& lexems, int len, set<string>& set1);
void expr_tail(vector<string>& lexems, int len, string name_func, set<string>& set1);
void comparison_expr(vector<string>& lexems, int len, string name_func, set<string>& set1);
void comparison_expr_tail(vector<string>& lexems, int len, string name_func, set<string>& set1);
void comparison_op(vector<string>& lexems, int len);
void arith_expr(vector<string>& lexems, int len, string name_func, set<string>& set1);
void arith_expr_tail(vector<string>& lexems, int len, string name_func, set<string>& set1);
void term(vector<string>& lexems, int len, string name_func, set<string>& set1);
void term_tail(vector<string>& lexems, int len, string name_func, set<string>& set1);
void factor(vector<string>& lexems, int len, string name_func, set<string>& set1);
int factor_tail(vector<string>& lexems, int len, string name_func, string name_func2, int& count_args, set<string>& set1);
int actual_args_list(vector<string>& lexems, int len, string name_func, int& count_args, set<string>& set1);
int expr_list(vector<string>& lexems, int len, string name_func, int& count_args, set<string>& set1);
int expr_list_tail(vector<string>& lexems, int len, string name_func, int& count_args, set<string>& set1);



int i = 0;
int is_error = 0;
int count1 = 0;
map<string, pair<int, vector<int>>> map1;
map<string, pair<int, int>> amount_args;
set<string> diff_func;
string peek(vector<string>& lexems, int len) {
    return lexems[i];
}
void next(vector<string>& lexems, int len) {
    if (i + 1 < len) {
        i += 1;
    }
}
int is_ident(string s) {
    int is_ident = 1;
    if (!(('a' <= s[0] && s[0] <= 'z') || ('A' <= s[0] && s[0] <= 'Z'))) {
        is_ident = 0;
    }
    for (char c : s) {
        if (!(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'))) {
            is_ident = 0;
        }
    }
    return is_ident;

}

//<program> :: = <function> <program> | 
void program(vector<string>& lexems, int len) {
    function1(lexems, len);
    if (peek(lexems, len) != "куку") {
        program(lexems, len);
    }
}

//<function> :: = <ident> (<formal - args - list>) := <expr> ;
void function1(vector<string>& lexems, int len) {
    string name_func = peek(lexems, len);
    if (is_ident(peek(lexems, len)) == 0) {
        is_error = 1;
    }
    next(lexems, len);
    if (peek(lexems, len) != "(") {
        is_error = 1;
    }
    next(lexems, len);
    int count_args = 0;
    set<string> set1;
    if (is_ident(peek(lexems, len))) {
        set1 = formal_args_list(lexems, len, set1);
        count_args = set1.size();
    }
    if (peek(lexems, len) != ")") {
        is_error = 1;
    }
    next(lexems, len);
    if (peek(lexems, len) != ":=") {
        is_error = 1;
    }
    next(lexems, len);
    diff_func.insert(name_func);
    if (is_ident(name_func)) {
        auto it = map1.find(name_func);   //добавляем в словарь
        if (it == map1.end()) {
            vector<int> a;
            pair<int, vector<int>> p = make_pair(count1, a);
            amount_args[name_func] = make_pair(count1, count_args);
            map1[name_func] = p;
            count1++;
        }
        else {
            if (count_args != amount_args[name_func].second) {
                is_error = 1;
            }
        }
        expr(lexems, len, name_func, set1);
    }
    if (peek(lexems, len) != ";") {
        is_error = 1;
    }
    next(lexems, len);
}



//<formal - args - list> :: = <ident - list> |
set<string> formal_args_list(vector<string>& lexems, int len, set<string>& set1) {
    if (is_ident(peek(lexems, len)) == 1) {
        set1 = ident_list(lexems, len, set1);
    }
    return set1;

}

// <ident-list> ::= <ident> <ident-list-tail>
set<string> ident_list(vector<string>& lexems, int len, set<string>& set1) {
    if (is_ident(peek(lexems, len)) == 0) {
        is_error = 1;
    }
    else {
        set1.insert(peek(lexems, len));
        next(lexems, len);
    }
    set1 = ident_list_tail(lexems, len, set1);
    return set1;
}

// <ident - list - tail> :: = , <ident> <ident - list - tail> |
set<string> ident_list_tail(vector<string>& lexems, int len, set<string>& set1) {
    string s = peek(lexems, len);
    if (s == ",") {
        next(lexems, len);
        if (is_ident(peek(lexems, len)) == 0) {
            is_error = 1;
        }
        else {
            set1.insert(peek(lexems, len));
            next(lexems, len);
        }
        set1 = ident_list_tail(lexems, len, set1);
    }
    return set1;
}

//<expr> :: = <comparison - expr> <expr - tail> | 
void expr(vector<string>& lexems, int len, string name_func, set<string>& set1) {
    string s = peek(lexems, len);
    if ((isNumber(s) == 1) || (is_ident(s) == 1) || (s == "(") || (s == "-")) {
        comparison_expr(lexems, len, name_func, set1);
        expr_tail(lexems, len, name_func, set1);
    }
}

// <expr - tail> :: = ? <comparison - expr> : <expr> |
void expr_tail(vector<string>& lexems, int len, string name_func, set<string>& set1) {
    if (peek(lexems, len) == "?") {
        next(lexems, len);
        comparison_expr(lexems, len, name_func, set1);
        if (peek(lexems, len) != ":") {
            is_error = 1;
        }
        next(lexems, len);
        expr(lexems, len, name_func, set1);
    }
}




//<comparison - expr> :: = <arith - expr> <comparison - expr - tail>
void comparison_expr(vector<string>& lexems, int len, string name_func, set<string>& set1) {
    arith_expr(lexems, len, name_func, set1);
    comparison_expr_tail(lexems, len, name_func, set1);
}

//<comparison - expr - tail> :: = <comparison - op> <arith - expr> | 
void comparison_expr_tail(vector<string>& lexems, int len, string name_func, set<string>& set1) {
    string s = peek(lexems, len);
    if ((s == "=") || (s == "<>") || (s == "<") || (s == ">") || (s == "<=") || (s == ">=")) {
        comparison_op(lexems, len);
        next(lexems, len);
        arith_expr(lexems, len, name_func, set1);
    }
}

// <comparison_op> :: = = | <> | < | > | <= | >= 
void comparison_op(vector<string>& lexems, int len) {
    string s = peek(lexems, len);
    //if (not((s == "|") || (s == "<>") || (s == "<") || (s == ">") || (s == "<=") || (s == ">="))) {
        //is_error = 1;
    //}
}

//<arith - expr> :: = <term> <arith - expr - tail>
void arith_expr(vector<string>& lexems, int len, string name_func, set<string>& set1) {
    term(lexems, len, name_func, set1);
    arith_expr_tail(lexems, len, name_func, set1);
}

//<arith - expr - tail> :: = +<term> <arith - expr - tail> | -<term> <arith - expr - tail> | 
void arith_expr_tail(vector<string>& lexems, int len, string name_func, set<string>& set1) {
    string s = peek(lexems, len);
    if (s == "+") {
        next(lexems, len);
        term(lexems, len, name_func, set1);
        arith_expr_tail(lexems, len, name_func, set1);
    }
    else {
        if (s == "-") {
            next(lexems, len);
            term(lexems, len, name_func, set1);
            arith_expr_tail(lexems, len, name_func, set1);
        }
    }
}
//<term> :: = <factor> <term - tail>
void term(vector<string>& lexems, int len, string name_func, set<string>& set1) {
    factor(lexems, len, name_func, set1);
    term_tail(lexems, len, name_func, set1);
}

//<term - tail> :: = *<factor> <term - tail> | / <factor> <term - tail> | 
void term_tail(vector<string>& lexems, int len, string name_func, set<string>& set1) {
    string s = peek(lexems, len);
    if (s == "*") {
        next(lexems, len);
        factor(lexems, len, name_func, set1);
        term_tail(lexems, len, name_func, set1);
    }
    else {
        if (s == "/") {
            next(lexems, len);
            factor(lexems, len, name_func, set1);
            term_tail(lexems, len, name_func, set1);
        }
    }
}
bool isNumber(string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}


//<factor> :: = <number> | <ident> <factor - tail> | (<expr>) | -<factor>
void factor(vector<string>& lexems, int len, string name_func, set<string>& set1) {
    string s = peek(lexems, len);
    //if ("0" <= s && s <= "9") {
        //if (i + 1 < len && (lexems[i + 1] == "(")) {
           // next(lexems, len);
            //factor_tail(lexems, len, name_func);
        //}
    //}
    if (isNumber(s)) {
        next(lexems, len);
    }
    if (!(isNumber(s))) {
        if (s == "(") {
            next(lexems, len);
            expr(lexems, len, name_func, set1);
            if (peek(lexems, len) != ")") {
                is_error = 1;
            }
            next(lexems, len);

        }
        else {
            if (s == "-") {
                next(lexems, len);
                factor(lexems, len, name_func, set1);
            }
            else {
                string name_func2 = peek(lexems, len);
                int count_args = 0;
                if (is_ident(peek(lexems, len)) == 0) {
                    is_error = 1;
                }
                next(lexems, len);
                if (peek(lexems, len) == "(") {
                    if (is_ident(name_func2)) {
                        count_args = factor_tail(lexems, len, name_func, name_func2, count_args, set1);
                        auto it = map1.find(name_func2);
                        if (it == map1.end()) {
                            vector<int> a;
                            pair<int, vector<int>> p = make_pair(count1, a);
                            amount_args[name_func2] = make_pair(count1, count_args);
                            map1[name_func2] = p;
                            count1++;
                        }
                        else {
                            if (count_args != amount_args[name_func2].second) {
                                is_error = 1;
                            }
                        }
                        map1[name_func].second.push_back(map1[name_func2].first);

                    }
                }
                else {
                    if (set1.find(name_func2) == set1.end()) {
                        is_error = 1;
                    }
                }
            }
        }
    }

}
// <factor - tail> :: = (<actual_args_list>) | 
int factor_tail(vector<string>& lexems, int len, string name_func, string name_func2, int& count_args, set<string>& set1) {
    if (peek(lexems, len) == "(") {
        next(lexems, len);
        count_args = actual_args_list(lexems, len, name_func, count_args, set1);
        if (peek(lexems, len) != ")") {
            is_error = 1;
        }
        next(lexems, len);
    }
    else {
        if (set1.find(name_func2) == set1.end()) {
            is_error = 1;
        }
    }
    return count_args;
}

//<actual_args_list> :: = <expr - list> |
int actual_args_list(vector<string>& lexems, int len, string name_func, int& count_args, set<string>& set1) {
    string s = peek(lexems, len);
    if (isNumber(s) || s == "-" || s == "(" || is_ident(s)) {
        count_args = expr_list(lexems, len, name_func, count_args, set1);
    }
    return count_args;
}


//<expr - list> :: = <expr> <expr - list - tail>
int expr_list(vector<string>& lexems, int len, string name_func, int& count_args, set<string>& set1) {
    string s = peek(lexems, len);
    expr(lexems, len, name_func, set1);
    count_args++;
    count_args = expr_list_tail(lexems, len, name_func, count_args, set1);
    return count_args;
}

//<expr - list - tail> ::=, <expr> <expr - list - tail> |
int expr_list_tail(vector<string>& lexems, int len, string name_func, int& count_args, set<string>& set1) {
    if (peek(lexems, len) == ",") {
        next(lexems, len);
        expr(lexems, len, name_func, set1);
        count_args++;
        count_args = expr_list_tail(lexems, len, name_func, count_args, set1);
    }
    return count_args;
}

vector<vector<int>> g, gr;
vector<char> used;
vector<int> order, component;

void dfs1(int v) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i)
        if (!used[g[v][i]]) {
            dfs1(g[v][i]);
        }
    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);
    for (int i = 0; i < gr[v].size(); ++i)
        if (!used[gr[v][i]]) {
            dfs2(gr[v][i]);
        }
}


int main() {
    vector<string> lexems = lex();
    int len = lexems.size();
    program(lexems, len);
    if (diff_func.size() != count1) {
        is_error = 1;
    }
    if (is_error == 1) {
        cout << "error" << endl;
    }
    else {
        g.resize(count1);
        gr.resize(count1);
        for (auto it = map1.begin(); it != map1.end(); ++it) {
            int num = it->second.first;
            g[num] = it->second.second;
            for (int v : it->second.second) {
                gr[v].push_back(num);
            }
            if (it->second.second.size() == 0) {
                is_error = 1;
            }
        }
        used.assign(count1, false);
        for (int i = 0; i < count1; ++i) {
            if (!used[i]) {
                dfs1(i);
            }
        }
        used.assign(count1, false);
        int ans = 0;
        for (int i = 0; i < count1; ++i) {
            int v = order[count1 - 1 - i];
            if (!used[v]) {
                dfs2(v);
                ans++;
                component.clear();
            }
        }
        cout << ans << endl;
    }
}