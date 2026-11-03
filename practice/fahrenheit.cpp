#include <iostream>

using namespace std;

void initial_display (){
    cout << "---- WELCOME TO C TO F CALCULATOR ----\n";
}

double ask_for_c (char* prompt){
    double value;
    cout << prompt;
    cin >> value;
    return value;
}

double get_F (double c) {
    double f  = (c * (9.00 / 5.00) + 32);
    return f;
}

void display (double c, double f){
    cout << "Celsius: " << c << endl;
    cout << "Fahrenheit: " << f << endl;
}


int main () {
    double c, f;

    initial_display();
    c = ask_for_c("ENTER VALUE OF C: ");
    f = get_F (c);

    display (c, f);
}