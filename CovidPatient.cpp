#include <iostream>
#include "CovidPatient.h"
#include "Patient.h"
using namespace std;
namespace sdds
{
    int nextCovidTicket = 1;

    CovidPatient::CovidPatient() : Patient(nextCovidTicket) {
        nextCovidTicket++;
    }

    char CovidPatient::type()const {
        return 'C';
    }

    std::istream& CovidPatient::csvRead(std::istream& istr) {
        Patient::csvRead(istr);
        nextCovidTicket = Patient::number() + 1;
        return istr;
    }

    std::ostream& CovidPatient::write(std::ostream& ostr) const {
        if (this->fileIO())Patient::csvWrite(ostr);
        else {
            ostr << "COVID TEST" << endl;
            Patient::write(ostr) << endl;
        }
        return ostr;
    }

    std::istream& CovidPatient::read(std::istream& istr) {
        if (this->fileIO())CovidPatient::csvRead(istr);
        else {
            Patient::read(istr);
            nextCovidTicket = Patient::number() + 1;
        }
        return istr;
    }

    std::ostream& operator<<(std::ostream& ostr, const CovidPatient& C) {
        return C.CovidPatient::write(ostr);
    }

    std::istream& operator>>(std::istream& istr, CovidPatient& C) {
        return C.read(istr);
    }
}