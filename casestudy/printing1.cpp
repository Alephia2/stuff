#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <limits>
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
    string extra;
    float cost;
    float wait;
    int queuenum = 0;
    int processing = 0;
       //0 = pendinig
       //1 = processing
       //2 = completed
};

void initialDisplay (){
    for (int i = 0 ; i < 40 ; i++){
        cout << "=";
    }
    cout << endl;
    cout << "          WELCOME TO PRINTFLOW" << endl;
    cout << "    Automatic Printing Service Manager" << endl;
    for (int i = 0 ; i < 40 ; i++){
        cout << "=";
    }
    cout << endl;
    cout << "Press Enter to continue. . .";
    cin.get();
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

    if (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        inChoice = 0;
    }

    return inChoice;
}

void newname (int queuecount, printreq queue[]){
    cout << "------- NEW PRINT REQUEST -------" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Document name:                        " << endl;
    getline(cin, queue[queuecount].name);
    cout << "Customer name:                        " << endl;
    getline(cin, queue[queuecount].nameperson);
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
    while (!(cin >> queue[queuecount].papersize) || queue[queuecount].papersize < 1 || queue[queuecount].papersize > 5){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid paper size. Enter 1-5: " << endl;
    }

}

void newcolormode (int queuecount, printreq queue[]){
    cout << "b&w - 1 or Colored - 2" << endl;
    cout << "Color Mode:                           " << endl;
    while (!(cin >> queue[queuecount].colormode) || queue[queuecount].colormode < 1 || queue[queuecount].colormode > 2){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid color mode. Enter 1 or 2: " << endl;
    }
}

void newpages (int queuecount, printreq queue[]){
    cout << "Number of Pages:                      " << endl;
    while (!(cin >> queue[queuecount].pages) || queue[queuecount].pages < 1){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of pages. Enter a number above 0: " << endl;
    }
}

void newcopies(int queuecount, printreq queue[]){
    cout << "Number of Copies:                     " << endl;
    while (!(cin >> queue[queuecount].copies) || queue[queuecount].copies < 1){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of copies. Enter a number above 0: " << endl;
    }
}

void newextra(int queuecount, printreq queue[]){
    cout << "Extra options (none/binding):       "<< endl;
    cin >> queue[queuecount].extra;

}

void calculatecost (int queuecount, printreq queue[]){
    int valuesize = queue[queuecount].papersize - 1;
    int valuecolormode = queue[queuecount].colormode - 1;
    queue[queuecount].cost = queue[queuecount].pages * queue[queuecount].copies * price_table[valuesize][valuecolormode];

}

void calculatewait (int queuecount, printreq queue[]){
    queue[queuecount].wait = queue[queuecount].pages * queue[queuecount].copies * waitimeperpage;
}

char ordersummary (int queuecount, printreq queue[]){
    char confirm;
    cout << "--------- ORDER SUMMARY ---------" << endl;
    cout <<"Total Pages:                 " << queue[queuecount].pages * queue[queuecount].copies << endl;
    cout <<"Estimated Cost:              " << queue[queuecount].cost << endl;
    cout <<"Estimated waittime:         " << queue[queuecount].wait << endl;
    cout <<"Queue Number:                "<< queue[queuecount].queuenum << endl;
    cout <<"----------------------------------" << endl;
    do {
        cout <<"Confirm order? (Y/N): ";
        cin >> confirm;
    } while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');
    return confirm;
}

char queuedisplay (int queuecount, printreq queue[]){
    char inChoice;
    cout << "================= CURRENT QUEUE =================" << endl;
    cout << left << setw(8) << "Queue#" << setw(20) << "Document" << setw(10) << "Pages" << setw(8) << "Status" << endl;
    cout <<"--------------------------------------------------" << endl;

    if (queuecount == 0){
        cout << "No orders in the queue." << endl;
    }

    for (int i = 0 ; i < queuecount ; i++){
    cout << left << setw(8) << queue[i].queuenum
        << setw(20) << queue[i].name 
        << setw(10)<< queue[i].pages;
        
        if (queue[i].processing == 1){
            cout << left << setw(8) << "Processing. . ." << endl;
        } else if (queue[i].processing == 0){
            cout << left << setw(8) << "Pending" << endl;
        } else {
            cout << left << setw(8) << "completed" << endl;
        }
    }

    for (int i = 0 ; i < 49 ; i++){
        cout << "=";
    }
    cout << endl;
    cout << "Press any key to Exit: ";
    cin >> inChoice;
    return inChoice;
}

