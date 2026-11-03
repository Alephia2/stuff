#include <iostream>

using namespace std;

float ask_grade (char* prompt) {
    float grade;
    cout << prompt;
    cin >> grade;
    return grade;
}

bool check (float grade) {
    bool x;
    if (grade < 0 || grade > 100 ) {
        x = false;
    } else {
        x = true;
    }
return x;
}

int get_grade(float grade){
    int status;
    if (grade >= 90) {
        status = 1;
    } else if (grade >= 80) {
        status  = 2;
    } else if (grade >= 70) {
        status = 3;
    } else if (grade >= 60) {
        status = 4;
    } else {
        status = 5;
    }
    return status;
}

void display (int status) {
    if (status == 1) {
        cout << "Grade: A";
    } else if (status == 2) {
       cout << "Grade: B";
    } else if (status == 3) {
        cout << "Grade: C";
    } else if (status == 4) {
        cout << "Grade: D";
    } else if (status == 5) {
        cout << "Grade: F";
    }
}

int main () {
    float grade;
    int status;
    bool x;

    grade = ask_grade("Enter Grade: ");
    x = check(grade);

    if (x == true) {
        status = get_grade(grade);
        display(status);
    } else if (x == false){
        cout << "Invalid grades! try again please.";
    }
}