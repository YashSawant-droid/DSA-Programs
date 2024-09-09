#include <iostream> // Include the standard input-output library
#include <string>   // Include the string library for handling string operations
#include <stack>
#include <cctype>    // Include the cctype library for character classification functions
#include <cmath>     // Include the cmath library for mathematical functions like pow()
#include <algorithm> // Include the algorithm library for functions like reverse
using namespace std;

// Node structure for linked list implementation of stack
struct Node
{
    char data;  // Data stored in the node (a character)
    Node *next; // Pointer to the next node in the linked list
};

// Stack class using linked list
class Stack
{
private:
    Node *top; // Pointer to the top element of the stack

public:
    Stack() : top(nullptr) {} // Constructor to initialize the stack with top set to nullptr

    // Push an element onto the stack
    void push(char x)
    {
        Node *temp = new Node(); // Allocate memory for a new node
        if (!temp)
        { // Check if memory allocation failed
            cout << "Memory not available\n";
            return;
        }
        temp->data = x;   // Set the data of the new node to x
        temp->next = top; // Link the new node to the current top
        top = temp;       // Update the top to point to the new node
    }

    // Pop an element from the stack
    char pop()
    {
        if (isEmpty())
        { // Check if the stack is empty
            cout << "Stack Empty\n";
            return '\0'; // Return null character if the stack is empty
        }
        char x = top->data; // Store the data from the top node
        Node *temp = top;   // Store the current top node in a temporary pointer
        top = top->next;    // Move the top pointer to the next node
        delete temp;        // Delete the old top node
        return x;           // Return the popped data
    }

    // Return the top element of the stack
    char peek()
    {
        if (!isEmpty())       // Check if the stack is not empty
            return top->data; // Return the data from the top node
        else
            return '\0'; // Return null character if the stack is empty
    }

    // Check if the stack is empty
    bool isEmpty()
    {
        return top == nullptr; // Stack is empty if top is nullptr
    }

    // Function to check matching parentheses
    bool isMatchingParenthesis(string expr)
    {
        for (char ch : expr)
        { // Iterate through each character in the expression
            if (ch == '(' || ch == '{' || ch == '[')
            {
                push(ch); // Push opening parentheses onto the stack
            }
            else if (ch == ')' || ch == '}' || ch == ']')
            {
                if (isEmpty())
                { // Check if stack is empty when a closing parenthesis is found
                    cout << "Close parenthesis missing\n";
                    return false; // Return false if no matching opening parenthesis
                }
                char topChar = pop(); // Pop the top element from the stack
                if ((ch == ')' && topChar != '(') ||
                    (ch == '}' && topChar != '{') ||
                    (ch == ']' && topChar != '['))
                {
                    cout << "Open parenthesis missing\n";
                    return false; // Return false if parentheses do not match
                }
            }
        }
        if (!isEmpty())
        { // Check if any unmatched opening parentheses remain
            cout << "Open parenthesis missing\n";
            return false; // Return false if unmatched parentheses exist
        }
        return true; // Return true if all parentheses match correctly
    }
};

// Function to return precedence of operators
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1; // Precedence 1 for '+' and '-'
    if (op == '*' || op == '/')
        return 2; // Precedence 2 for '*' and '/'
    if (op == '$' || op == '^')
        return 3; // Precedence 3 for '$' and '^'
    return 0;     // Return 0 for any other character (usually parentheses)
}

// Function to perform an operation and return output
int applyOp(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b; // Perform addition
    case '-':
        return a - b; // Perform subtraction
    case '*':
        return a * b; // Perform multiplication
    case '/':
        return a / b; // Perform division
    case '$':
    case '^':
        return pow(a, b); // Perform exponentiation
    }
    return 0; // Return 0 if an invalid operator is encountered
}

