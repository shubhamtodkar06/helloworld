#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

bool isOperator(char c){
    return (c == '+' || c == '-' || c == '/' || c == '*' || c == '^');
}

int precedence(char c){
    if (c == '^'){
        return 3;
    }
    else if (c == '*' || c == '/'){
        return 2;
    }
    else if (c == '+' || c == '-'){
        return 1;
    }

    return -1;
}

string infixToPrefix(const string& infix){
    stack<char> s;
    string prefix;

    // Reverse the infix expression
    string reversedInfix = infix;
    reverse(reversedInfix.begin(), reversedInfix.end());

    for (int i = 0; i < reversedInfix.length(); i++){
        if ((reversedInfix[i] >= 'a' && reversedInfix[i] <= 'z') || (reversedInfix[i] >= 'A' && reversedInfix[i] <= 'Z')){
            prefix += reversedInfix[i]; // Operand, append to prefix
        }

        else if (reversedInfix[i] == ')'){
            s.push(reversedInfix[i]); // Closing parenthesis, push to stack
        }

        else if (reversedInfix[i] == '('){
            while ((!s.empty()) && s.top() != ')'){
                prefix += s.top(); // Pop and append operators until ')'
                s.pop();
            }

            if (!s.empty() && s.top() == ')'){
                s.pop(); // Pop the ')' from the stack
            }
        }

        else if (isOperator(reversedInfix[i])){
            if (s.empty() || s.top() == ')'){
                s.push(reversedInfix[i]); // Push operator if stack is empty or top is ')'
            }
            else{
                if (precedence(s.top()) == precedence(reversedInfix[i]) && reversedInfix[i] == '^'){
                    s.push(reversedInfix[i]); // Push '^' if same precedence and operator is '^'
                }
                else {
                    while (!s.empty() && precedence(reversedInfix[i]) <= precedence(s.top())){
                        prefix += s.top(); // Pop and append operators until higher or equal precedence
                        s.pop();
                    }
                    s.push(reversedInfix[i]); // Push the current operator
                }
            }
        }
    }

    while (!s.empty()){
        prefix += s.top(); // Pop and append any remaining operators
        s.pop();
    }

    // Reverse the final prefix expression
    reverse(prefix.begin(), prefix.end());

    return prefix;
}

int main() {
    string infix, prefix;
    cout << "Enter an Infix Expression: ";
    getline(cin, infix);  // Use getline to capture the entire line

    prefix = infixToPrefix(infix);

    cout << "Prefix Expression: " << prefix << endl;

    return 0;
}
