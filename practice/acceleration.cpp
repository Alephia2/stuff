#include <iostream>

using namespace std;
double ask_for_value (char* prompt) {
    double value;
    cout << prompt;
    cin >> value;
    return value;
}

double get_acceleration (double force, double mass){
    double acceleration = force / mass;
    return acceleration;
}

void display_shit (double acceleration, double force, double mass) {
    cout << "=== ACCELERATION CALCULATOR ==\n";
    cout << "Force: " << force << endl;
    cout << "Mass: " << mass << endl;
    cout << "---------------------------------\n";
    cout << "Acceleration: " << acceleration << endl;
} 

int main () {
    double value;
    float force, mass, acceleration;

    force = ask_for_value("Enter Force: ");
    mass = ask_for_value("Enter Mass: ");

    get_acceleration (force, mass);
    display_shit (acceleration, force, mass);
}