#include <iostream>
#include <stack>

using namespace std;

bool isOperator(char c){
    return(c == '+' || c == '-' || c == '/' || c == '*' || c == '^');
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

string infixToPostfix(const string& infix){
    stack<char> s;
    string postfix;

    for (int i = 0; i < infix.length(); i++){
        if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z')){
            postfix += infix[i];
        }

        else if (infix[i] == '('){
            s.push(infix[i]);
        }

        else if (infix[i] == ')'){
            while ((!s.empty()) && s.top() != '('){
                postfix += s.top();
                s.pop();
            }

            if(!s.empty() && s.top() == '('){
                s.pop();
            }
        }

        else if (isOperator(infix[i])){
            if (s.empty() || s.top() == '('){
                s.push(infix[i]);
            }
            else{
                if (precedence(s.top()) == precedence(infix[i]) && infix[i] == '^'){
                    s.push(infix[i]);
                }

                else {
                    while (precedence(infix[i]) <= precedence(s.top()) && !s.empty()){
                        postfix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
            }

        }
    }

    while (!s.empty()){
        postfix += s.top();
        s.pop();
    }

    return postfix;
}


int main() {
    string infix, postfix;
    cout << "Enter an Infix Expression: ";
    getline(cin, infix);  // Use getline to capture the entire line

    postfix = infixToPostfix(infix);

    cout << "Postfix Expression: " << postfix << endl;

    return 0;
}

