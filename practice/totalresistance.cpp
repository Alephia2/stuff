#include <iostream>

struct resistor {
    int id;
    double resistance;
};

double calculateTotalSeries (resistor arr[], int size){
    double total = 0;
    for (int i = 0 ; i < size ; i++){
        total += arr[i].resistance;
    }
    return total;
}


int main (){
    int size = 3;
    struct resistor arr[size];

    for (int i = 0 ; i < size ; i++){
        std::cout << "Enter Resistance: ";
        std::cin >> arr[i].resistance;
    }

    double total = calculateTotalSeries(arr, size);
    std::cout << "total: " << total << std::endl;

}