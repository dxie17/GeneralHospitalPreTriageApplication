#include<istream>
#include "Menu.h"
#include"Utils.h"
using namespace std;
namespace sdds
{
    void Menu::setEmpty() {
        m_text = nullptr;
        m_noOfSel = 0;
    }

    void Menu::display()const {
        cout << this->m_text << endl;
        cout << "0- Exit" << endl;
    }

    Menu::Menu(const char* MenuContent, int NoOfSelections) {
        setEmpty();
        if (MenuContent != nullptr && NoOfSelections > 0)
        {
            m_text = new char[strLen(MenuContent) + 1];
            strCpy(m_text, MenuContent);
            m_noOfSel = NoOfSelections;
        }
    }

    Menu::~Menu() {
        delete[]m_text;
    }

    int& Menu::operator>>(int& Selection) {
        display();
        Selection = getInt(0, m_noOfSel, "> ", "Invalid option ", true);
        return Selection;
    }

    Menu::Menu(const Menu& A) {
        setEmpty();
        m_text = nullptr;
        m_noOfSel = 0;
        if (A.m_text != nullptr && A.m_noOfSel > 0)
        {
            m_text = new char[strLen(A.m_text) + 1];
            strCpy(m_text, A.m_text);
            m_noOfSel = A.m_noOfSel;
        }
    }
}