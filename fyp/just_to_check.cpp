#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    string make;
    string model;
    int year;

public:
    // Constructor
    Car(string make, string model, int year);

    // Method to display car details
    void displayDetails();

    // Getter methods
    string getMake();
    string getModel();
    int getYear();

    // Setter methods
    void setMake(string make);
    void setModel(string model);
    void setYear(int year);
};

// Constructor implementation
Car::Car(string make, string model, int year) {
    this->make = make;
    this->model = model;
    this->year = year;
}

// Method to display car details implementation
void Car::displayDetails() {
    cout << "Make: " << make << endl;
    cout << "Model: " << model << endl;
    cout << "Year: " << year << endl;
}

// Getter methods implementation
string Car::getMake() {
    return make;
}

string Car::getModel() {
    return model;
}

int Car::getYear() {
    return year;
}

// Setter methods implementation
void Car::setMake(string make) {
    this->make = make;
}

void Car::setModel(string model) {
    this->model = model;
}

void Car::setYear(int year) {
    this->year = year;
}
