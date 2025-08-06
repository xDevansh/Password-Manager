#include <iostream>  
#include<string>
#include<fstream>

using namespace std;


void addPassword() { //functionality for adding password
    string website, username, password;

    cout << "\nEnter Website Name: ";
    cin >> website;

    cout << "Enter Username or Email: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    // use ofstream to open file in append mode to add new entry at the end
    ofstream file("passwords.txt", ios::app);  

    if (file.is_open()) {
 
        file << website << " " << username << " " << password << endl;
        cout << "Password saved successfully!\n";
    }
    else {
        cout << "Error: Could not open file for writing.\n";
    }

    file.close();  //closing the file
}

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
            addPassword();
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
