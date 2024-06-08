// Header Files
#include <iostream>  //input output Stream like cin, cout
#include <fstream>   // for File Handling
#include <sstream>   // convert data types between string to other
#include <string>    // for string Methods
#include <conio.h>   // For _getch() function
#include <windows.h> // For Sleep()  function
#include <iomanip>   // For setw() function
using namespace std;

// declaration of Functions
void login_sign_in_Menu();
void main_Menu();
void banner() // temprary function for main menu beautify
{
    system("cls");
    cout << "\n\n\n\n"; // Add multiple newlines for vertical centering

    cout << "\t\t\t\t\tWelcome to the Traffic Management System\n\n";

    cout << "\t\t\t\t\t----------------------------------------\n\n";
}

void banner2() // temprary function for main menu beautify
{
    cout << "\n\n\n\n\n";
    cout << "\t\t\t\t\tWelcome to the sign-in and login page\n\n";
    cout << "\t\t\t\t\t-------------------------------------\n\n";
}

// Class User
class User
{
private:
    string username;
    string password;

public:
    // Public methods to access and modify the private attributes
    void setUsername(string uname) // set username
    {
        username = uname;
    }

    void setPassword(string pword) // set password
    {
        password = pword;
    }

    string getUsername() // get user name
    {
        return username;
    }

    string getPassword() // get password
    {
        return password;
    }

    string getPasswordInput() // Get password input and convert into staric *
    {
        string password;
        char ch;

        while ((ch = _getch()) != 13)// 13 is the ASCII code for Enter key

        { 
            if (ch != '\r')
            { // Ignore carriage return character
                cout << '*';
                password.push_back(ch);
            }
        }

        // Clear any remaining characters in the input buffer
        while (_kbhit())
        {
            _getch();
        }
        return password;
    }

    bool isUsernameTaken(string username) // This Function perfomr the Username is exist or not in a file
    {
        ifstream file("users.txt"); // ifstream input file stream & file is the object of ifstream
        if (file.is_open())
        {
            string u, p;           // u for username and p for password
            while (file >> u >> p) // read data from file into two variables u and p
            {
                if (u == username) // condition compare and return true and false
                {
                    return true;
                }
            }
            file.close(); // file close
        }
        return false;
    }

    void updateUser() // Update Function: Update username and password
    {
        string newUsername;
        string newPassword;
        string existingname;
        cout << "\t\t\t\t\tEnter your Existing user name: "; // enter existing username to update account
        cin.ignore();
        getline(cin, existingname);

        bool userFound = false; // set value dalfe by default

        ifstream inputFile("users.txt");     // iftream is input file stream
        ofstream tempFile("temp_users.txt"); // ofstream is output file stream

        if (inputFile.is_open() && tempFile.is_open()) // check condition if files is open or not
        {
            string line;
            while (getline(inputFile, line)) // this loop read the line from input file using getline() function
            {
                stringstream ss(line); // ss means stringstream break line into separate words, Each line is stored in the variable line
                string u, p;           // u for username & p for password
                ss >> u >> p;
                if (u == existingname) // check file for username is exist or not
                {
                    cout << "\n\t\t\t\t\tEnter New username: ";
                    getline(cin, newUsername);

                    if (isUsernameTaken(newUsername)) // call isUsernameTaken() fun and check condition username is already exist or not
                    {
                        cout << "\n\t\t\t\t\tUsername already taken. Please choose another name.";
                        cout << endl
                             << "\t\t\t\t\twait for 2 sec ";
                        Sleep(2000);
                        system("cls");
                        return;
                    }
                    cout << endl
                         << "\t\t\t\t\tEnter new password: ";
                    cin >> newPassword;
                    tempFile << newUsername << " " << newPassword << endl; // store updated username and password in file
                    userFound = true;
                }
                else
                {
                    tempFile << line << endl; // If the username doesn't match the existingname, the code writes the entire line
                }
            }

            inputFile.close(); // close file
            tempFile.close();  // close file

            if (userFound) // the value of userFound variable is true
            {
                if (remove("users.txt") != 0) // remove original file name using remove()
                {
                    cout << "\n\t\t\t\t\tError deleting original file.\n";
                }
                if (rename("temp_users.txt", "users.txt") != 0) // rename the original file name using rename()
                {
                    cout << "\n\t\t\t\t\tError renaming temporary file.\n";
                }

                cout << "\n\t\t\t\t\tAccount updated successfully!";
                cout << endl
                     << "\t\t\t\t\tWait for 2 seconds ";
                Sleep(2000);   // Sleep() function
                system("cls"); // clear consloe function()
            }
            else // if above condition false then run this code of block
            {
                cout << "\n\t\t\t\t\tUser name not found. Please try again.";
                cout << endl
                     << "\t\t\t\t\tWait for 2 seconds ";
                Sleep(2000);
                system("cls");
            }
        }
        else // if above condition false then run this code of block
        {
            cout << "\n\t\t\t\t\tError updating the file.";
            cout << endl
                 << "\n\t\t\t\t\tWait for 2 seconds ";
            Sleep(2000);
            system("cls");
        }
    }
}; // End of class

