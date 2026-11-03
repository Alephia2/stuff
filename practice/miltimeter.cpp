#include <iostream>
#include <cmath>

using namespace std;


void initialdisplay () {
    cout << "=====WELCOME=====\n";
    cout << "1     -     High power appliance (AC / Heater)\n";
    cout << "2     -     Low power device (LED lamp, router)\n";
    
}

float askforvalue (char* prompt){
    float value;
    cout << prompt;
    cin >> value;
    return value;
}

void initialdisplay1 () {
    cout << "R     -     Residential Rate\n";
    cout << "C     -     Commercial Rate\n)";
}

float calculatekwh (float power, float hours) {
    float kilowatthours = (power * hours) / 1000;
    return kilowatthours;
}

float calculatefinal (float kilowatthours, char status) {
    float finalp;
   if (status == 'R' || status == 'r'){
    finalp = kilowatthours / 0.15;
    return finalp;
   } else {
    finalp = kilowatthours / 0.22;
    return finalp;
   }

}

void display (float kilowatthours, char status, float finalp, float power, float hours){
    cout << "=====RECIEPT=====" << endl;
    cout << "Power: " << power << endl;
    cout << "Operating Hours: " << hours << endl;
    cout << "Kilowatt-hours: " << kilowatthours << endl;
    cout << "-----------------------------------------" << endl;

    if (status == 'R' || status == 'r') {
        cout << "residential Fee: $0.15 / kWh\n";
    }else {
        cout << "Commercial Fee: $0.22 / kWh\n";
    }

    cout << "-----------------------------------------" << endl;
    cout << "\nFinal Price: " << finalp;
}

int main (){
    float kilowatthours, finalp, power, hours;
    char status;

    initialdisplay();
    power = askforvalue("ENTER POWER: ");
    hours = askforvalue("ENTER OPERATING HOURS: ");
    calculatekwh(power, hours);

    initialdisplay1();
    status = askforvalue("ENTER STATUS: ");
    finalp = calculatefinal(kilowatthours, status);

    display(kilowatthours, status, finalp, power, hours);
}
