#include <iostream>
#include <string>
#include <cstring>
#include "TriagePatient.h"
#include "Patient.h"
#include "Utils.h"
#include "Time.h"
using namespace std;
namespace sdds
{
    int nextTriageTicket = 1;

    TriagePatient::TriagePatient() : Patient(nextTriageTicket) {
        m_symptoms = nullptr;
        nextTriageTicket++;
    }

    TriagePatient::~TriagePatient() {
        delete[] m_symptoms;
    }

    char TriagePatient::type()const {
        return 'T';
    }

    std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const {
        return Patient::csvWrite(ostr) << ',' << m_symptoms;
    }

    std::istream& TriagePatient::csvRead(std::istream& istr) {
        string symptoms = "";
        extern char delimiter;
        delimiter = ',';
        delete[] m_symptoms;
        Patient::csvRead(istr);
        getline(istr, symptoms);
        if (symptoms.length() > 0) {
            this->m_symptoms = new char[strLen(symptoms.c_str()) + 1];
            strCpy(m_symptoms, symptoms.c_str());
        }
        nextTriageTicket = Patient::number() + 1;
        delimiter = '\n';
        return istr;
    }

    std::ostream& TriagePatient::write(std::ostream& ostr) const {
        if (this->fileIO())TriagePatient::csvWrite(ostr);
        else {
            ostr << "TRIAGE" << endl;
            Patient::write(ostr) << endl;
            ostr << "Symptoms: " << m_symptoms << endl;
        }
        return ostr;
    }

    std::istream& TriagePatient::read(std::istream& istr) {
        if (this->fileIO())TriagePatient::csvRead(istr);
        else {
            string  symptoms = "";
            delete[] m_symptoms;
            Patient::read(istr);
            cout << "Symptoms: ";
            getline(istr, symptoms);
            this->m_symptoms = new char[strLen(symptoms.c_str()) + 1];
            strCpy(m_symptoms, symptoms.c_str());
            nextTriageTicket = Patient::number() + 1;
        }
        return istr;
    }

    std::ostream& operator<<(std::ostream& ostr, const TriagePatient& C) {
        return C.write(ostr);
    }

    std::istream& operator>>(std::istream& istr, TriagePatient& C) {
        return C.read(istr);
    }
}