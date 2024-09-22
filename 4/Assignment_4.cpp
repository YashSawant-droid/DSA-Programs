#include <iostream>
#include <string>

using namespace std;

// Forward declaration of BNode
struct BNode;

// Node structure for the stack
struct StackNode {
    BNode* data;
    StackNode* next;
};

// Stack class using singly linked list
class Stack {
private:
    StackNode* top;

public:
    Stack() : top(nullptr) {}

    // Push an element onto the stack
    void push(BNode* node) {
        StackNode* newNode = new StackNode{node, top};
        top = newNode;
    }

    // Pop an element from the stack
    BNode* pop() {
        if (isEmpty()) return nullptr;
        BNode* node = top->data;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        return node;
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Destructor to clean up the stack
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// Binary Tree Node structure
struct BNode {
    char data;
    BNode *left, *right;

    BNode(char val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to check if a character is an operand
bool isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

// Function to check operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix
string infixToPostfix(const string& infix) {
    Stack stack;
    string postfix;

    for (char c : infix) {
        if (isOperand(c)) {
            postfix += c; // If the character is an operand
        } else {
            while (!stack.isEmpty() && precedence(stack.pop()->data) >= precedence(c)) {
                postfix += stack.pop()->data; // Pop from stack if precedence is lower or equal
            }
            stack.push(new BNode(c)); // Push operator to stack
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.pop()->data; // Pop all remaining operators
    }

    return postfix;
}

// Convert infix to prefix
string infixToPrefix(const string& infix) {
    string reversedInfix;
    for (auto it = infix.rbegin(); it != infix.rend(); ++it) {
        if (*it == '(') reversedInfix += ')';
        else if (*it == ')') reversedInfix += '(';
        else reversedInfix += *it;
    }

    string postfix = infixToPostfix(reversedInfix);
    return string(postfix.rbegin(), postfix.rend());
}

// Function to create an expression tree from postfix expression
BNode* constructTreeFromPostfix(const string& postfix) {
    Stack st;
    for (char c : postfix) {
        if (isOperand(c)) {
            st.push(new BNode(c));
        } else { // Operator
            BNode* node = new BNode(c);
            node->right = st.pop(); // Right child first
            node->left = st.pop();  // Left child second
            st.push(node);
        }
    }
    return st.pop(); // The root of the tree
}

// Recursive In-order Traversal
void inOrderRecursive(BNode* root) {
    if (root) {
        inOrderRecursive(root->left);
        cout << root->data << " ";
        inOrderRecursive(root->right);
    }
}

// Recursive Pre-order Traversal
void preOrderRecursive(BNode* root) {
    if (root) {
        cout << root->data << " ";
        preOrderRecursive(root->left);
        preOrderRecursive(root->right);
    }
}

// Recursive Post-order Traversal
void postOrderRecursive(BNode* root) {
    if (root) {
        postOrderRecursive(root->left);
        postOrderRecursive(root->right);
        cout << root->data << " ";
    }
}

// Driver function
int main() {
    string infix;

    cout << "Enter an infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "\nPostfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;

    BNode* rootPostfix = constructTreeFromPostfix(postfix);

    cout << "\nConstructing tree from Postfix: " << postfix << endl;

    cout << "Recursive In-order Traversal: ";
    inOrderRecursive(rootPostfix);
    cout << endl;

    cout << "Recursive Pre-order Traversal: ";
    preOrderRecursive(rootPostfix);
    cout << endl;

    cout << "Recursive Post-order Traversal: ";
    postOrderRecursive(rootPostfix);
    cout << endl;

    return 0;
}
