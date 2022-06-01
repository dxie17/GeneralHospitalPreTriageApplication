#include<iomanip>
#include<istream>
#include<string>
#include<cstring>
#include "Time.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
    char delimiter = '\n';

    Time& Time::setToNow() {
        if (debug) {
            cout << "Enter current time: ";
            cin >> *this;
        }
        else this->m_min = sdds::getTime();
        return *this;
    }

    Time::Time(unsigned int min) {
        m_min = min;
    }

    std::ostream& Time::write(std::ostream& ostr) const {
        unsigned int mm, hh;
        mm = this->m_min % 60;
        hh = (this->m_min - mm) / 60;
        ostr << setw(2) << setfill('0') << hh << ":" << setw(2) << setfill('0') << mm;
        return ostr;
    }

    std::istream& Time::read(std::istream& istr) {
        string inputStr;
        unsigned int mm, hh;
        bool isLoop = true;
        string s;
        while (isLoop) {
            int countDigit = 0, countCom = 0;
            cin.clear();
            if (delimiter == '\n')
                getline(istr, inputStr, '\n');
            else if (delimiter == ',')
                getline(istr, inputStr, ',');
            for (int i = 0; i < strLen(inputStr.c_str()); i++) {
                if (isdigit(inputStr[i]))countDigit++;
                if (inputStr[i] == ':')countCom++;
            }
            char charHH[100], charMM[100];
            int countHH = 0, countMM = 0, flag = 0;
            if (countDigit == strLen(inputStr.c_str()) - 1 && countCom == 1) {
                for (int i = 0; i < strLen(inputStr.c_str()); i++) {
                    if (!flag) {
                        charHH[countHH] = inputStr.c_str()[i];
                        countHH++;
                    }
                    else {
                        charMM[countMM] = inputStr.c_str()[i];
                        countMM++;
                    }
                    if (inputStr[i] == ':') flag = 1;
                }
                charHH[countHH] = '\0';
                charMM[countMM] = '\0';
                mm = std::stoi(charMM);
                hh = std::stoi(charHH);
                this->m_min = hh * 60 + mm;
                isLoop = false;
            }
            else cout << "Bad time entry, retry (HH:MM): ";
        }
        return istr;
    }

    Time& Time::operator-=(const Time& D) {
        this->m_min >= D.m_min ? this->m_min -= D.m_min :
            this->m_min -= (D.m_min - 24 * 60 * ((int)((D.m_min - m_min) / 60 / 24) + 1));
        return *this;
    }

    Time Time::operator-(const Time& D) const {
        Time returnTime;
        m_min >= D.m_min ? returnTime.m_min = this->m_min - D.m_min :
            returnTime.m_min = this->m_min - D.m_min + 24 * 60 * ((int)((D.m_min - m_min) / 24 / 60) + 1);
        return returnTime;
    }

    Time& Time::operator+=(const Time& D) {
        this->m_min += D.m_min;
        return *this;
    }

    Time Time::operator+(const Time& D)const {
        Time returnTime;
        returnTime.m_min = this->m_min + D.m_min;
        return returnTime;
    }

    Time& Time::operator=(unsigned int val) {
        this->m_min = val;
        return *this;
    }

    Time& Time::operator *= (unsigned int val) {
        this->m_min *= val;
        return *this;
    }

    Time& Time::operator /= (unsigned int val) {
        this->m_min /= val;
        return *this;
    }

    Time Time::operator *(unsigned int val)const {
        Time returnTime;
        returnTime.m_min = this->m_min * val;
        return returnTime;
    }

    Time Time::operator /(unsigned int val)const {
        Time returnTime;
        returnTime.m_min = this->m_min / val;
        return returnTime;
    }

    Time::operator unsigned int()const {
        return this->m_min;
    }

    Time::operator int()const {
        return int(this->m_min);
    }

    std::ostream& operator<<(std::ostream& ostr, const Time& D) {
        return D.write(ostr);
    }

    std::istream& operator>>(std::istream& istr, Time& D) {
        return D.read(istr);
    }
}