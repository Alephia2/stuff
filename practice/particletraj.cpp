#include <iostream>
#include <cmath> 
#include <string>

double AskValue (const char* prompt){
    double value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

int main (){
    struct particle {
        int id;
        double mass;
        double velocity;
    };

int ask1 = AskValue("Enter Id: ");
double ask2 = AskValue("Enter mass; ");
double ask3 = AskValue("Enmter velocity: ");

struct particle particle1 = {ask1, ask2, ask3};

double kenetic = 1/2 * particle1.mass * pow(particle1.velocity, 2);

std::cout << "Kenetic Energy: " << kenetic;

}