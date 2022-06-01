#include <iostream>
#include <fstream>
#include "PreTriage.h"
#include "Patient.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "Utils.h"
#include "Time.h"
using namespace std;
namespace sdds
{
    void PreTriage::reg() {
        int selection = 100;
        while (m_lineupSize < maxNoOfPatients && selection && m_pMenu >> selection) {
            if (selection == 1)
                m_lineup[m_lineupSize] = new CovidPatient;
            else if (selection == 2)
                m_lineup[m_lineupSize] = new TriagePatient;
            if (selection == 1 || selection == 2) {
                m_lineup[m_lineupSize]->fileIO(false);
                m_lineup[m_lineupSize]->setArrivalTime();
                std::cout << "Please enter patient information: " << endl;
                m_lineup[m_lineupSize]->read(cin);
                std::cout << endl << "******************************************" << endl;
                m_lineup[m_lineupSize]->write(std::cout) << "Estimated Wait Time: " << this->getWaitTime(*m_lineup[m_lineupSize]);
                std::cout << endl << "******************************************" << endl << endl;
                m_lineupSize++;
                selection = 0;
            }
        }
        if (m_lineupSize == maxNoOfPatients)
            std::cout << "Line up full!" << endl;
    }

    void PreTriage::admit() {
        int selection = 100, indexOfFirst = 0;
        char type = 'x';
        while (selection && m_pMenu >> selection) {
            if (selection == 1) type = 'C';
            else if (selection == 2) type = 'T';
            indexOfFirst = indexOfFirstInLine(type);
            if (indexOfFirst == -1) selection = 0;

            else {
                m_lineup[indexOfFirst - 1]->fileIO(false);
                std::cout << endl << "******************************************" << endl;
                std::cout << "Calling for ";
                m_lineup[indexOfFirst - 1]->write(std::cout);
                std::cout << "******************************************" << endl << endl;
                setAverageWaitTime(*m_lineup[indexOfFirst - 1]);
                removePatientFromLineup(indexOfFirst - 1);
                selection = 0;
            }
        }
    }

    const Time PreTriage::getWaitTime(const Patient& p)const {
        Time time = 0;
        for (int i = 0; i < m_lineupSize; i++) {
            if (p.type() == m_lineup[i]->type() && p.number() != m_lineup[i]->number())
                time = time + getWaitTime(*m_lineup[i]);
        }
        return time;
    }

    void PreTriage::setAverageWaitTime(const Patient& p) {
        Time now;
        now.setToNow();
        if (p.type() == 'C') {
            m_averCovidWait *= (p.number() - 1);
            m_averCovidWait += (now - Time(p));
            m_averCovidWait /= p.number();
        }
        else if (p.type() == 'T') {
            m_averTriageWait *= (p.number() - 1);
            m_averTriageWait += (now - Time(p));
            m_averTriageWait /= p.number();
        }
        return;
    }

    void PreTriage::removePatientFromLineup(int index) {
        removeDynamicElement(m_lineup, index, m_lineupSize);
        return;
    }

    int PreTriage::indexOfFirstInLine(char type) const {
        int i, flag = 1;
        for (i = 0; i < m_lineupSize && flag; i++) {
            if (m_lineup[i]->type() == type)flag = 0;
        }
        if (i == m_lineupSize) i = -1;
        return i;
    }

    void PreTriage::load() {
        std::cout << "Loading data..." << endl;
        ifstream fileCheckNull;
        fileCheckNull.open(m_dataFilename, ios::in);
        char testChar = 'x';
        fileCheckNull >> testChar;
        fileCheckNull.close();
        if (fileCheckNull.eof())std::cout << "No data or bad data file!" << endl << endl;
        else {
            fileCheckNull.ignore(10000);
            ifstream fin(m_dataFilename, ios::in);
            if (fin) {
                extern char delimiter;
                delimiter = ',';
                fin >> m_averCovidWait;
                delimiter = '\n';
                fin >> m_averTriageWait;
                int i;
                for (i = 0; i < maxNoOfPatients && fin; i++) {
                    char type = 'x';
                    fin.get(type);
                    fin.ignore();
                    if (type == 'C') {
                        m_lineup[i] = new CovidPatient;
                        delimiter = '\n';
                    }
                    else if (type == 'T') {
                        m_lineup[i] = new TriagePatient;
                        delimiter = ',';
                    }
                    if (m_lineup[i]) {
                        m_lineup[i]->fileIO(true);
                        m_lineup[i]->read(fin);
                        m_lineup[i]->fileIO(false);
                    }
                }
                if (i == maxNoOfPatients && fin) {
                    std::cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
                    i++;
                }
                std::cout << i - 1 << " Records imported..." << endl << endl;
                m_lineupSize = i - 1;
                fin.close();
            }
        }
    }

    PreTriage::PreTriage(const char* dataFilename) :m_averTriageWait(5), m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2) {
        m_dataFilename = new char[strLen(dataFilename) + 1];
        strCpy(m_dataFilename, dataFilename);
        m_averCovidWait = 15;
        m_averTriageWait = 5;
    }

    PreTriage::~PreTriage() {
        std::cout << "Saving Average Wait Times," << endl;
        std::cout << "   COVID Test: " << m_averCovidWait << endl;
        std::cout << "   Triage: " << m_averTriageWait << endl;
        std::cout << "Saving m_lineup..." << endl;
        ofstream fout(m_dataFilename);
        fout << m_averCovidWait << ',' << m_averTriageWait << endl;
        for (int i = 0; i < m_lineupSize; i++) {
            std::cout << i + 1 << "- ";
            m_lineup[i]->csvWrite(std::cout) << endl;
            m_lineup[i]->csvWrite(fout) << endl;
            delete m_lineup[i];
        }
        delete[]m_dataFilename;
        fout.close();
        std::cout << "done!" << endl;
    }

    void PreTriage::run(void) {
        int selection = 100;
        load();
        while (m_appMenu >> selection && selection) {
            if (selection == 1) reg();
            else if (selection == 2) admit();
        }
    }
}