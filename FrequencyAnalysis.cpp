#include <iostream>

float askValue (const char* prompt){
    float value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

int algo (int arr[], int freq, int targetnum){
    for (int i = 0 ; i < 10 ; i++){
        if (arr[i] == targetnum) {
            freq++;
        }
    }
    return freq;
}

int main (){
    int arr[10];
    for (int i = 0 ; i < 10 ; i++){
        arr[i] = askValue("Enter Number: ");
    }

    std::cout << "--------------------------\n";
    int targetnum = askValue("Enter Target Number: ");

    int freq = 0; 
    freq = algo(arr, freq, targetnum);

    if (freq == 0){
        std::cout << "Target not found in Array!\n";
    } else {
        std::cout << "Frequency: " << freq;
    }

}