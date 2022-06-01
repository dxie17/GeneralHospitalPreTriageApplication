#include <string>
#include <cstring>
#include "Ticket.h"
using namespace std;
namespace sdds
{
    Ticket::Ticket(int number) {
        m_number = number;
    }

    Ticket::operator Time() const {
        return m_time;
    }

    int Ticket::number() const {
        return m_number;
    }

    void Ticket::resetTime() {
        m_time.setToNow();
    }

    std::ostream& Ticket::csvWrite(std::ostream& ostr) const {
        return ostr << m_number << "," << m_time;
    }

    std::istream& Ticket::csvRead(std::istream& istr) {
        string sNumber, sTime;
        getline(istr, sNumber, ',');
        m_number = stoi(sNumber);
        return istr >> m_time;
    }

    std::ostream& Ticket::write(std::ostream& ostr) const {
        return ostr << "Ticket No: " << m_number << ", Issued at: " << m_time;
    }

    std::istream& Ticket::read(std::istream& istr) {
        return csvRead(istr);
    }
}
