#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_
#include "Patient.h"
namespace sdds
{
    class CovidPatient : public Patient
    {
    public:
        CovidPatient();
        CovidPatient(const CovidPatient& C) = delete;
        CovidPatient& operator =(const CovidPatient& C) = delete;
        char type()const;
        std::istream& csvRead(std::istream& istr);
        std::ostream& write(std::ostream& ostr)const;
        std::istream& read(std::istream& istr);
    };
    std::ostream& operator<<(std::ostream& ostr, const CovidPatient& C);
    std::istream& operator>>(std::istream& istr, CovidPatient& C);
}
#endif