// Sign in class
class signin : public User // used Inheritance
{
public:
    void signUp() // signup function to create account
    {
        User newUser; // Conatinership method
        string username;
        cout << "\t\t\t\t\tEnter username: ";
        cin.ignore(); // ignore new line character
        getline(cin, username);
        cout << endl;

        if (isUsernameTaken(username)) // call isUsernameTaken() fun and check condition username is already exist or not
        {
            cout << "\n\t\t\t\t\tUsername already taken. Please choose another name.";
            cout << endl
                 << "\t\t\t\t\twait for 2 sec ";
            Sleep(2000);
            system("cls");
            return;
        }

        newUser.setUsername(username); // newuser is the object of clas User

        if (username == "") // condition for the username and password is empty or not while creating account
        {
            cout << "\t\t\t\t\tThe username should not be empty : ";
            cout << endl
                 << "\t\t\t\t\twait for 2 sec ";
            Sleep(2000);
            system("cls");
        }

        else // if above condition false then run this code of block
        {
            cout << "\t\t\t\t\tEnter password: ";
            newUser.setPassword(getPasswordInput()); // set password by calling getPasswordInput() fun

            ofstream file("users.txt", ios::app); // ios::app means All output operations are performed at the end of the file
            if (file.is_open())                   // condition for file is open or not
            {
                file << newUser.getUsername() << " " << newUser.getPassword() << endl; // store username and pass in file
                file.close();                                                          // close file
                cout << endl
                     << "\n\t\t\t\t\tAccount created successfully!";
                cout << endl
                     << "\t\t\t\t\twait for 2 sec ";
                Sleep(2000);
                system("cls");
            }
            else // if above condition false then run this code of block
            {
                cout << "\n\n\t\t\t\t\tError opening the file.";
                cout << endl
                     << "\t\t\t\t\twait for 2 sec ";
                Sleep(2000);
                system("cls");
            }
        }
    }

    bool checkCredentials(string username, string password) // Bool function check Credentials and return True and False
    {
        ifstream file("users.txt");
        if (file.is_open()) // condition for file is open or not
        {
            string u, p;           // u for username and p for password
            while (file >> u >> p) // check condition & file is the object of ifstream
            {
                if (u == username && p == password) // check condition and return true and false
                {
                    return true;
                }
            }
            file.close(); // close file
        }
        return false;
    }
}; // End of class

// Class Login
class login : public signin // used Inheritance
{
public:
    void logins() // login function for login
    {
        string username, password;
        cout << "\t\t\t\t\tEnter username: ";
        cin.ignore();
        getline(cin, username);
        cout << endl
             << "\t\t\t\t\tEnter password: ";
        password = getPasswordInput(); // set password by calling getPasswordInput() fun

        if (checkCredentials(username, password)) // check condition for login account
        {
            cout << "\n\n\t\t\t\t\tLogin successful!\n";
            cout << endl
                 << "\t\t\t\t\twait for 2 sec ";
            Sleep(2000);
            system("cls");
            main_Menu();
        }
        else // if the enters username and password are deos not exist in file then run this code
        {
            cout << "\n\n\t\t\t\t\tInvalid username or password. Please try again.";
            cout << endl
                 << "\t\t\t\t\twait for 2 sec ";
            Sleep(2000);
            system("cls");
        }
    }

