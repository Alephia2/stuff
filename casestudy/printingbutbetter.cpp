#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <fstream>
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

string papernames[5] = {"Letter", "Legal", "A4", "Photopaper", "Sticker Paper"};

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

// ---------- helper functions (used by the new features) ----------

// returns the array index of the order with this queue number, or -1 if not found
int findorder (int queuecount, printreq queue[], int ordernum){
    for (int i = 0 ; i < queuecount ; i++){
        if (queue[i].queuenum == ordernum){
            return i;
        }
    }
    return -1;
}

string statustext (int processing){
    if (processing == 1){
        return "Processing";
    } else if (processing == 2){
        return "Completed";
    }
    return "Pending";
}

string lowercase (string text){
    for (int i = 0 ; i < (int)text.length() ; i++){
        if (text[i] >= 'A' && text[i] <= 'Z'){
            text[i] = text[i] + 32;
        }
    }
    return text;
}

// shows one order in full (individual display)
void displayorder (int idx, printreq queue[]){
    cout << "--------- ORDER DETAILS ---------" << endl;
    cout << "Queue No:                    " << queue[idx].queuenum << endl;
    cout << "Customer:                    " << queue[idx].nameperson << endl;
    cout << "Document:                    " << queue[idx].name << endl;
    cout << "Paper Size:                  " << papernames[queue[idx].papersize - 1] << endl;
    cout << "Color Mode:                  " << (queue[idx].colormode == 1 ? "Black&White" : "Colored") << endl;
    cout << "Copies:                      " << queue[idx].copies << endl;
    cout << "Pages/copy:                  " << queue[idx].pages << endl;
    cout << "Total Pages:                 " << queue[idx].pages * queue[idx].copies << endl;
    cout << "Binding/Extra:               " << queue[idx].extra << endl;
    cout << "Total Cost:                  " << queue[idx].cost << endl;
    cout << "Estimated waittime:          " << queue[idx].wait << endl;
    cout << "Status:                      " << statustext(queue[idx].processing) << endl;
    cout << "---------------------------------" << endl;
}

// shows one order as a table row (used by search results)
void displayrow (int idx, printreq queue[]){
    cout << left << setw(8) << queue[idx].queuenum
        << setw(20) << queue[idx].name
        << setw(20) << queue[idx].nameperson
        << setw(8) << queue[idx].pages
        << statustext(queue[idx].processing) << endl;
}

// ---------- original functions ----------

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
    cout << "5. Manage Orders" << endl;
    cout << "6. Reports & Data" << endl;
    cout << "7. Exit" << endl;
    cout << "=============================================" << endl;
    cout << "Enter choice (1-7): ";
    cin >> inChoice;

    if (cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        inChoice = 0;
    }

    return inChoice;
}

int manageMenu (){
    int inChoice;
    cout << "\n------------ MANAGE ORDERS ------------" << endl;
    cout << "1. Search / View Individual Order" << endl;
    cout << "2. Edit Order" << endl;
    cout << "3. Delete Order" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Enter choice (0-3): ";
    cin >> inChoice;

    if (cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        inChoice = -1;
    }

    return inChoice;
}

int reportsMenu (){
    int inChoice;
    cout << "\n----------- REPORTS & DATA -----------" << endl;
    cout << "1. Summary" << endl;
    cout << "2. Save to File" << endl;
    cout << "3. Load from File" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Enter choice (0-3): ";
    cin >> inChoice;

    if (cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        inChoice = -1;
    }

    return inChoice;
}

void newname (int queuecount, printreq queue[]){
    cout << "------- NEW PRINT REQUEST -------" << endl;
    cin.ignore(1000, '\n');
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
        cin.ignore(1000, '\n');
        cout << "Invalid paper size. Enter 1-5: " << endl;
    }

}

void newcolormode (int queuecount, printreq queue[]){
    cout << "b&w - 1 or Colored - 2" << endl;
    cout << "Color Mode:                           " << endl;
    while (!(cin >> queue[queuecount].colormode) || queue[queuecount].colormode < 1 || queue[queuecount].colormode > 2){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid color mode. Enter 1 or 2: " << endl;
    }
}

void newpages (int queuecount, printreq queue[]){
    cout << "Number of Pages:                      " << endl;
    while (!(cin >> queue[queuecount].pages) || queue[queuecount].pages < 1){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid number of pages. Enter a number above 0: " << endl;
    }
}

