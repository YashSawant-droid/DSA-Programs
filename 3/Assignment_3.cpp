#include <iostream>
#include <cctype>
#include <cmath>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class Stack {
private:
    Node* top;
public:
    Stack() : top(nullptr) {}

    bool isEmpty() {
        return top == nullptr;
    }

    void push(int value) {
        Node* newNode = new Node();
        if (!newNode) {
            cout << "Memory not available" << endl;
            return;
        }
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            return -1;
        }
        Node* temp = top;
        int poppedValue = temp->data;
        top = top->next;
        delete temp;
        return poppedValue;
    }

    int peek() {
        if (!isEmpty()) {
            return top->data;
        }
        return -1;
    }
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

string infixToPostfix(string infix) {
    Stack stack;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += (char)stack.pop();
            }
            stack.pop();
        } else if (isOperator(ch)) {
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
                postfix += (char)stack.pop();
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) {
        postfix += (char)stack.pop();
    }

    return postfix;
}

int evaluatePostfix(string postfix) {
    Stack stack;

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        if (isdigit(ch)) {
            stack.push(ch - '0');
        } else if (isOperator(ch)) {
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            int result = 0;

            switch (ch) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                case '^': result = pow(operand1, operand2); break;
            }
            stack.push(result);
        }
    }

    return stack.pop();
}

string reverseString(string str) {
    int len = str.length();
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}

string infixToPrefix(string infix) {
    infix = reverseString(infix);

    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }

    string postfix = infixToPostfix(infix);
    string prefix = reverseString(postfix);

    return prefix;
}

int main() {
    string infix;
    cout << "Enter Infix Expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;

    string prefix = infixToPrefix(infix);
    cout << "Prefix Expression: " << prefix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Evaluation of Postfix: " << result << endl;

    return 0;
}
