#include <iostream>

using namespace std;

class Rectangle {
private:
    double length;
    double width;

public:
    // Constructor
    Rectangle(double l, double w) {
        length = l;
        width = w;
    }

    // Method to calculate area
    double calculateArea() {
        return length * width;
    }

    // Method to calculate perimeter
    double calculatePerimeter() {
        return 2 * (length + width);
    }

    // Getter methods
    double getLength() {
        return length;
    }

    double getWidth() {
        return width;
    }

    // Setter methods
    void setLength(double l) {
        length = l;
    }

    void setWidth(double w) {
        width = w;
    }
};

int main() {
    // Creating object of Rectangle class
    Rectangle rect(5.0, 4.0);

    // Displaying rectangle details
    cout << "Rectangle Details:" << endl;
    cout << "Length: " << rect.getLength() << endl;
    cout << "Width: " << rect.getWidth() << endl;
    cout << "Area: " << rect.calculateArea() << endl;
    cout << "Perimeter: " << rect.calculatePerimeter() << endl;

    // Modifying rectangle dimensions
    rect.setLength(6.0);
    rect.setWidth(3.0);

    // Displaying updated rectangle details
    cout << "\nUpdated Rectangle Details:" << endl;
    cout << "Length: " << rect.getLength() << endl;
    cout << "Width: " << rect.getWidth() << endl;
    cout << "Area: " << rect.calculateArea() << endl;
    cout << "Perimeter: " << rect.calculatePerimeter() << endl;

    return 0;
}
