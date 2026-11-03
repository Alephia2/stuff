#include <iostream>
#include <vector>

int askNum (const char* prompt){
    int value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

float average (double arr[], int size){
    float sum = 0.0;
    for (int i = 0 ; i < size ; i++){
    sum += arr[i];
}
float average = sum / size;
return average;
}


int main (){
    std::vector<double> arr;

int size = askNum("Enter how many scores: ");

for (int i = 0 ; i < size ; i++){
    arr.push_back(askNum("Enter Score: "));
}

float fave = average(arr.data(), size);
   std::cout << "The average score is: " << fave<< std::endl;

}