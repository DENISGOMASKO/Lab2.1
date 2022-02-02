#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void printTime(int h, int m, int s) {
    //-----------------  проверка валидности времени
    if (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60) {
        int temp[] { h, m, s };
        for (int i{ 0 }; i < 3; ++i) {
            cout << setw(2) << setfill('0') << temp[i];
            if (i < 2) {
                cout << ":";
            }
            else {
                cout << endl;
            }
        }
    }
}

int cnt_digits(int num) { return (num /= 10) ? 1 + cnt_digits(num) : 1; }//количество цифр в числе


int readTime(char* iStr, int* oHours, int* oMinutes, int* oSeconds) {
    int* time[]{ oHours, oMinutes, oSeconds, };
    int len{ int(strlen(iStr)) }, i{ 0 }, i_time{ 0 };
    bool is_valid{ true };
    while (i < len) {
        if (isdigit(iStr[i])) {
            *time[i_time] = stoi(iStr + i);//записали число
            //cout << *time[i_time] << " ";
            i += cnt_digits(*time[i_time]);//переместили "курсор" чтения

            //-----------------  проверка валидности времени
            if (i_time == 0) {
                if (*time[i_time] < 0 || *time[i_time] > 23) {
                    is_valid = false;
                    break;
                }
            }
            else {
                if (*time[i_time] < 0 || *time[i_time] > 59) {
                    is_valid = false;
                    break;
                }
            }

            i_time++; //перемещаем запись в следующую ячейку времени

            //----------------- проверка следующего указателя
            if (i_time < 2) {
                if (time[i_time] == nullptr) {
                    break;
                }
            }

        }
        else {
            //-----------------  проверяем валидность строки 
            if (iStr[i] != ':') {
                is_valid = false;
                break;
            }
            i++;//переместили "курсор" чтения
        }
    }
    if (!is_valid) for (int j{ 0 }; j < 3; ++j) *time[j] = -1; //обнуление данных при невалидности
    return int(is_valid);
}

void print_read_time(char* iStr) {
    int h{0}, m{0}, s{0}; 
    int status{ readTime(iStr, &h, &m, &s) };
    int tmp[]{ h, m, s };
    for (int i{3}; i > 0; --i) {
        cout << status << " ";
        for (int j{ 0 }; j < i; ++j) cout << tmp[j] << ' ';
        cout << endl;
    }
}

int main() {
    char a[10];
    cin >> a;

    print_read_time(a);

    return 0;
}