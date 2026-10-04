#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#define costperpage 3
#define waitimeperpage 0.05

using namespace std;

float price_table[5][2] = {
    {2.00 , 3.00},    //1 = letter                 2nd column = B&w, 3rd = colored
    {2.00 , 4.25},   //2 = legal                          
    {2.00 , 3.00},   //3 = a4
    {2.00 , 4.50},   //4 = photopaper
    {2.00 , 4.50}    //5 = sticker paper
    
};

struct printreq {
    string name;
    string nameperson;
    int papersize;
    
    int colormode;
    int pages;
    int copies;
    int extra;
    float cost;
    float wait;
    int queuenum = 0;
    int processing = 0;
       //0 = pendinig
       //1 = processing
       //2 = completed
};

void initialDisplay (){
    for (int i = 0 ; i < 10 ; i++){
        cout << "=";
    }
    cout << left << setw(7) << "WELCOME TO PRINTFLOW" << endl;
    cout << left << setw(3) << "Automatic Printing Service Manager" << endl;
    for (int i = 0 ; i < 10 ; i++){
        cout << "=";
    }
    cout << left << setw(5) << "Press Enter to continue. . .";
}

int mainMenu (){
    int inChoice;
    cout << "\n================ MAIN MENU ================" << endl;
    cout << "1. New Print Request " << endl;
    cout << "2. View Queue / Order Status" << endl;
    cout << "3. Process Next Order" << endl;
    cout << "4. Generate Receipt" << endl;
    cout << "5. Exit" << endl;
    cout << "=============================================" << endl;
    cout << "Enter choice (1-5): ";
    cin >> inChoice;

    return inChoice;
}

void newname (int queuecount, printreq queue[]){
    cout << "------- NEW PRINT REQUEST -------" << endl;
    cout << "Document name:                        " << endl;
    cin >> queue[queuecount].name;
}

void newpapersize (int queuecount, printreq queue[]){
    cout << "-----------------------------------------" << endl;
    cout << "Letter                -                1     "<< endl;
    cout <<"Legal                  -                2     "<< endl;
    cout <<"A4                     -                3     "<< endl;
    cout <<"Photopaper            -                4     "<< endl;
    cout <<"Sticker Paper         -                5     "<< endl;
    cout << "-----------------------------------------" << endl;
    cout << "Paper size:                           " << endl;
    cin >> queue[queuecount].papersize;

}

void newcolormode (int queuecount, printreq queue[]){
    cout << "b&w - 1 or Colored - 2" << endl;
    cout << "Color Mode:                           " << endl;
    cin >> queue[queuecount].colormode;
}

void newpages (int queuecount, printreq queue[]){
    cout << "Number of Pages:                      " << endl;
    cin >> queue[queuecount].pages;
}

void newcopies(int queuecount, printreq queue[]){
    cout << "Number of Copies:                     " << endl;
    cin >> queue[queuecount].copies;
}

void newextra(int queuecount, printreq queue[]){
    cout << "Extra options (none/binding):       "<< endl;
    cin >> queue[queuecount].extra;

}

void calculatecost (int queuecount, printreq queue[]){
    int valuesize = queue[queuecount.papersize];
    int valuecolormode = queue[queuecount.colormode];
    queue[queuecount].cost = queue[queuecount].pages * queue[queuecount].copies * price_table[valuesize][valuecolormode];

}

void calculatewait (int queuecount, printreq queue[]){
    queue[queuecount].wait = queue[queuecount].pages * queue[queuecount].copies * waitimeperpage;
}

char ordersummary (int queuecount, printreq queue[]){
    char confirm;
    cout << "--------- ORDER SUMMARY ---------" << endl;
    cout <<"Total Pages;                 " << queue[queuecount].pages << endl;
    cout <<"Estimated Cost:              " << queue[queuecount].cost << endl;
    cout <<"Estimated waittime:         " << queue[queuecount].wait << endl;
    cout <<"Queue Number:                "<< queue[queuecount].wait << endl;
    cout <<"----------------------------------" << endl;
    cout <<"Confirm order? (Y/N): ";
    cin >> confirm;
}

