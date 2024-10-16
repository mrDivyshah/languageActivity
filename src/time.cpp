#include<iostream>
#include <ctime>
#include <thread>  // For sleep_for()
#include <chrono>  // For chrono::seconds

using namespace std;


void liveTime(int row, int col) {
    while (true) {
        // Get current time
        time_t now = time(0);
        tm *local_time = localtime(&now);

        // Save the current cursor position using ANSI escape codes
        cout << "\033[s";  // Save cursor position

        // Move the cursor to the desired position for time display
        cout << "\033[" << row << ";" << col << "H";  // Move cursor to row and col

        // Clear the current line before printing new time (optional)
        // cout << "\033[K";

        // Display formatted date and time
        cout << "Current Date and Time: ";
        cout << 1900 + local_time->tm_year << "-"  // Year
             << 1 + local_time->tm_mon << "-"     // Month
             << local_time->tm_mday << " "        // Day
             << local_time->tm_hour << ":"        // Hours
             << local_time->tm_min << ":"         // Minutes
             << local_time->tm_sec << flush;      // Seconds

        // Restore the original cursor position using ANSI escape codes
        cout << "\033[u";  // Restore cursor position

        // Sleep for 1 second
        this_thread::sleep_for(chrono::seconds(1));
    }
}

string getTime()
{
    // Get current time
    time_t now = time(0);
    tm *local_time = localtime(&now);

    // Construct the date and time string using to_string() for integer to string conversion
    string dateAndTime = to_string(local_time->tm_mday) + "-" +
                         to_string(1 + local_time->tm_mon) + "-" +
                         to_string(1900 + local_time->tm_year) + " " +
                         to_string(local_time->tm_hour) + ":" +
                         to_string(local_time->tm_min) + ":" +
                         to_string(local_time->tm_sec);

    return dateAndTime;
}
