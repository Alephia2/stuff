#include <iostream>
#include <cmath>

using namespace std;

float askNumber (const char* prompt){
    float value;
    cout << prompt;
    cin >> value;
    return value;
}

float getAve (float arr[]){
float sum = 0.0;
float ave;
    for (int i = 0 ; i < 6 ; i++) {
        sum += arr[i];
    }

    ave = sum / 6.0;

return ave;
}

int main (){
float arr[6];

    for (int i = 0 ; i < 6 ; i++){
        arr[i] = askNumber("Enter a floating Point num: ");
    }

float average = getAve(arr);


cout << "average temp: "<< average << endl;
}