void newcopies(int queuecount, printreq queue[]){
    cout << "Number of Copies:                     " << endl;
    while (!(cin >> queue[queuecount].copies) || queue[queuecount].copies < 1){
        cin.clear();
        cin.ignore(1000, '\n');
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
        cout << "Enter Queue No: ";
        while (!(cin >> ordernum) || findorder(queuecount, queue, ordernum) == -1){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid queue number. Try again: ";
        }

        int idx = findorder(queuecount, queue, ordernum);
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

// ---------- new feature functions ----------

// Search (by queue number shows the individual order in full)
char searchorders (int queuecount, printreq queue[]){
    char inChoice;
    int searchchoice;
    int ordernum;
    int statuschoice;
    int found = 0;
    string keyword;

    if (queuecount == 0){
        cout << "No orders yet. Nothing to search." << endl;
    } else {
        cout << "------------ SEARCH ORDERS ------------" << endl;
        cout << "1. By Queue Number (individual order)" << endl;
        cout << "2. By Customer Name" << endl;
        cout << "3. By Document Name" << endl;
        cout << "4. By Status" << endl;
        cout << "Enter choice (1-4): ";
        while (!(cin >> searchchoice) || searchchoice < 1 || searchchoice > 4){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Enter 1-4: ";
        }

        if (searchchoice == 1){
            cout << "Enter Queue No: ";
            while (!(cin >> ordernum)){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid queue number. Try again: ";
            }
            int idx = findorder(queuecount, queue, ordernum);
            if (idx == -1){
                cout << "Order not found." << endl;
            } else {
                displayorder(idx, queue);
            }
        } else {
            if (searchchoice == 4){
                cout << "0 - Pending, 1 - Processing, 2 - Completed" << endl;
                cout << "Enter status (0-2): ";
                while (!(cin >> statuschoice) || statuschoice < 0 || statuschoice > 2){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid status. Enter 0-2: ";
                }
            } else {
                cin.ignore(1000, '\n');
                cout << "Enter keyword: ";
                getline(cin, keyword);
                keyword = lowercase(keyword);
            }

            cout << "================= SEARCH RESULTS ================" << endl;
            cout << left << setw(8) << "Queue#" << setw(20) << "Document" << setw(20) << "Customer" << setw(8) << "Pages" << "Status" << endl;
            cout << "-------------------------------------------------------------------" << endl;

            for (int i = 0 ; i < queuecount ; i++){
                bool match = false;
                if (searchchoice == 2){
                    match = (lowercase(queue[i].nameperson).find(keyword) != string::npos);
                } else if (searchchoice == 3){
                    match = (lowercase(queue[i].name).find(keyword) != string::npos);
                } else {
                    match = (queue[i].processing == statuschoice);
                }

                if (match){
                    displayrow(i, queue);
                    found++;
                }
            }

            if (found == 0){
                cout << "No matching orders found." << endl;
            } else {
                cout << "-------------------------------------------------------------------" << endl;
                cout << found << " order(s) found." << endl;
            }
        }
    }

    cout << "\n\nReturn to menu (y/n): ";
    cin >> inChoice;
    return inChoice;
}

// Edit a pending order (reuses the original input and calculate functions)
char editorder (int queuecount, printreq queue[]){
    char inChoice;
    int ordernum;
    int idx;
    int editchoice;

    if (queuecount == 0){
        cout << "No orders yet. Nothing to edit." << endl;
    } else {
        cout << "------------ EDIT ORDER ------------" << endl;
        cout << "Enter Queue No (0 to cancel): ";
        while (!(cin >> ordernum) || (ordernum != 0 && findorder(queuecount, queue, ordernum) == -1)){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid queue number. Try again (0 to cancel): ";
        }

        if (ordernum != 0){
            idx = findorder(queuecount, queue, ordernum);

            if (queue[idx].processing != 0){
                cout << "Only Pending orders can be edited." << endl;
            } else {
                displayorder(idx, queue);
                cout << "What do you want to edit?" << endl;
                cout << "1. Document / Customer name" << endl;
                cout << "2. Paper size" << endl;
                cout << "3. Color mode" << endl;
                cout << "4. Number of pages" << endl;
                cout << "5. Number of copies" << endl;
                cout << "6. Extra options" << endl;
                cout << "Enter choice (1-6): ";
                while (!(cin >> editchoice) || editchoice < 1 || editchoice > 6){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid choice. Enter 1-6: ";
                }

                switch (editchoice){
                    case 1: newname(idx, queue); break;
                    case 2: newpapersize(idx, queue); break;
                    case 3: newcolormode(idx, queue); break;
                    case 4: newpages(idx, queue); break;
                    case 5: newcopies(idx, queue); break;
                    case 6: newextra(idx, queue); break;
                }

                calculatecost(idx, queue);
                calculatewait(idx, queue);
                cout << "Order updated." << endl;
                displayorder(idx, queue);
            }
        }
    }

    cout << "\n\nReturn to menu (y/n): ";
    cin >> inChoice;
    return inChoice;
}

// Delete an order and shift the rest of the array to the left
char deleteorder (int &queuecount, printreq queue[]){
    char inChoice;
    char confirm;
    int ordernum;
    int idx;

    if (queuecount == 0){
        cout << "No orders yet. Nothing to delete." << endl;
    } else {
        cout << "------------ DELETE ORDER ------------" << endl;
        cout << "Enter Queue No (0 to cancel): ";
        while (!(cin >> ordernum) || (ordernum != 0 && findorder(queuecount, queue, ordernum) == -1)){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid queue number. Try again (0 to cancel): ";
        }

        if (ordernum != 0){
            idx = findorder(queuecount, queue, ordernum);
            displayorder(idx, queue);
            do {
                cout << "Delete this order? (Y/N): ";
                cin >> confirm;
            } while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');

            if (confirm == 'y' || confirm == 'Y'){
                for (int i = idx ; i < queuecount - 1 ; i++){
                    queue[i] = queue[i + 1];
                }
                queuecount--;
                queue[queuecount].queuenum = 0;
                queue[queuecount].processing = 0;
                cout << "Order deleted." << endl;
            } else {
                cout << "Delete cancelled." << endl;
            }
        }
    }

    cout << "\n\nReturn to menu (y/n): ";
    cin >> inChoice;
    return inChoice;
}

// Summary of the whole queue
char queuesummary (int queuecount, printreq queue[]){
    char inChoice;
    int pendingcount = 0;
    int processingcount = 0;
    int completedcount = 0;
    int totalpages = 0;
    float totalcost = 0;
    float completedcost = 0;
    float pendingcost = 0;
    float pendingwait = 0;

    for (int i = 0 ; i < queuecount ; i++){
        totalpages += queue[i].pages * queue[i].copies;
        totalcost += queue[i].cost;

        if (queue[i].processing == 0){
            pendingcount++;
            pendingcost += queue[i].cost;
            pendingwait += queue[i].wait;
        } else if (queue[i].processing == 1){
            processingcount++;
        } else {
            completedcount++;
            completedcost += queue[i].cost;
        }
    }

    cout << "============== QUEUE SUMMARY ==============" << endl;
    cout << "Total Orders:                " << queuecount << endl;
    cout << "  Pending:                   " << pendingcount << endl;
    cout << "  Processing:                " << processingcount << endl;
    cout << "  Completed:                 " << completedcount << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Total Pages (all orders):    " << totalpages << endl;
    cout << "Total Value (all orders):    " << totalcost << endl;
    cout << "Collected (completed):       " << completedcost << endl;
    cout << "Outstanding (pending):       " << pendingcost << endl;
    cout << "Wait time for pending:       " << pendingwait << endl;
    cout << "===========================================" << endl;

    cout << "\n\nReturn to menu (y/n): ";
    cin >> inChoice;
    return inChoice;
}

// Save the queue to a text file
void savequeue (int queuecount, int nextqueuenum, printreq queue[]){
    ofstream file("printflow_data.txt");

    if (!file){
        cout << "Could not save the file." << endl;
        return;
    }

    file << fixed << setprecision(2);
    file << queuecount << endl;
    file << nextqueuenum << endl;

    for (int i = 0 ; i < queuecount ; i++){
        file << queue[i].name << endl;
        file << queue[i].nameperson << endl;
        file << queue[i].extra << endl;
        file << queue[i].papersize << " " << queue[i].colormode << " "
             << queue[i].pages << " " << queue[i].copies << " "
             << queue[i].cost << " " << queue[i].wait << " "
             << queue[i].queuenum << " " << queue[i].processing << endl;
    }

    file.close();
    cout << "Saved " << queuecount << " order(s) to printflow_data.txt" << endl;
}

// Load the queue from the text file
// returns 1 = loaded, 0 = no file found, -1 = file is corrupted (current queue is left untouched)
int loadqueue (int &queuecount, int &nextqueuenum, printreq queue[], int size){
    ifstream file("printflow_data.txt");
    int count;
    int savednext;

    if (!file){
        cout << "No saved file found." << endl;
        return 0;
    }

    if (!(file >> count >> savednext) || count < 0 || count > size){
        cout << "Saved file is corrupted." << endl;
        return -1;
    }
    file.ignore(1000, '\n');

    printreq *loaded = new printreq[size];

    for (int i = 0 ; i < count ; i++){
        getline(file, loaded[i].name);
        getline(file, loaded[i].nameperson);
        getline(file, loaded[i].extra);
        file >> loaded[i].papersize >> loaded[i].colormode >> loaded[i].pages >> loaded[i].copies
             >> loaded[i].cost >> loaded[i].wait >> loaded[i].queuenum >> loaded[i].processing;
        file.ignore(1000, '\n');

        if (file.fail() || loaded[i].papersize < 1 || loaded[i].papersize > 5
            || loaded[i].colormode < 1 || loaded[i].colormode > 2
            || loaded[i].pages < 1 || loaded[i].copies < 1
            || loaded[i].processing < 0 || loaded[i].processing > 2){
            cout << "Saved file is corrupted." << endl;
            delete[] loaded;
            return -1;
        }
    }

    for (int i = 0 ; i < size ; i++){
        if (i < count){
            queue[i] = loaded[i];
        } else {
            queue[i].queuenum = 0;
            queue[i].processing = 0;
        }
    }

    queuecount = count;
    nextqueuenum = savednext;
    delete[] loaded;
    cout << "Loaded " << queuecount << " order(s) from printflow_data.txt" << endl;
    return 1;
}

int main (){
    initialDisplay();
    int inChoice;
    int subChoice;
    char choice;
    char confirm;
    const int size = 100;
    int queuecount = 0;
    int nextqueuenum = 1;
    struct printreq queue[size];

    cout << fixed << setprecision(2);

    ifstream checkfile("printflow_data.txt");
    if (checkfile){
        checkfile.close();
        do {
            cout << "Saved data found. Load it now? (Y/N): ";
            cin >> confirm;
        } while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');
        if (confirm == 'y' || confirm == 'Y'){
            loadqueue(queuecount, nextqueuenum, queue, size);
        }
    }

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
            queue[queuecount].queuenum = nextqueuenum;
            confirm = ordersummary(queuecount, queue);
            } while (confirm == 'n' || confirm == 'N');
            queuecount++;
            nextqueuenum++;
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
            do {
                subChoice = manageMenu();

                switch (subChoice) {
                    case 1: {
                        do {
                            choice = searchorders(queuecount, queue);
                        } while (choice == 'n' || choice == 'N');
                    } break;

                    case 2: {
                        do {
                            choice = editorder(queuecount, queue);
                        } while (choice == 'n' || choice == 'N');
                    } break;

                    case 3: {
                        do {
                            choice = deleteorder(queuecount, queue);
                        } while (choice == 'n' || choice == 'N');
                    } break;

                    case 0: {
                    } break;

                    default: {
                        cout << "Invalid choice. Please enter 0-3." << endl;
                    }
                }
            } while (subChoice != 0);
        } break;

        case 6: {
            do {
                subChoice = reportsMenu();

                switch (subChoice) {
                    case 1: {
                        do {
                            choice = queuesummary(queuecount, queue);
                        } while (choice == 'n' || choice == 'N');
                    } break;

                    case 2: {
                        savequeue(queuecount, nextqueuenum, queue);
                    } break;

                    case 3: {
                        confirm = 'y';
                        if (queuecount > 0){
                            do {
                                cout << "Loading will replace the current queue. Continue? (Y/N): ";
                                cin >> confirm;
                            } while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');
                        }
                        if (confirm == 'y' || confirm == 'Y'){
                            loadqueue(queuecount, nextqueuenum, queue, size);
                        }
                    } break;

                    case 0: {
                    } break;

                    default: {
                        cout << "Invalid choice. Please enter 0-3." << endl;
                    }
                }
            } while (subChoice != 0);
        } break;

        case 7: {
            do {
                cout << "Save before exiting? (Y/N): ";
                cin >> confirm;
            } while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');
            if (confirm == 'y' || confirm == 'Y'){
                savequeue(queuecount, nextqueuenum, queue);
            }
            cout << "Goodbye!" << endl;
        } break;

        default: {
            cout << "Invalid choice. Please enter 1-7." << endl;
        }

    }   

    } while (inChoice != 7);

    return 0;
}