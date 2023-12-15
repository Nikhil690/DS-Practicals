#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

// Stack class as an ADT
template <typename T>
class Stack {
private:
    std::stack<T> data;

public:
    // Function to push an element onto the stack
    void push(T value) {
        data.push(value);
    }

    // Function to pop an element from the stack
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        T top = data.top();
        data.pop();
        return top;
    }

    // Function to check if the stack is empty
    bool isEmpty() const {
        return data.empty();
    }

    // Function to get the top element of the stack without popping it
    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data.top();
    }
};

// Function to evaluate a postfix expression
template <typename T>
T evaluatePostfixExpression(const std::string& expression) {
    Stack<T> stack;

    std::istringstream iss(expression);
    std::string token;
    while (iss >> token) {
        if (isdigit(token[0])) {
            // If the token is a number, push it onto the stack
            stack.push(static_cast<T>(std::stoi(token)));
        } else {
            // If the token is an operator, pop operands from the stack, perform the operation, and push the result back
            T operand2 = stack.pop();
            T operand1 = stack.pop();

            if (token == "+") {
                stack.push(operand1 + operand2);
            } else if (token == "-") {
                stack.push(operand1 - operand2);
            } else if (token == "*") {
                stack.push(operand1 * operand2);
            } else if (token == "/") {
                if (operand2 == 0) {
                    throw std::runtime_error("Division by zero");
                }
                stack.push(operand1 / operand2);
            } else {
                throw std::runtime_error("Invalid operator: " + token);
            }
        }
    }

    if (stack.isEmpty()) {
        throw std::runtime_error("Invalid postfix expression");
    }

    return stack.pop();
}

int main() {
    try {
        // Example postfix expression: "5 3 4 * +"
        std::string postfixExpression;
        std::cout << "Enter a postfix expression (space-separated): ";
        std::getline(std::cin, postfixExpression);

        // Evaluate the postfix expression
        int result = evaluatePostfixExpression<int>(postfixExpression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
