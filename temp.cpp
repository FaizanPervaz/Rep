#include <iostream>

// Function to add two numbers
int add(int a, int b) {
    return a + b;
}

// Function to subtract two numbers
int subtract(int a, int b) {
    return a - b;
}

// Function to multiply two numbers
int multiply(int a, int b) {
    return a * b;
}

// Function to divide two numbers
float divide(int a, int b) {
    if (b != 0)
        return static_cast<float>(a) / b;
    else {
        std::cerr << "Error: Division by zero!" << std::endl;
        return 0.0f;
    }
}

int main() {
    int x = 10, y = 5;
    
    std::cout << "Addition: " << add(x, y) << std::endl;
    std::cout << "Subtraction: " << subtract(x, y) << std::endl;
    std::cout << "Multiplication: " << multiply(x, y) << std::endl;
    std::cout << "Division: " << divide(x, y) << std::endl;

    return 0;
}
