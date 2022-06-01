#include <string>
#include <cstring>
#include "Patient.h"
#include "Utils.h"
#include "Ticket.h"
using namespace std;
namespace sdds
{

    Patient::Patient(int number, bool IOflag) :m_ticket(number) {
        m_IOflag = IOflag;
        m_name = nullptr;
        m_OHIP = 0;
    }

    Patient::~Patient() {
        delete[] m_name;
    }

    int Patient::number() const {
        return m_ticket.number();
    }

    bool Patient::fileIO() const {
        return m_IOflag;
    }

    void Patient::fileIO(const bool IOflag) {
        m_IOflag = IOflag;
        return;
    }

    void Patient::setArrivalTime() {
        m_ticket.resetTime();
    }

    Patient::operator Time() const {
        return Patient::m_ticket;
    }

    std::ostream& Patient::csvWrite(std::ostream& ostr) const {
        ostr << type() << "," << m_name << "," << m_OHIP << ",";
        m_ticket.Ticket::csvWrite(ostr);
        return ostr;
    }

    std::istream& Patient::csvRead(std::istream& istr) {
        string sName = "", sOHIP = "";
        getline(istr, sName, ',');
        if (sName.length() > 0) {
            delete[]m_name;
            this->m_name = new char[strLen(sName.c_str()) + 1];
            strCpy(m_name, sName.c_str());
            getline(istr, sOHIP, ',');
            m_OHIP = stoi(sOHIP);
            m_ticket.Ticket::csvRead(istr);
        }
        return istr;
    }

    std::ostream& Patient::write(std::ostream& ostr) const {
        char name[26] = { 0 };
        int i;
        for (i = 0; i < 25 && m_name[i] != '\0'; i++)name[i] = m_name[i];
        name[i] = '\0';
        ostr << m_ticket << endl << name << ", OHIP: " << m_OHIP;
        return ostr;
    }

    std::istream& Patient::read(std::istream& istr) {
        cout << "Name: ";
        string s;
        getline(istr, s, '\n');
        if (s.length() > 0) {
            delete[]m_name;
            m_name = new char[strLen(s.c_str()) + 1];
            strCpy(m_name, s.c_str());
            m_OHIP = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ", true);
        }
        return istr;
    }

    bool operator==(const Patient& P, const char a) {
        return P.type() == a;
    }

    bool operator==(const Patient& P, const Patient& B) {
        return P.type() == B.type();
    }

    std::ostream& operator<<(std::ostream& ostr, const Patient& P) {
        if (P.fileIO())P.Patient::csvWrite(ostr);
        else P.Patient::write(ostr);
        return ostr;
    }

    std::istream& operator>>(std::istream& istr, Patient& P) {
        if (P.fileIO())P.Patient::csvRead(istr);
        else P.Patient::read(istr);
        return istr;
    }
}
