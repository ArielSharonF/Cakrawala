#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

#include <iostream>

using namespace std;

class Utilities {
    public:
        static void clearScreen();
        static void printCenteredTitle(const string& title, int width);
        static void pressAnyKeyToContinue(const string& customMessage);
};

#endif