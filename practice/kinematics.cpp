#include <iostream>
#include <math.h> 

using namespace std;

void initial_display (){
    cout << "=====WELCOME TO KINEMATICS CALCULATOR=====\n";
}

float askValue (char* prompt) {
    float value;
    cout << prompt;
    cin >> value;
    return value;
}

float calculateVelo (float iniVelo, float time, float acc){
    float velo = iniVelo + acc * time;
    return iniVelo; 
}

float calculateDisplacement (float iniVelo, float time, float acc){
    float displacement =  (iniVelo * time) + (1/2 * acc * pow(time, 2));
    return displacement;
}

void display (float iniVelo, float time, float acc, float velo, float displacement){
    cout << "\n\n-----------RESULTS------------\n";
    cout << "Initial Velocity: " << iniVelo << endl;
    cout << "Time: " << time << endl;
    cout << "Velocity: " << velo << endl;
    cout << "Displacement: " << displacement << endl;
}


int main () {
    float iniVelo, time, acc, velo, displacement;
    
    iniVelo = askValue("Enter Initial Value: ");
    time = askValue("Enter Time: ");
    acc = askValue("Enter Acceleration: ");

    velo = calculateVelo(iniVelo, time, acc);
    displacement = calculateDisplacement(iniVelo, time, acc);

    display(iniVelo, time, acc, velo, displacement);
}