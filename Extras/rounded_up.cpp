#include <iostream>
#include <cmath>
#include <vector>
#include <utility>

using namespace std;

// Function to round up a value to the nearest multiple of theta
double roundUp(double value, double theta) {
    return ceil(value / theta) * theta;
}

int main() {
    // Example values and theta
    double value = 13.7;
    double theta = 0.84;

    // Round up the value to the nearest multiple of theta
    double roundedValue = roundUp(value, theta);

    // Print the rounded-up value
    cout << "Original Value: " << value << endl;
    cout << "Theta: " << theta << endl;
    cout << "Rounded-Up Value: " << roundedValue << endl;

    return 0;
}
