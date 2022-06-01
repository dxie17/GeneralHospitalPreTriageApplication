#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include "IOAble.h"
#include "Ticket.h"

namespace sdds
{
    class Patient :public IOAble
    {
        char* m_name;
        int m_OHIP;
        Ticket m_ticket;
        bool m_IOflag;
    public:
        Patient(int number = 0, bool IOflag = false);
        Patient(const Patient& P) = delete;
        Patient& operator =(const Patient& P) = delete;
        ~Patient();
        virtual char type()const = 0;
        int number()const;
        operator Time() const;
        bool fileIO()const;
        void fileIO(const bool IOflag);
        void setArrivalTime();
        virtual std::ostream& csvWrite(std::ostream& ostr) const;
        virtual std::istream& csvRead(std::istream& istr);
        virtual std::ostream& write(std::ostream& ostr)const;
        virtual std::istream& read(std::istream& istr);
    };
    bool operator == (const Patient& P, const char a);
    bool operator == (const Patient& P, const Patient& B);
    std::ostream& operator<<(std::ostream& ostr, const Patient& P);
    std::istream& operator>>(std::istream& istr, Patient& P);
}
#endif
