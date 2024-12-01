#include<iostream>
#include <ctime>
#include <thread>  // For sleep_for()
#include <chrono>  // For chrono::seconds
#include <sstream> 

using namespace std;



string getTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" 
       << 1 + ltm->tm_mon << "-" 
       << ltm->tm_mday << " "
       << 1 + ltm->tm_hour << ":"
       << 1 + ltm->tm_min << ":"
       << 1 + ltm->tm_sec;
       
    return ss.str();
}
