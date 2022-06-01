#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H
#include "Patient.h"
namespace sdds
{
    class TriagePatient : public Patient
    {
        char* m_symptoms;
    public:
        TriagePatient();
        TriagePatient(const TriagePatient& C) = delete;
        TriagePatient& operator =(const TriagePatient& C) = delete;
        ~TriagePatient();
        char type()const;
        std::ostream& csvWrite(std::ostream& ostr) const;
        std::istream& csvRead(std::istream& istr);
        std::ostream& write(std::ostream& ostr)const;
        std::istream& read(std::istream& istr);
    };
    std::ostream& operator<<(std::ostream& ostr, const TriagePatient& C);
    std::istream& operator>>(std::istream& istr, TriagePatient& C);
}
#endif