char queuedisplay (int queuecount, printreq queue[]){
    char inChoice;
    cout << "================= CURRENT QUEUE =================";
    cout << left << setw(2) << "Queue#" << setw(8) << "Document" << setw(18) << "Pages" << setw(8) << "Status" << endl;
    cout <<"--------------------------------------------------" << endl;
    

    for (int i = 0 ; i < queue[queuecount].queuenum ; i++){
    cout << left << setw(2) << queue[queuecount].queuenum
        << setw(8) << queue[i].name 
        << setw(18)<< queue[i].pages;
        
        if (queue[queuecount].processing == 1){
            cout << left << setw(8) << "Processing. . ." << endl;
        } else if (queue[queuecount].processing == 0){
            cout << left << setw(8) << "Pending" << endl;
        } else {
            cout << left << setw(8) << "completed" << endl;
        }
    }

    for (int i = 0 ; i < 10 ; i++){
        cout << "=";
    }
    cout << "Press any key to Exit: ";
    cin >> inChoice;
    return inChoice;
}

char processnextorder (int queuecount, printreq queue[]){
    char inChoice;
    cout << "Processing Order " << queue[queuecount].queuenum << ". . . ." << endl;
    cout << "Status updated: Processing → Completed" << endl;
    queue[queuecount].processing = 2;
   cout << "Return to menu (y/n): ";
   cin >> inChoice; 
   return inChoice;
}

char printreceipt (int queuecount, printreq queue[]){
    int valuesize = queue[queuecount.papersize];
    int valuecolormode = queue[queuecount.colormode];

    cout << "================================" << endl;
    cout << "        PRINTFLOW RECEIPT"<< endl;
    cout << "Queue No:                  " << queue[queuecount].queuenum << endl;
    cout << "Customer:                  " << queue[queuecount].nameperson << endl;
    cout << "--------------------------------" << endl;
    cout << "Document:                 " << queue[queuecount].name << endl;
    cout << "Paper Size:               " << queue[queuecount].papersize << endl;
    cout << "Color Mode:               ";

    if (queue[queuecount].colormode == 1){
        cout << "Black&White";
    } else if (queue[queuecount].colormode == 2){
        cout << "Colored";
    } else {
        cout << "invalid colormode";
    } cout << endl; 

    cout << "Copies:                   " <<queue[queuecount].copies  << endl;
    cout << "Pages/copies:            " << queue[queuecount].pages << endl;
    cout << "Total Pages:             " << queue[queuecount].pages * queue[queuecount].copies << endl;
    cout << "-------------------------------" << endl;
    cout << "Unit Price:              " << price_table[valuesize][valuecolormode]<<endl;
    cout << "binding:             " << queue[queuecount].extra << endl;
    cout << "-------------------------------" << endl;
    cout << "Total Due:                " << queue[queuecount].cost << endl;
    cout << "-------------------------------" << endl;
    cout << "Status:                   " << "Completed" << endl;
    cout << "================================" << endl;
    cout << "Thank you for Printing with PRINTFLOW!";
    cout << "================================" << endl;


char inChoice;
 cout << "\n\nReturn to menu (y/n): ";
   cin >> inChoice; 
   return inChoice;
}

int main (){
    initialDisplay();
    int inChoice;
    char choice;
    int confirm;
    int size = 100;
    int queuecount = 0;
    struct printreq queue[size];

    do {
    inChoice = mainMenu();

    switch (inChoice) {
        case 1: {
            do {
            newname(queuecount, queue);
            newpapersize(queuecount, queue);
            newcolormode(queuecount, queue);
            newpages(queuecount, queue);
            newcopies(queuecount, queue);
            newextra(queuecount, queue);
            calculatecost(queuecount, queue);
            calculatewait(queuecount, queue);
            char confirm = ordersummary(queuecount, queue);
            queuecount++;
            queue[queuecount].queuenum + 1;
            } while (confirm == 'n' || confirm == 'N');
        } break;

        case 2: {
            do {
                choice = queuedisplay(queuecount, queue);
            } while (choice == 'n' || choice == 'N');
        } break;

        case 3: {
            do {choice = processnextorder(queuecount, queue);
            } while (choice == 'Y' || choice == 'y');
        }

        case 4: {
            printreceipt(queuecount, queue);
        }

    }   

    } while (inChoice != 5);

}



