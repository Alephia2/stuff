#include <vector>
#include <iostream>

float askvalue (const char* prompt){
    float value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

void getVoltages (float N, std::vector<double> &voltages) {
    for (int i = 0 ; i < N ; i++){
        double temp;
        std::cout << "Enter voltage: ";
        std::cin >> temp;
        voltages.push_back(temp);
    }
}

void getFilter (int N, std::vector<double> &voltages, std::vector<double> &filteredVoltages){
    for (int i = 0 ; i < N ; i++){
        
    }
}

int main (){
    int N = askvalue("How many entries?: ");
    std::vector<double> voltages;
    getVoltages(N, voltages);
    int threshold = askvalue ("Threshhold: ");
    std::vector<double> filteredVoltages;
    
}


