#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip> // For setw

using namespace std;

// File paths
#define USER_DATABASE "../../database/user.txt"
#define STATUS_DATABASE "../../database/status.txt"

// Color definitions using ANSI escape codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"


// Structs for User and Status
struct User
{
    int id;
    string joiningDate;
    string name;
    string password;
};

struct Status
{
    int id;
    string timeStamp;
    string name;
    int level;
};

// Utility function to get the current date
string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream date;
    date << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
    return date.str();
}

// Function to get the next user ID
int getNextUserId()
{
    ifstream file(USER_DATABASE);
    string line;
    int id = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> id; // Read the last ID from the file
    }
    return id + 1; // Increment ID for the new user
}

    



 // For stringstream

void displayUsers()
{
    fstream file(USER_DATABASE, ios::in);
    string line;

    if (file.is_open())
    {
        cout << CYAN << "\n+------------+--------------------+--------------------+" << RESET << "\n";
        cout << CYAN << "| " << BOLD << setw(10) << "ID" << RESET
             << CYAN << " | " << BOLD << setw(18) << "Name" << RESET
             << CYAN << " | " << BOLD << setw(18) << "Joining Date" << RESET << CYAN << " |" << "\n";
        cout << CYAN << "+------------+--------------------+--------------------+" << RESET << "\n";

        bool hasUsers = false;

        while (getline(file, line))
        {
            hasUsers = true;

            stringstream ss(line);
            string id, name, joiningDate;

            // Split by comma
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, joiningDate, ',');

            // Display data
            cout << CYAN << "| " << RESET << setw(10) << id
                 << CYAN << " | " << RESET << setw(18) << name
                 << CYAN << " | " << RESET << setw(18) << joiningDate
                 << CYAN << " |" << RESET << "\n";
        }

        if (!hasUsers)
        {
            cout << CYAN << "| " << RESET << setw(52) << "No users found!" << CYAN << " |" << RESET << "\n";
        }

        cout << CYAN << "+------------+--------------------+--------------------+" << RESET << "\n";

        file.close();
    }
    else
    {
        cout << RED << "Unable to open file.\n" << RESET;
    }
}

// Function to validate a user
bool validateUser(const string &name, const string &password)
{
    ifstream file(USER_DATABASE);
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        int id;
        string joiningDate, existingName, existingPassword;

        ss >> id;
        getline(ss, joiningDate, ',');
        getline(ss, existingName, ',');
        getline(ss, existingPassword, ',');

        existingName.erase(0, existingName.find_first_not_of(' '));

        if (existingName == name && existingPassword == password)
        {
            return true;
        }
    }
    return false;
}

// Function to check if a user exists
bool userExists(const string &name)
{
    ifstream file(USER_DATABASE);
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        int id;
        string joiningDate, existingName, password;

        ss >> id;
        getline(ss, joiningDate, ',');
        getline(ss, existingName, ',');
        getline(ss, password, ',');

        existingName.erase(0, existingName.find_first_not_of(' '));

        if (existingName == name)
        {
            return true;
        }
    }
    return false;
}

// Function to update user information
void updateUser(const string &searchName)
{
    ifstream file(USER_DATABASE); // Open the file for reading
    vector<User> users;           // To hold all user records
    bool found = false;           // Flag to check if the user was found

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            User user;
            string id, joiningDate, name, password;

            // Parse the CSV line
            getline(ss, id, ',');
            getline(ss, joiningDate, ',');
            getline(ss, name, ',');
            getline(ss, password);

            // Remove leading spaces from the name
            name.erase(0, name.find_first_not_of(' '));

            // Check if the current record matches the search name
            if (name == searchName)
            {
                found = true;

                // Ask for new details
                cout << "Enter new name: ";
                getline(cin, name);
                cout << "Enter new password: ";
                getline(cin, password);

                // Update the user details
                user = {stoi(id), joiningDate, name, password};
            }
            else
            {
                user = {stoi(id), joiningDate, name, password};
            }

            users.push_back(user);
        }
        file.close();

        if (found)
        {
            ofstream outFile(USER_DATABASE, ios::trunc); // Open the file for overwriting

            for (const auto &user : users)
            {
                outFile << user.id << "," << user.joiningDate << "," << user.name << "," << user.password << endl;
            }

            outFile.close();
            cout << GREEN << "User updated successfully.\n" << RESET;
        }
        else
        {
            cout << RED << "User not found.\n" << RESET;
        }
    }
    else
    {
        cout << RED << "Unable to open file.\n" << RESET;
    }
}


// Function to update user information
//void updateUser(const string &searchName)
// {
//     ifstream file(USER_DATABASE);
//     vector<User> users;
//     int id;
//     string joiningDate, name;
//     bool found = false;

//     if (file.is_open())
//     {
//         while (file >> id >> joiningDate >> name)
//         {
//             if (name == searchName)
//             {
//                 found = true;
//             }
//             users.push_back({id, joiningDate, name});
//         }
//         file.close();

