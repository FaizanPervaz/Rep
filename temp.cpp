#include<iostream>

// New comment cause why not ////


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
