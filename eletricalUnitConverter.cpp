#include <iostream>

using namespace std;

void inidialDisplay (){
    cout << "===WELCOME TO ELECTRICAL UNIT CONVERTER===\n";
    cout << "1   -   V = I*R\n";
    cout << "2   -   I = V/R\n";
    cout << "3   -   R = V/I\n\n";
}

float askForValue (char* prompt) {
    float value;
    cout << prompt;
    cin >> value;
    return value;
}

float get_calculation (int value, float voltage, float current, float resistance) {
    if (value == 1) {
        voltage = current * resistance;
        return voltage;
    } else if (value == 2 ) {
        current = voltage / resistance;
        return current;
    } else if (value == 3) {
        resistance = voltage / current;
    } else {
        cout << "ERROR INVALID";
    }
}
void display (float voltage, float current, float resistance) {
    cout << "\n\n-----RESULTS-----\n";
    cout << "Voltage: " << voltage << endl;
    cout << "Current: " << current << endl;
    cout << "Resistance: " << resistance << endl;
}


int main (){
    float voltage, current, resistance;
    int value;

    inidialDisplay();
    value = askForValue ("Enter Which Operation to Do: ");

    if (value == 1){
        current = askForValue("Enter Current: ");
        resistance = askForValue ("Enter Resistance");
        voltage = get_calculation(value, voltage, current, resistance);
        display(voltage, current, resistance);

    } else if (value == 2) {
        voltage = askForValue("Enter Voltage: ");
        resistance = askForValue("Enter Resistance: ");
        current = get_calculation(value, voltage, current, resistance);
        display(voltage, current, resistance);
        
    } else if (value == 3) {
        voltage = askForValue("Enter Voltage: ");
        current = askForValue("Enter Current: ");
        resistance = get_calculation(value, voltage, current, resistance);
        display(voltage, current, resistance);
    }

}