//         if (found)
//         {
//             ofstream outFile(USER_DATABASE, ios::trunc);
//             for (const auto &user : users)
//             {
//                 outFile << user.id << "," << user.joiningDate << "," << user.name << endl;
//             }
//             outFile.close();
//             cout << GREEN << "User updated successfully.\n"
//                  << RESET;
//         }
//         else
//         {
//             cout << RED << "User not found.\n"
//                  << RESET;
//         }
//     }
//     else
//     {
//         cout << RED << "Unable to open file.\n"
//              << RESET;
//     }
// }

// Function to add a new user
User addUser(string name, const string password)
{
    fstream file(USER_DATABASE, ios::app);
    name.erase(0, name.find_first_not_of(' '));
    User userData = {-1, " ", " ", " "};
    if (file.is_open())
    {
        int id = getNextUserId();
        string joiningDate = getCurrentDate();
        file << id << "," << joiningDate << "," << name << "," << password << endl;
        file.close();
        userData = {id, joiningDate, name, password};
    }
    else
    {
        cout << RED << "Unable to open file.\n"
             << RESET;
    }
    return userData;
}

// Function to search for a user by name
User searchUser(const string searchName)
{
    ifstream file(USER_DATABASE);
    string line;
    string name, joiningDate, password, id;

    User userData = {-1, "", "", ""};

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, joiningDate, ',');
            getline(ss, name, ',');
            getline(ss, password);
            name.erase(0, name.find_first_not_of(' '));
            if (name == searchName)
            {
                userData = {stoi(id), joiningDate, name, password};
                return userData;
            }
        }
        file.close();
    }
    return userData;
}

// Function to print user details in a box
void printUserDetailsBox(const User &user)
{
    int boxWidth = 50;
    stringstream userDetails;
    userDetails << MAGENTA << "User found:\n"
                << RESET;
    userDetails << "ID: " << user.id << "\n";
    userDetails << "Name: " << user.name << "\n";
    userDetails << "Joining Date: " << user.joiningDate << "\n";

    string details = userDetails.str();
    cout << GREEN << string(boxWidth, '*') << "\n"
         << RESET;
    istringstream iss(details);
    string line;

    while (getline(iss, line))
    {
        cout << GREEN << "* " << left << setw(boxWidth - 3) << line << "*\n"
             << RESET;
    }
    cout << GREEN << string(boxWidth, '*') << "\n"
         << RESET;
}
// Function to add a new status
Status addStatus(int id, string name, int level)
{
    fstream file(STATUS_DATABASE, ios::app);
    name.erase(0, name.find_first_not_of(' '));
    Status statusData = {-1, " ", " ", -1};
    if (file.is_open())
    {
        string date = getCurrentDate();
        file << id << "," << date << "," << name << "," << level << endl;
        file.close();
        statusData = {id, date, name, level};
    }
    else
    {
        cout << "Unable to open file.\n";
    }
    return statusData;
}

// Menu display
void displayMenu()
{
    cout << BOLD << BLUE << "\n=== Admin Panel Of WordWise ===\n"
         << RESET;
    cout << YELLOW << "1. Add User\n";
    cout << "2. Display All Users\n";
    cout << "3. Update User\n";
    cout << "4. Add Status\n";
    cout << "5. Search User\n";
    cout << "6. Exit\n"
         << RESET;
    cout << GREEN << "Enter your choice: " << RESET;
}

// Admin Panel Logic
void adminPanel()
{
    while (true)
    {
        int choice;
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            string name, password;
            cout << "Enter user name: ";
            getline(cin, name);
            cout << "Enter password: ";
            getline(cin, password);

            if (userExists(name))
            {
                cout << RED << "User already exists!\n"
                     << RESET;
            }
            else
            {
                User newUser = addUser(name, password);
                if (newUser.id != -1)
                {
                    cout << GREEN << "User added successfully! ID: " << newUser.id << "\n"
                         << RESET;
                }
            }
            
        }
        else if (choice == 2)
        {
            displayUsers();
            
        }
        else if (choice == 3)
        {
            string name;
            cout << "Enter the name of the user to update: ";
            getline(cin, name);
            updateUser(name);
            
        }
        else if (choice == 4)
        {
            int id, level;
            string name;
            cout << "Enter user ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter user name: ";
            getline(cin, name);
            cout << "Enter user level: ";
            cin >> level;

            addStatus(id, name, level);
            
        }
        else if (choice == 5)
        {
            string name;
            cout << "Enter the name of the user to search: ";
            getline(cin, name);
            User user = searchUser(name);
            if (user.id != -1)
            {
                printUserDetailsBox(user);
            }
            else
            {
                cout << RED << "User not found.\n"
                     << RESET;
            }
            
        }
        else if (choice == 6)
        {
                 cout << GREEN << "Exiting admin panel...\n"
                 << RESET;
                break;
        }
           
        else
        {
                cout << RED << "Invalid choice. Please try again.\n"
                 << RESET;
                 break;
        }
            

        }
    } 


// Main Function
int main()
{
    adminPanel();
    return 0;
}
