#include "SYalgorithm.h"


using namespace std;

Expression *createExp(deque<string> *tokens) {
    Expression *retExp;
    string token = tokens->back();   //get the last token in the deque
    tokens->pop_back();      //remove the last token
    if (isdigit(token[0]) || isdigit(token[1])) {
        double value = stod(token, nullptr);
        retExp = new Num(value);
    } else {
        Expression *r = createExp(tokens);
        Expression *l = createExp(tokens);
        switch (token[0]) {
            case '+':
                retExp = new Plus(l, r);
                break;
            case '-':
                retExp = new Minus(l, r);
                break;
            case '*':
                retExp = new Mul(l, r);
                break;
            case '/':
                retExp = new Div(l, r);
                break;
            default:
                throw "invalid token";
        }
    }
    return retExp;
}

void initPrecedence(map<char, int> &precedence) {
    // initialize the precedence of thr operators (mul before plus and such ..)
    precedence['+'] = 1;
    precedence['-'] = 1;
    precedence['*'] = 2;
    precedence['/'] = 2;
}

Expression *shuntingYard(string exp) {
    map<char, int> precedence;
    initPrecedence(precedence);
    deque<string> numbers;
    stack<char> operators;
    bool foundDig = false;
    exp = fixDoubleMinus(exp);
    for (int i = 0; i < exp.size(); ++i) {
        if (isdigit(exp[i])) {
            if (foundDig) {
                //chain the digits
                numbers.back() += string(1, exp[i]);
            } else {
                // saving number at the queue.
                numbers.push_back(string(1, exp[i]));
                foundDig = true;
            }
            //for fractures like "1.2"
        } else if (exp[i] == '.') {
            numbers.back() += string(1, exp[i]);
        } else if (exp[i] == '(') {
            // saving the '(' on the stack.
            operators.push(exp[i]);
            foundDig = false;
        } else if (exp[i] == ')') {
            // for not getting seg fault.
            if (!operators.empty()) {
                while (operators.top() != '(') {
                    // saving the operators between '(' and ')' at the queue.
                    numbers.push_back(string(1, operators.top()));
                    // move them from the stack.
                    operators.pop();
                }
                // move '(' from the stack and not (!) save it.
                if (operators.top() == '(') {
                    operators.pop();
                }
            }
            foundDig = false;
        } else if ((!foundDig) && exp[i] == ('-')) { //in case NEGATIVE ("-x")
            numbers.push_back(string(1, exp[i]));
            foundDig = true;
        } else {
            // for not getting segmentation fault.
            if (!operators.empty()) {
                // saving operators with higher precedence, before in the stack.
                while (precedence[operators.top()] > precedence[exp[i]]) {
                    numbers.push_back(string(1, operators.top()));
                    operators.pop();
                    if (operators.empty()) {
                        break;
                    }
                }
            }
            operators.push(exp[i]);
            foundDig = false;
        }
    }
    // saving all of the leftovers in the queue.
    while (!operators.empty()) {
        numbers.push_back(string(1, operators.top()));
        operators.pop();
    }
    Expression *retVal = createExp(&numbers);
    return retVal;
}

string fixDoubleMinus(string s) {
    while (s.find("--") != string::npos) {
        int i = s.find("--");
        s.replace(i, 2, "");
    }
    return s;
}
/*
while (s.find("-(-") != string::npos) {
    string buffer;
    int temp;
    int i = s.find("-(-") ;
    temp =i +3 ; //temp is index of X in: "-(-X...."

    while (s[temp] != ')') {
        buffer += s[temp];
        temp++;
    }
    s.replace(i,3,buffer);

}
*/