char processnextorder (int queuecount, printreq queue[]){
    char inChoice;
    int next = -1;

    for (int i = 0 ; i < queuecount ; i++){
        if (queue[i].processing == 0){
            next = i;
            break;
        }
    }

    if (next == -1){
        cout << "No pending orders to process." << endl;
    } else {
        queue[next].processing = 1;
        cout << "Processing Order " << queue[next].queuenum << ". . . ." << endl;
        cout << "Status updated: Processing -> Completed" << endl;
        queue[next].processing = 2;
    }
   cout << "Return to menu (y/n): ";
   cin >> inChoice; 
   return inChoice;
}

char printreceipt (int queuecount, printreq queue[]){
    char inChoice;
    int ordernum;

    if (queuecount == 0){
        cout << "No orders yet. Nothing to print." << endl;
    } else {
        cout << "Enter Queue No (1-" << queuecount << "): ";
        while (!(cin >> ordernum) || ordernum < 1 || ordernum > queuecount){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid queue number. Try again: ";
        }

        int idx = ordernum - 1;
        int valuesize = queue[idx].papersize - 1;
        int valuecolormode = queue[idx].colormode - 1;

        cout << "================================" << endl;
        cout << "        PRINTFLOW RECEIPT"<< endl;
        cout << "Queue No:                  " << queue[idx].queuenum << endl;
        cout << "Customer:                  " << queue[idx].nameperson << endl;
        cout << "--------------------------------" << endl;
        cout << "Document:                 " << queue[idx].name << endl;
        cout << "Paper Size:               " << queue[idx].papersize << endl;
        cout << "Color Mode:               ";

        if (queue[idx].colormode == 1){
            cout << "Black&White";
        } else if (queue[idx].colormode == 2){
            cout << "Colored";
        } else {
            cout << "invalid colormode";
        } cout << endl; 

        cout << "Copies:                   " <<queue[idx].copies  << endl;
        cout << "Pages/copies:            " << queue[idx].pages << endl;
        cout << "Total Pages:             " << queue[idx].pages * queue[idx].copies << endl;
        cout << "-------------------------------" << endl;
        cout << "Unit Price:              " << price_table[valuesize][valuecolormode]<<endl;
        cout << "binding:             " << queue[idx].extra << endl;
        cout << "-------------------------------" << endl;
        cout << "Total Due:                " << queue[idx].cost << endl;
        cout << "-------------------------------" << endl;
        cout << "Status:                   ";
        if (queue[idx].processing == 2){
            cout << "Completed" << endl;
        } else if (queue[idx].processing == 1){
            cout << "Processing" << endl;
        } else {
            cout << "Pending" << endl;
        }
        cout << "================================" << endl;
        cout << "Thank you for Printing with PRINTFLOW!" << endl;
        cout << "================================" << endl;
    }

 cout << "\n\nReturn to menu (y/n): ";
   cin >> inChoice; 
   return inChoice;
}

int main (){
    initialDisplay();
    int inChoice;
    char choice;
    char confirm;
    const int size = 100;
    int queuecount = 0;
    struct printreq queue[size];

    cout << fixed << setprecision(2);

    do {
    inChoice = mainMenu();

    switch (inChoice) {
        case 1: {
            if (queuecount >= size){
                cout << "Queue is full." << endl;
                break;
            }
            do {
            newname(queuecount, queue);
            newpapersize(queuecount, queue);
            newcolormode(queuecount, queue);
            newpages(queuecount, queue);
            newcopies(queuecount, queue);
            newextra(queuecount, queue);
            calculatecost(queuecount, queue);
            calculatewait(queuecount, queue);
            queue[queuecount].queuenum = queuecount + 1;
            confirm = ordersummary(queuecount, queue);
            } while (confirm == 'n' || confirm == 'N');
            queuecount++;
        } break;

        case 2: {
            do {
                choice = queuedisplay(queuecount, queue);
            } while (choice == 'n' || choice == 'N');
        } break;

        case 3: {
            do {choice = processnextorder(queuecount, queue);
            } while (choice == 'n' || choice == 'N');
        } break;

        case 4: {
            do {
                choice = printreceipt(queuecount, queue);
            } while (choice == 'n' || choice == 'N');
        } break;

        case 5: {
            cout << "Goodbye!" << endl;
        } break;

        default: {
            cout << "Invalid choice. Please enter 1-5." << endl;
        }

    }   

    } while (inChoice != 5);

    return 0;
}