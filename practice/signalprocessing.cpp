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

void getFilter (std::vector<double> &voltages, std::vector<double> &filteredVoltages, int N, int threshold){
    for (int i = 0 ; i < N ; i++){
        if (voltages[i] > threshold){
            filteredVoltages.push_back(voltages[i]);

        }
    }
}


int main (){
    int N = askvalue("How many entries?: ");
    std::vector<double> voltages;
    getVoltages(N, voltages);
    int threshold = askvalue ("Threshhold: ");
    std::vector<double> filteredVoltages;
    getFilter(voltages, filteredVoltages, N, threshold);
    
    std::cout << "Filtered Voltages: " << std::endl;
    std::cout << "----------------------------------------" << std:: endl;
    int size = filteredVoltages.size();
    for (int i = 0 ; i < size ; i++){
        std::cout << "V" << i + 1 << "     -     " << filteredVoltages[i] << std::endl;
    }
}