    void clearScreen() // clear Screen Method
    {
        system("cls"); // this function perfom task same as system("cls")
    }
}; // End of class

// Class Vehical
class Vehicle
{
private: // class vehicle private data member
    string registrationNumber;
    string owner;
    string vehicletype;
    string entryDate;
    bool challanStatus;
    string ruleBreak;
    string pbreak;
    int cpayment;
    int challanPayment;

public:
    // initialize data members by using parameterized   ructor
    Vehicle(string regNumber = "", string ownerName = "", string vehicleType = "")
    {
        registrationNumber = regNumber;
        owner = ownerName;
        vehicletype = vehicleType;
        challanStatus = false;
        ruleBreak = "";
        pbreak = "";
        cpayment = 0;
        challanPayment = 0;
        entryDate = "";
    }

    // Public Methods of class Vehicle
    string getRegistrationNumber() // get reg no
    {
        return registrationNumber;
    }

    string getOwnerName() // get owner name
    {
        return owner;
    }

    string getVehicleType() // get vehicle type
    {
        return vehicletype;
    }

    string getEntryDate() // get entry date of vehicle
    {
        return entryDate;
    }

    void setEntryDate(string entrydate) // set entry date details by parameters
    {
        entryDate = entrydate;
    }

    bool hasChallan() // has challan function used in some differnet places
    {
        return challanStatus;
    }

    void setChallanDetails(string rule, int payment) // set challan details by parameters
    {
        ruleBreak = rule;
        pbreak = rule;
        cpayment = payment;
        challanPayment = payment;
        challanStatus = true;
    }

    void displayChallanDetails() // display challan details function and call it into other fun
    {
        cout << endl
             << "\t\t\t\t\tChallan Date       : " << entryDate << "\n";
        cout << "\t\t\t\t\tRule Break         : " << ruleBreak << "\n";
        cout << "\t\t\t\t\tChallan Payment    : pkr " << challanPayment << "\n";
    }

    void cDeatils()
    {
        cout << "\n\t\t\t\t\tRule Break : " << pbreak <<endl;
        cout << "\t\t\t\t\tChallan Payment : " << cpayment << "\n";
    }

    int getChallanPayment() // get challan payment
    {
        return challanPayment;
    }

    string getPaymentStatus() // get payment status
    {
        return challanStatus ? "Not Paid" : "Paid";
    }

    void setChallaned(bool challaned) // set challaned status by parameters type bhool true or false
    {
        challanStatus = challaned;
    }

    void setRegNumber(string newRegNumber) // Set reg No by parameters
    {
        registrationNumber = newRegNumber;
    }

    void setOwnerName(string newOwnerName) // set owner Name by parameters
    {
        owner = newOwnerName;
    }

    void setVehicleType(string newVehicleType) // set vehicle type by parameters
    {
        vehicletype = newVehicleType;
    }
}; // End of class

// class TrafficManagmentSystem This is the most imp and main part of project
class TrafficManagementSystem : public Vehicle
{
    // private Attributes of class TrafficManagmentSystem
private:
    Vehicle vehicles[100]; // suppose maximum of 100 vehicles can be registered
    int numVehicles = 0;
    int totalChallanPayment;

public:
    TrafficManagementSystem() //   Constructor
    {
        totalChallanPayment = 0;
    }

    // Register Vehicle Function
    void registerVehicle(string regNumber, string ownerName, string vehicleType, string entryDate)
    {
        // Check if a vehicle with the same registration number and entry date already exists
        bool vehicleExists = false;
        for (int i = 0; i < numVehicles; ++i)
        {
            if (vehicles[i].getRegistrationNumber() == regNumber && vehicles[i].getEntryDate() == entryDate)
            {
                vehicleExists = true;
                break;
            }
        }

        if (vehicleExists)
        {
            cout << "\n\t\t\t\t\tVehicle with the same registration number and entry date already exists.\n";
        }
        else
        {
            // If no matching vehicle is found, add the new vehicle
            if (numVehicles < 100) // Ensure we don't exceed the maximum number of vehicles
            {
                vehicles[numVehicles] = Vehicle(regNumber, ownerName, vehicleType);
                vehicles[numVehicles].setEntryDate(entryDate); // Set the entry date
                numVehicles++;
                cout << "\n\t\t\t\t\tVehicle registration successful.\n";
            }
            else
            {
                cout << "\n\t\t\t\t\tMaximum number of vehicles reached. Cannot register more vehicles.\n";
            }
        }
    }

