#include <iostream> 

using namespace std;

void applygain(double* ptr, int size, double gain){
    for (int i = 0 ; i < size ; i++){
          *(ptr ++) *= gain ;
    }


}


int main (){
    int size = 4;
    int gain;
    gain = 1;

    double arr[4] = {1.5, 2.0, 3.5, 4.0};
    double *ptr = &arr[0];



    applygain(&arr[0], size, gain);
    for (int i = 0; i < size ; i++){
        cout << arr[i] << endl;
    }
}