#include <iostream>
#include <windows.h>

using namespace std;

string getCurrentDirectory() {
    char buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer);
    return string(buffer);
}