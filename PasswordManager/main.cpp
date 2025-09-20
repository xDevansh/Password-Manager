#include <iostream>  
#include<string>
#include<fstream>
#include<limits> //ive added for implementing a important measure to ignore a newline character after the intended input
#include <random>    // For secure random number generation


void addPassword();
void viewPasswords();
std::string generatePassword();

void addPassword() {
    //UPDATED: Changed 'website' to 'service' for better clarity and generic ness
    std::string service, username, password;
    int choice;

    //ignoring the newline after entering "choice" number
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //UPDATED: made the message more generic
    std::cout << "\nEnter Service/Account Name (e.g., Google, Home WiFi): ";
    std::getline(std::cin, service);

    //UPDATED: can be optional now.
    std::cout << "Enter Username/Email (you can leave this blank): ";
    std::getline(std::cin, username);

    while (true) {
        std::cout << "\nHow would you like to set the password?\n";
        std::cout << "1. Enter password manually\n";
        std::cout << "2. Generate a strong password\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Error: Please enter '1' or '2'.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
        case 2:
            // Call the generator and store the returned password
            password = generatePassword();
            std::cout << "\nGenerated Strong Password: " << password << std::endl;
            break;
        case 1:
            std::cout << "Enter Password: ";
            // We need to ignore the leftover newline from the 'cin >> choice'
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, password);
            break;
        default:
            std::cout << "\nInvalid input. Try again\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        break;

    }
    
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

std::string generatePassword() {
    int length;
    char choice;
    bool includeLowercase, includeUppercase, includeNumbers, includeSymbols;

    std::cout << "\n--- Strong Password Generator ---\n";
    //Loop indefinitely until we get a valid length
    while (true) { 
        std::cout << "Enter desired password length (ex: 16): ";
        std::cin >> length;

        //Check 1:Handle non-numeric input 
        if (std::cin.fail() || length<0) {
            std::cout << "Error: Please enter a valid number.\n";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            continue; 
        }
        //Check 2:Handle user enters 0/default case
        if (length == 0) {
            length = 16;
            std::cout << "Length cannot be 0!. Defaulting: Length set to the default of 16.\n";
            break; 
        }
        //Check 3:Handle negative numbers
        if (length > 0) {
            break; 
        }
        else {
            //handles all negative numbers
            std::cout << "Error: Password length cannot be negative.\n";
        }
    }
    std::cout << "Configuring your password. Invalid answer defaults to 'no'." << '\n';
    std::cout << "Include lowercase letters (a-z)? (y/n): " << '\n';
    std::cin >> choice;
    includeLowercase = (choice == 'y' || choice == 'Y');

    std::cout << "Include uppercase letters (A-Z)? (y/n): " << '\n';
    std::cin >> choice;
    includeUppercase = (choice == 'y' || choice == 'Y');

    std::cout << "Include numbers (0-9)? (y/n): " << '\n';
    std::cin >> choice;
    includeNumbers = (choice == 'y' || choice == 'Y');

    std::cout << "Include symbols (!@#$%^&*)? (y/n): " << '\n';
    std::cin >> choice;
    includeSymbols = (choice == 'y' || choice == 'Y');

    std::string charset = "";
    if (includeLowercase) charset += "abcdefghijklmnopqrstuvwxyz";
    if (includeUppercase) charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (includeNumbers) charset += "0123456789";
    if (includeSymbols) charset += "!@#$%^&*";

    if (charset.empty()) {
        std::cout << "\nError: No character sets selected. Using a default set.\n";
        charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }

    // 1. Get a truly random seed from the OS
    std::random_device rd;
    // 2. Seed the Mersenne Twister engine
    std::mt19937 generator(rd());

    std::string password = "";
    // 3. Define the distribution range
    std::uniform_int_distribution<> distribution(0, charset.length() - 1);

    for (int i = 0; i < length; ++i) {
        // Pick a random character from the charset using our secure system
        password += charset[distribution(generator)];
    }

    return password; // Return the final generated password by reference
}

int main() {
    int choice;
    
    //to create a infinite loop menu
    while (true) {
        std::cout << "\n=== Secure Password Manager ===\n";
        std::cout << "1. Add New Password\n";
        std::cout << "2. View Stored Passwords\n";
        std::cout << "3. Generate a Password randomly (will not be saved)\n";
        std::cout << "4. Exit\n";
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
        {
            std::string password = generatePassword();
            std::cout << "Generated Password is: " << password;
        }

            break;
        case 4:
            std::cout << "Exiting Password Manager. Goodbye!\n";
            return 0; //exits the main function and terminates the program
        default:
            // default case handling other inputs
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }
    return 0; 
}

