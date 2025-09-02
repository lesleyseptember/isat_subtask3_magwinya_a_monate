#include <iostream>
#include <iomanip>
#include <string>
#include <limits>   // numeric
#include <algorithm> // fill
using namespace std;

const int MAX_ORDERS = 50; //no change

//parallel arrays 
//store information about orders
int    orderId[MAX_ORDERS];
string customerName[MAX_ORDERS];
int    magwinyaQty[MAX_ORDERS];
float  totalAmount[MAX_ORDERS];

//current number of saved orders
int orderCount = 0;

//helper utilities
void seedInitialData() {
    //preload first 10 entries/manually
    int    ids[10]    = {101,102,103,104,105,106,107,108,109,110};
    string names[10]  = {"Thabo","Lerato","Nomvula","Sipho",
                         "Bongani","Lindiwe","Jabulani","Ayanda",
                         "Kgosi","Refilwe"};
    int    qtys[10]   = {3,5,2,4,4,3,2,6,4,5};
    float  totals[10] = {15.75f,30.50f,10.00f,22.00f,
                         40.25f,5.25f,12.75f,18.00f,
                         28.00f,24.50f};   // corrected totals per your request

    for (int i = 0; i < 10; ++i) {
        orderId[i]      = ids[i];
        customerName[i] = names[i];
        magwinyaQty[i]  = qtys[i];
        totalAmount[i]  = totals[i];
    }
    orderCount = 10;

    //initialize to empty values 
    //initialize project with base order management system
    std::fill(orderId + orderCount, orderId + MAX_ORDERS, 0);
    std::fill(magwinyaQty + orderCount, magwinyaQty + MAX_ORDERS, 0);
    std::fill(totalAmount + orderCount, totalAmount + MAX_ORDERS, 0.0f);
    for (int i = orderCount; i < MAX_ORDERS; ++i) {
        customerName[i].clear();
    }
}

int findIndexById(int id) {
    for (int i = 0; i < orderCount; ++i) {
        if (orderId[i] == id) return i;
    }
    return -1;
}

//Menu
void addOrder() {
    if (orderCount >= MAX_ORDERS) {
        cout << "Storage full. Cannot add more orders.\n";
        return;
    }

    int id;
    cout << "Enter Order ID: ";
    while (!(cin >> id) || id <= 0 || findIndexById(id) != -1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (id <= 0) cout << "Order ID must be a positive integer. Try again: ";
        else cout << "Order ID already exists. Enter a different one: ";
    }

    cout << "Enter Customer Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
    string name;
    getline(cin, name);

    int qty;
    cout << "Enter Number of Magwinyas Ordered: ";
    while (!(cin >> qty) || qty < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid non-negative integer for quantity: ";
    }

    float total;
    cout << "Enter Total Cost: ";
    while (!(cin >> total) || total < 0.0f) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid non-negative amount: ";
    }

    orderId[orderCount]      = id;
    customerName[orderCount] = name;
    magwinyaQty[orderCount]  = qty;
    totalAmount[orderCount]  = total;
    orderCount++;

    cout << "Order added successfully! (Order ID: " << id << ")\n";
}

void displayAll() {
    if (orderCount == 0) {
        cout << "No orders to display.\n";
        return;
    }

    cout << left << setw(10) << "OrderID"
         << left << setw(15) << "Customer"
         << left << setw(10) << "Qty"
         << left << setw(10) << "Total" << '\n';

    cout << string(45, '-') << '\n';

    cout << fixed << setprecision(2);
    for (int i = 0; i < orderCount; ++i) {
        cout << left << setw(10) << orderId[i]
             << left << setw(15) << customerName[i]
             << left << setw(10) << magwinyaQty[i]
             << "R " << totalAmount[i] << '\n';
    }
}

void findOrder() {
    cout << "Enter Order ID to find: ";
    int id;
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Order ID.\n";
        return;
    }

    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "Order with ID " << id << " not found.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "Order ID: " << orderId[idx]
         << ", Customer: " << customerName[idx]
         << ", Number of Magwinyas: " << magwinyaQty[idx]
         << ", Total: R " << totalAmount[idx] << '\n';
}

void calculateRevenue() {
    float sum = 0.0f;
    for (int i = 0; i < orderCount; ++i) sum += totalAmount[i];
    cout << fixed << setprecision(2)
         << "Total revenue from all orders: R " << sum << '\n';
}

// main program 
int main() {
    seedInitialData();  // preload orders
                        //Fix total amounts in seeded initial data

    int choice;
    do {
        cout << "\nOrder Management System\n"
             << "1. Add a new order\n"
             << "2. Display all orders\n"
             << "3. Find an order by Order ID\n"
             << "4. Calculate total revenue\n"
             << "5. Exit\n"
             << "Enter your choice (1-5): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
            case 1: addOrder(); break;
            case 2: displayAll(); break;
            case 3: findOrder(); break;
            case 4: calculateRevenue(); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option. Choose 1-5.\n"; break;
        }
    } while (choice != 5);

    return 0;
}
