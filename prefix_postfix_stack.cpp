#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

// Function to evaluate a postfix expression
int evaluatePostfix(const std::string& postfix) {
    std::stack<int> operandStack;

    for (char ch : postfix) {
        if (std::isdigit(ch)) {
            // If the character is a digit, push its integer value onto the stack
            operandStack.push(ch - '0');
        } else if (std::isspace(ch)) {
            // Skip whitespace
            continue;
        } else {
            // If the character is an operator, pop two operands from the stack, perform the operation, and push the result back
            if (operandStack.size() < 2) {
                std::cerr << "Error: Insufficient operands for operator " << ch << std::endl;
                return 0; // Return 0 for simplicity in case of an error
            }

            int operand2 = operandStack.top();
            operandStack.pop();

            int operand1 = operandStack.top();
            operandStack.pop();

            switch (ch) {
                case '+':
                    operandStack.push(operand1 + operand2);
                    break;
                case '-':
                    operandStack.push(operand1 - operand2);
                    break;
                case '*':
                    operandStack.push(operand1 * operand2);
                    break;
                case '/':
                    if (operand2 != 0) {
                        operandStack.push(operand1 / operand2);
                    } else {
                        std::cerr << "Error: Division by zero" << std::endl;
                        return 0;
                    }
                    break;
                default:
                    std::cerr << "Error: Unknown operator " << ch << std::endl;
                    return 0;
            }
        }
    }

    // The final result should be at the top of the stack
    if (!operandStack.empty()) {
        return operandStack.top();
    } else {
        std::cerr << "Error: Empty stack. Expression may be invalid." << std::endl;
        return 0;
    }
}

int main() {
    std::string postfixExpression;

    // Get the postfix expression from the user
    std::cout << "Enter a postfix expression: ";
    std::getline(std::cin, postfixExpression);

    // Evaluate the postfix expression and display the result
    int result = evaluatePostfix(postfixExpression);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
