#include <iostream>


float askValue (const char* prompt){
    float value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

void getArr (double* arr){
    for (int i = 0 ; i < 5 ; i++){
        *(arr + i) = askValue("Enter voltage: ");
    }
}

void average (double* avg, double* arr) {
    for (int i = 0 ; i < 4 ; i++) {
        *(avg + i) = (*(arr + i) + *(arr + i + 1)) / 2.00;
    }
}

void print (double* avg, double* arr){
    for (int i = 0 ; i < 5 ; i++){
       std::cout << "Voltage " << i + 1 << "     -     "<< *(arr + i) << std::endl;
    }
    std::cout << "----------------------------------------\n";
    for (int i = 0 ; i < 4 ; i++){
        std::cout << "average: " << *(avg + i) << std::endl;
    }


}



int main (){
    int size = 0;
    double arr[5];
    double avg[4];

    getArr(arr);
    average(avg, arr);
    print(avg, arr);
}