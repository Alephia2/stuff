#include <iostream>
#include <math.h>

using namespace std;

void initialDisplay (){
    cout << "(Heating Mode) 1     -     1500W\n";
    cout << "(Cooling Mode) 2     -     1200W\n";
}

void display(){
    cout <<"L     -     LOW POWER\n";
    cout <<"M     -     MEDIUM POWER\n";
    cout <<"H     -     HIGH POWER\n";
}

float askforinput (char* prompt){
    float value;
    cout << prompt;
    cin >> value;
    return value;
}

float get_base (int status){
    float basepower;
    if (status ==1){
         basepower = 1500;
        return basepower;
    } else if (status == 2){
        basepower = 1200;
        return basepower;
}
}

float get_kwh (int status, float basepower, float time){
    float kwh;
    if (status =='L' || status == 'l'){
         kwh = basepower * time * 1;
        return kwh;

    } else if (status =='M' || status == 'm'){
        kwh = basepower * time * ( 0.2);
        return kwh;
    }  else {
         kwh = basepower * time * 0.5;
        return kwh;
}
}

int main (){
    int status;
    float basepower, time, kwh;

    initialDisplay();
    status = askforinput("ENTER BASEPOWER: ");
    basepower = get_base(status);


    display();
    status = askforinput("ENTER POWER LEVEL: ");
    time  = askforunput("ENTER TIME: ");

    kwh = get_kwh(status, basepower, time);

    cout << "kWh: "<< kwh << endl;


}