    // Issuance of challan Function
    void issueChallan(string regNumber, string entryDate)
    {
        bool found = false;
        for (int i = 0; i < numVehicles; ++i)
        {
            if (vehicles[i].getRegistrationNumber() == regNumber && vehicles[i].getEntryDate() == entryDate)
            {
                found = true;
                if (!vehicles[i].hasChallan())
                {
                    string rule;
                    int payment;
                    cout << endl
                         << "\t\t\t\t\tEnter Rule Break: ";
                    getline(cin, rule);
                    cout << endl
                         << "\t\t\t\t\tEnter Challan Payment: ";
                    cin >> payment;
                    cin.ignore();

                    vehicles[i].setChallanDetails(rule, payment);
                    totalChallanPayment += payment;
                    cout << "\n\t\t\t\t\tChallan issued successfully.\n";
                }
                else
                {
                    cout << "\n\t\t\t\t\tVehicle already has a challan.\n";
                }
            }
        }

        if (!found)
        {
            cout << "\n\t\t\t\t\tVehicle not found or entry date mismatch.\n";
        }
    }

    // Display Violation History of Vehicles
    void displayViolationRecordsByDateAndType(string regNumber, string ownerName, string vehicleType, string entryDate)
    {

        bool found = false;
        for (int i = 0; i < numVehicles; ++i)
        {
            if (vehicles[i].getRegistrationNumber() == regNumber && vehicles[i].getOwnerName() == ownerName && vehicles[i].getVehicleType() == vehicleType && vehicles[i].getEntryDate() == entryDate)
            {
                cout << "\n\t\t\t\t\tViolation Records for Given Data is\n\n";
                found = true;
                cout << "\t\t\t\t\tReg No: " << vehicles[i].getRegistrationNumber() << "\n";
                cout << "\t\t\t\t\tOwner : " << vehicles[i].getOwnerName() << "\n";
                cout << "\t\t\t\t\tType  : " << vehicles[i].getVehicleType() << "\n";
                vehicles[i].cDeatils();

                if (vehicles[i].hasChallan())
                {
                    vehicles[i].displayChallanDetails();
                    cout << "\t\t\t\t\tPayment Status     : " << vehicles[i].getPaymentStatus() << "\n";
                }
            }
        }
        if (!found)
        {
            cout << "\n\t\t\t\t\tNo records found for the given date.....\n";
        }
    }
    // Payment portal Function
    void paymentPortal(string regNumber, string entryDate)
    {
        bool found = false;
        for (int i = 0; i < numVehicles; ++i)
        {
            if (vehicles[i].getRegistrationNumber() == regNumber && vehicles[i].getEntryDate() == entryDate)
            {
                found = true;
                if (vehicles[i].hasChallan())
                {
                    cout << "\n\t\t\t\t\tChallan Details:\n";
                    vehicles[i].displayChallanDetails();
                    cout << "\t\t\t\t\tPayment Status     : " << vehicles[i].getPaymentStatus() << "\n";
                    cout << endl
                         << "\t\t\t\t\tEnter Payment Amount: pkr ";
                    int paymentAmount;
                    cin >> paymentAmount;
                    if (paymentAmount >= vehicles[i].getChallanPayment())
                    {
                        int change = paymentAmount - vehicles[i].getChallanPayment();
                        vehicles[i].setChallaned(false);
                        cout << "\n\t\t\t\t\tPayment successful.\n";
                        if (change > 0)
                        {
                            cout << endl
                                 << "\t\t\t\t\tChange: pkr " << change << "\n";
                        }
                    }
                    else
                    {
                        cout << endl
                             << "\t\t\t\t\tInsufficient payment amount.\n";
                    }
                }
                else
                {
                    cout << "\n\t\t\t\t\tNo pending challan for this vehicle.\n";
                }
            }
        }

        if (!found)
        {
            cout << "\n\t\t\t\t\tVehicle not found or entry date mismatch.\n";
        }
    }

