#include <iostream>  
#include<string>
#include<fstream>
#include<limits> //ive added for implementing a important measure to ignore a newline character after the intended input

void addPassword();
void viewPasswords();

void addPassword() {
    //UPDATED: Changed 'website' to 'service' for better clarity and generic ness
    std::string service, username, password;

    //ignoring the newline after entering "choice" number
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //UPDATED: made the message more generic
    std::cout << "\nEnter Service/Account Name (e.g., Google, Home WiFi): ";
    std::getline(std::cin, service);

    //UPDATED: can be optional now.
    std::cout << "Enter Username/Email (you can leave this blank): ";
    std::getline(std::cin, username);

    std::cout << "Enter Password: ";
    std::getline(std::cin, password);

    // --- File Handling (Writing) ---
    std::ofstream file("passwords.txt", std::ios::app);

    if (file.is_open()) {
        //chnaged the delimiter to "|" instead of spaces
        file << service << " | " << username << " | " << password << std::endl;
        std::cout << "\nPassword saved successfully!\n";
    }
    else {
        //if error in writing to file
        std::cout << "\nError: Could not open file for writing.\n";
    }
    file.close();
}

void viewPasswords() {
    // --- File Handling (Reading) ---
    std::ifstream file("passwords.txt");
    std::string line;

    if (file.is_open()) {
        std::cout << "\n--- Stored Passwords ---\n";

        //'peek()' function "peeks" at the next character in the file stream without actually removing
        if (file.peek() == std::ifstream::traits_type::eof()) {
            std::cout << "No passwords stored yet.\n";
        }
        else {
            //rreading the file line by line and storing each line in "line"
            while (std::getline(file, line)) {
                //printing the value of "line"
                std::cout << line << std::endl;
            }
        }
    }
    else {
        std::cout << "\nError: Could not open file for reading, or file does not exist.\n";
    }
    file.close();
}

int main() {
    int choice;

    //to create a infinite loop menu
    while (true) {
        std::cout << "\n=== Secure Password Manager ===\n";
        std::cout << "1. Add New Password\n";
        std::cout << "2. View Stored Passwords\n";
        std::cout << "3. Exit\n";
        std::cout << "=============================\n";
        std::cout << "Enter your choice: ";

        //user's choice.
        std::cin >> choice;

        // --- Input Validation ---
        //if user doesnt enter a number
        if (std::cin.fail()) {
            std::cout << "\nError: Invalid input. Please enter a number.\n";
            std::cin.clear(); //clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//discard everything in stream till nextine
            continue; // Skip the rest of the loop and show the menu again.
        }

        //handling "choice"
        switch (choice) {
        case 1:
            addPassword();
            break;
        case 2:
            viewPasswords();
            break;
        case 3:
            std::cout << "Exiting Password Manager. Goodbye!\n";
            return 0; //exits the main function and terminates the program
        default:
            // default case handling other inputs
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }
    return 0; 
}

