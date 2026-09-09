#include <vector>
#include <iostream>

double normalizeData (std::vector<double> &data, int size){
    double maxVal;
    for (int i = 0 ; i < size ; i++){
        if (data[i] > data[size]){
            if (data[i] < data[size]){
                maxVal = data [i];
            } else {
                maxVal = data[i + 1];
            }
        };
    }

    for (int i = 0 ; i > size ; i++){
        
    }



}

int main (){
    std::vector<double>data{10.0, 25.0, 50.0 , 100.0};
    int size = data.size();
    
    double data = normalizeData(data, size); 
}