    // List of Violation Category function
    void trafficViolationCategories()
    {

        // traffic violation categories here
        cout << "\t\t\t\t\tTraffic Violation Categories And Rates:\n"
             << endl;
        cout << "\t\t\t\t\t1. Over Speeding         |        300  pkr\n";
        cout << "\t\t\t\t\t2. Red Light Violation   |        250  pkr\n";
        cout << "\t\t\t\t\t3. Illegal Parking       |        500  pkr\n";
        cout << "\t\t\t\t\t4. No Helmit Wearing     |        200  pkr\n";
        cout << "\t\t\t\t\t5. No Documents          |        1000 pkr\n";
        cout << "\t\t\t\t\t6. Illegal Smuggling     |        1500 pkr\n";
    }
    // Display All vehicles functions
    void displayAllVehicles()
    {
        cout << "\n\n";
        cout << "\t\t\t\t\t+-----------------+-----------------+--------------+--------------+" << endl;
        cout << "\t\t\t\t\t| Registration No | Owner Name       | Vehicle Type|  Entry Date  |" << endl;
        cout << "\t\t\t\t\t+-----------------+-----------------+--------------+--------------+" << endl;

        if (numVehicles <= 0)
        {
            cout << "\t\t\t\t\tNoo Vehicles Kindly add Vehicles first.......\n";
        }
        else
        {
            for (int i = 0; i < numVehicles; ++i)
            {
                cout << "\t\t\t\t\t|" << setw(17) << left << vehicles[i].getRegistrationNumber()
                     << "|" << setw(18) << left << vehicles[i].getOwnerName() << "|" << setw(13) << left << vehicles[i].getVehicleType();
                cout << "|" << setw(14) << left << vehicles[i].getEntryDate() << "|\n";
                cout << "\t\t\t\t\t+------------------+------------------+--------------+------------+" << endl;
            }
        }
    }
    // Search Vehicles Function
    void searchVehicle(string regNumber, string entryDate)
    {
        cout << "\n\n";
        cout << "\t\t\t\t\t+-----------------+-----------------+--------------+--------------+" << endl;
        cout << "\t\t\t\t\t| Registration No | Owner Name       | Vehicle Type|  Entry Date  |" << endl;
        cout << "\t\t\t\t\t+-----------------+-----------------+--------------+--------------+" << endl;
        bool found = false;
        for (int i = 0; i < numVehicles; ++i)
        {
            if (vehicles[i].getRegistrationNumber() == regNumber && vehicles[i].getEntryDate() == entryDate)
            {
                cout << "\t\t\t\t\t|" << setw(17) << left << vehicles[i].getRegistrationNumber()
                     << "|" << setw(18) << left << vehicles[i].getOwnerName() << "|" << setw(13) << left << vehicles[i].getVehicleType();
                cout << "|" << setw(14) << left << vehicles[i].getEntryDate() << "|\n";
                cout << "\t\t\t\t\t+------------------+------------------+--------------+------------+" << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "\t\t\t\t\tVehicle not found.\n";
        }
    }
    // Delete Vehicles Function
    void deleteVehicle(string regNumber, string entryDate)
    {

        for (int i = 0; i < numVehicles; ++i)
        {
            if (vehicles[i].getRegistrationNumber() == regNumber && vehicles[i].getEntryDate() == entryDate)
            {
                vehicles[i] = vehicles[numVehicles - 1];
                numVehicles--;
                cout << "\n\t\t\t\t\tVehicle deleted successfully.\n";
                return;
            }
        }
        cout << "\n\t\t\t\t\tVehicle not found.\n";
    }
    // Update Vehicles Function
    void updateVehicle(string regNumber, string entryDate)
    {
        bool found = false;
        for (int i = 0; i < numVehicles; ++i)
        {
            if (vehicles[i].getRegistrationNumber() == regNumber && vehicles[i].getEntryDate() == entryDate)
            {
                found = true;
                string newRegNumber, newOwnerName, newVehicleType;

                cout << endl
                     << "\t\t\t\t\tEnter new Registration No: ";
                getline(cin, newRegNumber);

                cout << endl
                     << "\t\t\t\t\tEnter new Owner Name: ";
                getline(cin, newOwnerName);

                cout << endl
                     << "\t\t\t\t\tEnter new Vehicle Type: ";
                getline(cin, newVehicleType);

                vehicles[i].setRegNumber(newRegNumber);
                vehicles[i].setOwnerName(newOwnerName);
                vehicles[i].setVehicleType(newVehicleType);

                cout << "\n\t\t\t\t\tVehicle information updated successfully.\n";
            }
        }

        if (!found)
        {
            cout << "\n\t\t\t\t\tVehicle not found or entry date mismatch.\n";
        }
    }

    // Show total challaned Payment History
    int getTotalChallanPayment()
    {

        return totalChallanPayment;
    }
}; // End of class

// Login_sign_on_Menu() fun
void login_sign_in_Menu()
{
    login l1;         // object of class login
    l1.clearScreen(); // for clear consloe
    int choice;
    do
    {
        banner2();
        cout << "\t\t\t\t\t1. Sign up\n";
        cout << "\t\t\t\t\t2. Log in\n";
        cout << "\t\t\t\t\t3. Update Info\n";
        cout << "\t\t\t\t\t4. Exit\n"
             << endl;
        cout << "\t\t\t\t\tEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            l1.clearScreen();
            banner2();
            cout << "\t\t\t\t\tKindly Sign up your self\n\n";
            l1.signUp();
            break;
        case 2:
            l1.clearScreen();
            banner2();
            cout << "\t\t\t\t\tNow Login your self\n\n";
            l1.logins();
            break;
        case 3:
            l1.clearScreen();
            banner2();
            cout << "\t\t\t\t\tNow Update your Login Info\n\n";
            l1.updateUser();
            break;
        case 4:
            l1.clearScreen();
            cout << "Exiting th system...\n";
            break;
        default:
            cout << "\n\t\t\t\t\tInvalid choice. Please try again.\n";
            cout << "\t\t\t\t\twait for 2 sec ";
            Sleep(2000);
            system("cls");
        }
    } while (choice != 4);
} // End login_sign_in_Menu() fun

