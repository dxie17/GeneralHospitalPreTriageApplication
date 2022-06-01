#ifndef SDDS_UTILS_H_
#define SDDS_UTILS_H_
namespace sdds
{
    extern bool debug; // making sdds::debug variable global to all the files
                       // which include: "utils.h"
    int getTime(); // returns the time of day in minutes
    int getInt();
    int getInt(const char* prompt);
    int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError = true);
    char* getcstr(const char* prompt = nullptr);
    int strLen(const char* s);
    void strCpy(char* des, const char* src);

    template <typename type>
    void removeDynamicElement(type* array[], int index, int& size) {
        delete array[index];
        for (int j = index; j < size; j++) {
            array[j] = array[j + 1];
        }
        size--;
    }
}
#endif // !SDDS_UTILS_H_