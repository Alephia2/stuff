#include <iostream>
#include <iomanip>

using namespace  std;


float askValue (const char* prompt){
    float value;
    cout << prompt;
    cin >> value;
    return value;
}
 
void getRrow (float arr[][3], float rarr[]){
    float rrow = 0.0;
    for (int i = 0 ; i < 3 ; i++){
        for (int y = 0 ; y < 3 ; y++) {
            rrow = 1/arr[i][y];
        }
    rarr[i] = 1/rrow;
        }

    }

void print (float arr[][3], float rarr[]){
    for (int i = 0 ; i < 3 ; i++){
        for (int y = 0 ; y < 3 ; y++){
        cout << left << setw(4) << arr[i][y];
    } cout << endl;
    }

    for (int i = 0 ; i < 3 ; i++){
        cout << rarr[i] << endl;
    }
}


int main(){
int i = 0;
int y = 0;
float arr[3][3];
float rarr[3];

    for ( i = 0 ; i < 3 ; i++){
         arr[i][y] = askValue("Enter resistance: ");
            for ( y = 0 ; y < 3 ; y++){
                 arr[i][y] = askValue("Enter resistance: ");
            }
    }

getRrow(arr, rarr);
print(arr, rarr);


}