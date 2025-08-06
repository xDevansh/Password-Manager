#include <iostream>  
using namespace std;

int main() {
    int choice;

    while (true) {  
        cout << "\n=== Password Manager ===\n";
        cout << "1. Add New Password\n";
        cout << "2. View Stored Passwords\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; 

        switch (choice) {
        case 1:
            cout << "Add Password functionality will go here.\n";
            break;
        case 2:
            cout << "View Passwords functionality will go here.\n";
            break;
        case 3:
            cout << "Exiting Password Manager.\n";
            return 0;  
        default:
            cout << "Invalid choice. Please enter 1, 2 or 3.\n";
        }
    }

    return 0;
}
