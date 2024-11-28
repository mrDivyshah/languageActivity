#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>

void AdmindisplayUsers()
{
    fstream file(USER_DATABASE, ios::in);
    string line;

    if (file.is_open())
    {
        cout << Color_Cyan << "\n+------------+--------------------+--------------------+" << Color_Reset << "\n";
        cout << Color_Cyan << "| " << setw(10) << "ID" << Color_Reset
             << Color_Cyan << " | " << setw(18) << "Name" << Color_Reset
             << Color_Cyan << " | " << setw(18) << "Joining Date" << Color_Reset << Color_Cyan << " |" << "\n";
        cout << Color_Cyan << "+------------+--------------------+--------------------+" << Color_Reset << "\n";

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
            cout << Color_Cyan << "| " << Color_Reset << setw(10) << id
                 << Color_Cyan << " | " << Color_Reset << setw(18) << name
                 << Color_Cyan << " | " << Color_Reset << setw(18) << joiningDate
                 << Color_Cyan << " |" << Color_Reset << "\n";
        }

        if (!hasUsers)
        {
            cout << Color_Cyan << "| " << Color_Reset << setw(52) << "No users found!" << Color_Cyan << " |" << Color_Reset << "\n";
        }

        cout << Color_Cyan << "+------------+--------------------+--------------------+" << Color_Reset << "\n";

        file.close();
    }
    else
    {
        cout << Color_Red << "Unable to open file.\n"
             << Color_Reset;
    }
}

void printUserDetailsBox(const User &user)
{
    // Gather user details
    cout << "\n";
    stringstream userDetails;
    userDetails << "User found:\n";
    userDetails << "ID: " << user.id << "\n";
    userDetails << "Name: " << user.name << "\n";
    userDetails << "Joining Date: " << user.joiningDate << "\n";

    // Extract details as a string and determine the maximum line width
    string details = userDetails.str();
    istringstream iss(details);
    string line;
    size_t maxLineWidth = 0;

    while (getline(iss, line))
    {
        maxLineWidth = max(maxLineWidth, line.length());
    }

    // Add padding for aesthetics
    size_t boxWidth = maxLineWidth + 4;

    // Reset the stringstream to read the lines again
    iss.clear();
    iss.seekg(0, ios::beg);

    // Print the top border
    cout << Color_Green << string(boxWidth, '*') << "\n"
         << Color_Reset;

    // Print each line with padding
    while (getline(iss, line))
    {
        cout << Color_Green << "* " << left << setw(maxLineWidth) << line << " *\n"
             << Color_Reset;
    }

    // Print the bottom border
    cout << Color_Green << string(boxWidth, '*') << "\n"
         << Color_Reset;
}

void displayMenu()
{
    cout << Color_Blue << "\n=== Admin Panel Of WordWise ===\n"
         << Color_Reset;
    cout << Color_Yellow;
    cout << "1. Display All Users\n";
    cout << "2. Update User\n";
    cout << "3. Search User\n";
    cout << "4. Exit\n"
         << Color_Reset;
    cout << Color_Green << "Enter your choice: " << Color_Reset;
}
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
            AdmindisplayUsers();
        }
        else if (choice == 2)
        {
            string name;
            cout << "Enter the name of the user to update: ";
            getline(cin, name);
            updateUser(name);
        }
        else if (choice == 3)
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
                cout << Color_Red << "User not found.\n"
                     << Color_Reset;
            }
        }
        else if (choice == 4)
        {
            cout << Color_Green << "Exiting admin panel...\n"
                 << Color_Reset;
            system("cls");
            break;
        }

        else
        {
            cout << Color_Red << "Invalid choice. Please try again.\n"
                 << Color_Reset;
            break;
        }
    }
}
