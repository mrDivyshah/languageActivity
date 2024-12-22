#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include "../pwd.cpp"

using namespace std;

#define USER_DATABASE getCurrentDirectory() + "/database/user.txt"
#define STATUS_DATABASE getCurrentDirectory() + "/database/status.txt"

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

string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream date;
    date << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
    return date.str();
}

int getNextUserId()
{
    ifstream file(USER_DATABASE);
    string line;
    int id = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;
        ss >> id; // Read the last ID from the file
    }
    return id + 1; // Increment ID for the new user
}
// Function to display all users
void displayUsers()
{
    fstream file(USER_DATABASE, ios::in);
    int id;
    string joiningDate, name;

    if (file.is_open())
    {
        cout << "Users in the database:\n";
        while (file >> id >> joiningDate >> name)
        {
            // Display the user information
            cout << "ID: " << id << ", Name: " << name << ", Joining Date: " << joiningDate << endl;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file.\n";
    }
}

bool validateUser(const string &name, const string &password)
{
    ifstream file(USER_DATABASE);
    string line;

    // Loop through each line in the file
    while (getline(file, line))
    {
        stringstream ss(line);
        int id;
        string joiningDate;
        string existingName, existingPassword;

        // Read the data from the line
        ss >> id;
        getline(ss, joiningDate, ',');      // Get joiningDate
        getline(ss, existingName, ',');     // Get name
        getline(ss, existingPassword, ','); // Get password

        // Trim leading whitespace for name
        existingName.erase(0, existingName.find_first_not_of(' '));

        // Compare name and password
        if (existingName == name && existingPassword == password)
        {
            return true; // User and password match
        }
    }

    return false; // No matching user or incorrect password
}

bool userExists(const string &name)
{
    ifstream file(USER_DATABASE);
    string line;

    // Loop through each line in the file
    while (getline(file, line))
    {
        stringstream ss(line);
        int id;
        string joiningDate;
        string existingName, password;

        // Read the data from the line
        ss >> id;

        // Read the remaining line as existingName (to capture full name)
        getline(ss, joiningDate, ',');  // Get joiningDate
        getline(ss, existingName, ','); // Get name
        getline(ss, password, ',');     // Get password

        // Trim leading whitespace
        existingName.erase(0, existingName.find_first_not_of(' '));

        // Compare full names
        if (existingName == name)
        {
            return true; // User found
        }
    }
    return false; // User not found
}

bool updateUser(int searchId, const User &updatedUser)
{
    ifstream file(USER_DATABASE);
    vector<User> users;
    bool found = false;

    if (!file.is_open())
    {
        cout << "Unable to open file.\n";
        return false;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, joiningDate, name, password;

        // Read comma-separated values
        getline(ss, idStr, ',');
        getline(ss, joiningDate, ',');
        getline(ss, name, ',');
        getline(ss, password, ',');

        int id = stoi(idStr);

        if (id == searchId)
        {
            found = true;
            users.push_back(updatedUser); // Replace with updated user
        }
        else
        {
            users.push_back({id, joiningDate, name, password});
        }
    }
    file.close();

    if (found)
    {
        // Write updated users back to the file
        ofstream outFile(USER_DATABASE, ios::trunc);
        for (const auto &user : users)
        {
            outFile << user.id << "," << user.joiningDate << "," << user.name << "," << user.password << endl;
        }
        outFile.close();
        return true;
    }
    else
    {
        cout << "User not found.\n";
        return false;
    }
}

// Function to add a new user
User addUser(string name, const string password)
{
    User userData = {-1, " ", " ", " "}; // Default userData initialization
    try
    {
        fstream file(USER_DATABASE, ios::app);
        if (!file.is_open())
        {
                throw runtime_error("Unable to open file."); // Explicitly throw an exception
        }

        // Trim leading whitespace from the name
        name.erase(0, name.find_first_not_of(' '));

        // Generate user ID and joining date
        int id = getNextUserId();
        string joiningDate = getCurrentDate();

        // Write data to the file
        file << id << "," << joiningDate << "," << name << "," << password << endl;
        file.close();

        // Populate the userData object
        userData.id = id;
        userData.joiningDate = joiningDate;
        userData.name = name;
        userData.password = password;

        return userData;
    }
    catch (const exception &e) 
    {
        cout << "An error occurred: " << e.what() << endl;
    }
    catch (...) 
    {
        cout << "An unknown error occurred." << endl;
    }

    return userData; 
}

vector<string> AllAvailableUsers()
{
    vector<string> userName;
    string line, str, name, password;
    fstream file(USER_DATABASE, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, str, ',');
            getline(ss, str, ',');
            getline(ss, name, ',');
            getline(ss, password);
            name.erase(0, name.find_first_not_of(' '));
            if (!name.empty())
            {
                userName.push_back(name);
            }
        }
    }
    else
    {
        return {};
    }
    file.close();
    return userName;
}

int getUserCount()
{
    int count = 0;
    for (string user : AllAvailableUsers())
    {
        if (!user.empty())
        {
            count++;
        }
        else
        {
            return 0;
        }
    }
    return count - 1;
}

User userDataUsingUserIndex(int U_ID)
{
    ifstream file(USER_DATABASE);
    string line;
    int index = 0;
    string name, joiningDate, id, password;

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
            if (index == U_ID)
            {
                userData.id = stoi(id);
                userData.joiningDate = joiningDate;
                userData.name = name;
                userData.password = password;
                return userData;
            }
            index++;
        }
        file.close();
    }
    return userData;
}

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
                userData.id = stoi(id);
                userData.joiningDate = joiningDate;
                userData.name = name;
                userData.password = password;
                return userData;
            }
        }
        file.close();
    }
    return userData;
}

Status addStatus(int id, string name, int level)
{
    fstream file(STATUS_DATABASE, ios::app);
    name.erase(0, name.find_first_not_of(' '));
    Status statusData = {-1, " ", " ", -1};
    if (file.is_open())
    {
        string Date = getCurrentDate();
        file << id << "," << Date << "," << name << "," << level << endl;
        file.close();
        statusData.id = id;
        statusData.timeStamp = Date;
        statusData.name = name;
        statusData.level = level;
        return statusData;
    }
    else
    {
        cout << "Unable to open file.\n";
    }
    return statusData;
}