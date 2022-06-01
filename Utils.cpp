#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include "Utils.h"
#include "Time.h"
using namespace std;
namespace sdds
{
    bool debug = false;
    int getTime() {
        int mins = -1;
        if (debug) {
            Time t(0);
            cout << "Enter current time: ";
            do {
                cin.clear();
                cin >> t;   // needs extraction operator overloaded for Time
                if (!cin) {
                    cout << "Invlid time, try agian (HH:MM): ";
                    cin.clear();
                }
                else {
                    mins = int(t);
                }
                cin.ignore(1000, '\n');
            } while (mins < 0);
        }
        else {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            mins = lt.tm_hour * 60 + lt.tm_min;
        }
        return mins;
    }

    int getInt() {
        string inputStr;
        bool isLoop = true;
        int returnInt = 0;
        while (isLoop) {
            int countDigit = 0, firstLetterPlusOrMinus = 0;
            getline(cin, inputStr);
            for (int i = 0; i < strLen(inputStr.c_str()); i++) {
                if (isdigit(inputStr[i]))countDigit++;
                if (inputStr[0] == '+' || inputStr[0] == '-')firstLetterPlusOrMinus = 1;
            }
            if (countDigit == strLen(inputStr.c_str()) ||
                ((countDigit == strLen(inputStr.c_str()) - 1) && firstLetterPlusOrMinus)) {
                returnInt = std::stoi(inputStr.c_str());
                isLoop = false;
            }
            else if (countDigit > 0) cout << "Enter only an integer, try again: ";
            else cout << "Bad integer value, try again: ";
        }
        return returnInt;
    }

    int getInt(const char* prompt) {
        cout << prompt;
        int returnInt = getInt();
        return returnInt;
    }

    int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError) {
        bool isLoop = true;
        cout << prompt;
        int returnInt = getInt();
        while (isLoop) {
            if (returnInt >= min && returnInt <= max) isLoop = false;
            else {
                if (showRangeAtError) cout << errorMessage << "[" << min << " <= value <= " << max << "]: ";
                else cout << errorMessage;
                returnInt = getInt();
            }
        }
        return returnInt;
    }

    char* getcstr(const char* prompt) {
        cout << prompt;
        string inputStr;
        cin.clear();
        getline(cin, inputStr);
        char* returnPt = new char[strLen(inputStr.c_str()) + 1];
        strCpy(returnPt, inputStr.c_str());
        return returnPt;
    }

    int strLen(const char* s) {
        int len = 0;
        for (len = 0; s[len] != '\0'; len++);
        return len;
    }

    void strCpy(char* des, const char* src) {
        int len_src = 0;
        for (len_src = 0; src[len_src] != '\0'; len_src++);
        des[len_src] = { 0 };
        for (int i = 0; i < len_src; i++)des[i] = src[i];
        des[len_src] = '\0';
        return;
    }
}