// Main Menu() Fun
void main_Menu()
{
    TrafficManagementSystem tms; // tms is the object of class TrafficManagmentSystem

    while (true) // Infinite Loop
    {
        banner(); // Call Banner function for display Headings

        cout << "\t\t\t\t\tMain Menu:\n"
             << endl;
        cout << "\t\t\t\t\t1.  Vehicle Registration\n";
        cout << "\t\t\t\t\t2.  Challan Issuance\n";
        cout << "\t\t\t\t\t3.  Violation Records\n";
        cout << "\t\t\t\t\t4.  Payment Portal\n";
        cout << "\t\t\t\t\t5.  Traffic Violation Categories\n";
        cout << "\t\t\t\t\t6.  Show all vehicles\n";
        cout << "\t\t\t\t\t7.  Search Vehicle\n";
        cout << "\t\t\t\t\t8.  Delete Vehicle\n";
        cout << "\t\t\t\t\t9.  Update Vehicle\n";
        cout << "\t\t\t\t\t10. Total Challan Payment\n";
        cout << "\t\t\t\t\t11. Logout\n"
             << endl;

        int choice;
        cout << "\t\t\t\t\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            banner();
            string regNumber, ownerName, vehicleType, entryDate;
            cout << "\t\t\t\t\tVehicle Registration Page: \n\n";
            cout << "\t\t\t\t\tEnter Vehicle Registration Number: ";
            cin.ignore();
            cin >> regNumber;
            cout << endl
                 << "\t\t\t\t\tEnter Owner Name: ";
            cin.ignore();
            getline(cin, ownerName);
            cout << endl
                 << "\t\t\t\t\tEnter Vehicle Type: ";
            getline(cin, vehicleType);
            cout << endl
                 << "\t\t\t\t\tEnter Date (dd/mm/yyyy): ";
            getline(cin, entryDate);
            tms.registerVehicle(regNumber, ownerName, vehicleType, entryDate);
        }
        else if (choice == 2)
        {
            banner();
            cout << "\t\t\t\t\tVehicle Challan Issuance Page: \n\n";
            string regNumber, entryDate;
            cout << "\t\t\t\t\tEnter Vehicle Registration Number: ";
            cin >> regNumber;
            cout << "\n\t\t\t\t\tEnter Challan Issue Date (yyyy-mm-dd): ";
            cin.ignore();
            getline(cin, entryDate);
            tms.issueChallan(regNumber, entryDate);
        }
        else if (choice == 3)
        {
            banner();
            cout << "\t\t\t\t\tViolation Record Page: \n\n";
            string regNumber, ownerName, vehicleType, entryDate;
            cout << "\t\t\t\t\tEnter Registration Number: ";
            cin.ignore();
            getline(cin, regNumber);
            cout << endl
                 << "\t\t\t\t\tEnter Owner Name: ";
            getline(cin, ownerName);
            cout << endl
                 << "\t\t\t\t\tEnter Vehicle Type: ";
            getline(cin, vehicleType);
            cout << endl
                 << "\t\t\t\t\tEnter Date (dd/mm/yyyy): ";
            getline(cin, entryDate);
            tms.displayViolationRecordsByDateAndType(regNumber, ownerName, vehicleType, entryDate);
        }
        else if (choice == 4)
        {
            banner();
            cout << "\t\t\t\t\tPayment Portal Page: \n\n";
            string regNumber, entryDate;
            cout << "\t\t\t\t\tEnter Vehicle Registration Number: ";
            cin >> regNumber;
            cout << "\n\t\t\t\t\tEnter Challan Issue Date (yyyy-mm-dd): ";
            cin.ignore();
            getline(cin, entryDate);
            tms.paymentPortal(regNumber, entryDate);
        }
        else if (choice == 5)
        {
            banner();
            cout << "\t\t\t\t\tTraffic Violation Categories Page: \n\n";
            tms.trafficViolationCategories();
        }
        else if (choice == 6)
        {
            banner();
            tms.displayAllVehicles();
        }
        else if (choice == 7)
        {
            banner();
            cout << "\t\t\t\t\tVehicle Search Page: \n\n";
            string regNumber, entryDate;
            cout << "\t\t\t\t\tEnter Vehicle Registration Number: ";
            cin >> regNumber;
            cout << endl
                 << "\t\t\t\t\tEnter Entry Date (dd/mm/yyyy): ";
            cin.ignore();
            getline(cin, entryDate);
            tms.searchVehicle(regNumber, entryDate);
        }
        else if (choice == 8)
        {
            banner();
            cout << "\t\t\t\t\tVehicle Deletation Page: \n\n";
            string regNumber, entryDate;
            cout << "\t\t\t\t\tEnter Vehicle Registration Number: ";
            cin >> regNumber;
            cout << endl
                 << "\t\t\t\t\tEnter Entry Date (dd/mm/yyyy): ";
            cin.ignore();
            getline(cin, entryDate);
            tms.deleteVehicle(regNumber, entryDate);
        }

        else if (choice == 9)
        {
            banner();
            cout << "\t\t\t\t\tVehicle Update Page: \n\n";
            string regNumber, entryDate;
            cout << "\t\t\t\t\tEnter Vehicle Registration Number: ";
            cin >> regNumber;
            cout << "\n\t\t\t\t\tEnter Challan Issue Date (yyyy-mm-dd): ";
            cin.ignore();
            getline(cin, entryDate);
            tms.updateVehicle(regNumber, entryDate);
        }

        else if (choice == 10)
        {
            banner();
            cout << "\t\t\t\t\tTotal Challan Payment Page: \n\n";
            cout << "\t\t\t\t\tTotal Challan Payment: pkr " << tms.getTotalChallanPayment() << "\n";
        }
        else if (choice == 11)
        {
            system("cls");
            cout << "\n\n\n\n\n\n";
            cout << "\t\t\t\t\t\tLogged out successfully.\n"
                 << endl;
            cout << "\t\t\t\t\t\twait for 2 sec ";
            Sleep(2000);
            system("cls");
            break;
        }
        else
        {
            cout << endl
                 << "\t\t\t\t\tInvalid choice. Please try again.\n";
        }
        cout << "\n\t\t\t\t\tPress Enter to continue...";
        getch();
    }
} // End of Main Menu() Fun

// Main Function Entery point of the project
int main()
{
    system("Color 05"); // change console color
    login_sign_in_Menu();

    return 0;
}
// End of project