// Function to convert infix to postfix
string infixToPostfix(string infix)
{
    Stack stack;         // Create an instance of the Stack class
    string postfix = ""; // Initialize an empty string for postfix

    for (char &ch : infix)
    { // Iterate through each character in the infix expression
        if (isalnum(ch))
        {                  // If the character is an operand (alphabet or digit)
            postfix += ch; // Append it to the postfix expression
        }
        else if (ch == '(')
        {
            stack.push(ch); // Push '(' onto the stack
        }
        else if (ch == ')')
        {
            while (!stack.isEmpty() && stack.peek() != '(')
            {
                postfix += stack.pop(); // Pop and add operators until '(' is found
            }
            stack.pop(); // Remove '(' from the stack
        }
        else
        {
            while (!stack.isEmpty() && precedence(ch) <= precedence(stack.peek()))
            {
                postfix += stack.pop(); // Pop and add operators with higher or equal precedence
            }
            stack.push(ch); // Push the current operator onto the stack
        }
    }

    while (!stack.isEmpty())
    {
        postfix += stack.pop(); // Add any remaining operators to the postfix expression
    }

    return postfix; // Return the postfix expression
}

// Function to convert infix to prefix
string infixToPrefix(string infix)
{
    reverse(infix.begin(), infix.end()); // Reverse the infix expression
    for (char &ch : infix)
    { // Iterate through the reversed expression
        if (ch == '(')
            ch = ')'; // Replace '(' with ')'
        else if (ch == ')')
            ch = '('; // Replace ')' with '('
    }

    string prefix = infixToPostfix(infix); // Convert the modified infix to postfix
    reverse(prefix.begin(), prefix.end()); // Reverse the postfix to get the prefix
    return prefix;                         // Return the prefix expression
}

// Function to evaluate postfix expression
int evaluatePostfix(string exp)
{
    stack<int> stack; // Use the standard stack from the library for evaluation
    for (char &ch : exp)
    {
        if (isdigit(ch))
        {                         // If the character is a digit
            stack.push(ch - '0'); // Push the integer value onto the stack
        }
        else
        {
            int val2 = stack.top();
            stack.pop(); // Pop the top two values
            int val1 = stack.top();
            stack.pop();
            stack.push(applyOp(val1, val2, ch)); // Apply the operator and push the result
        }
    }
    return stack.top(); // The final result is at the top of the stack
}

// Function to evaluate prefix expression
int evaluatePrefix(string exp)
{
    stack<int> stack; // Use the standard stack from the library for evaluation
    for (int i = exp.size() - 1; i >= 0; i--)
    { // Iterate from right to left
        if (isdigit(exp[i]))
        {                             // If the character is a digit
            stack.push(exp[i] - '0'); // Push the integer value onto the stack
        }
        else
        {
            int val1 = stack.top();
            stack.pop(); // Pop the top two values
            int val2 = stack.top();
            stack.pop();
            stack.push(applyOp(val1, val2, exp[i])); // Apply the operator and push the result
        }
    }
    return stack.top(); // The final result is at the top of the stack
}

int main()
{
    // Array of infix expression to convert and evaluate
    string expression;

    // Accept the input expression
    cout << "INPUT: ";
    cin >> expression;

    // Convert and display postfix expression
    cout << "POSTFIX OUTPUT: ";
    Stack stack;
    if (stack.isMatchingParenthesis(expression))
    {                                              // Check if the parentheses match
        cout << infixToPostfix(expression) << " "; // Convert and print the postfix expression
    }
    else
    {
        cout << "Invalid Expression "; // Print an error message if invalid
    }
    cout << endl;

    // Convert and display prefix expression
    cout << "PREFIX OUTPUT: ";
    if (stack.isMatchingParenthesis(expression))
    {                                             // Check if the parentheses match
        cout << infixToPrefix(expression) << " "; // Convert and print the prefix expression
    }
    else
    {
        cout << "Invalid Expression "; // Print an error message if invalid
    }
    cout << endl;

    return 0; // End of the program
}
