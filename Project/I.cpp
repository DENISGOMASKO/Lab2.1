#include <iostream>
#include <iomanip>
#include <string>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

//---------------------------------------------------------------- first task
void printTime(int h, int m, int s) {
    //-----------------  ïðîâåðêà âàëèäíîñòè âðåìåíè
    if (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60) {
        int temp[]{ h, m, s };
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

//---------------------------------------------------------------- second task
int cnt_digits(int num) { return (num /= 10) ? 1 + cnt_digits(num) : 1; }//cifr v chisle
int readTime(char* iStr, int* oHours, int* oMinutes, int* oSeconds) {
    int* time[]{ oHours, oMinutes, oSeconds, };
    int len{ int(strlen(iStr)) }, i{ 0 }, i_time{ 0 };
    bool is_valid{ true };
    while (i < len) {
        if (isdigit(iStr[i])) {
            while (iStr[i] == '0')
            {
                i++;
            }
            *time[i_time] = stoi(iStr + i);//çàïèñàëè ÷èñëî
            //cout << *time[i_time] << " ";
            i += cnt_digits(*time[i_time]);//ïåðåìåñòèëè "êóðñîð" ÷òåíèÿ
            //-----------------  ïðîâåðêà âàëèäíîñòè âðåìåíè
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
            i_time++; //ïåðåìåùàåì çàïèñü â ñëåäóþùóþ ÿ÷åéêó âðåìåíè
            //----------------- ïðîâåðêà ñëåäóþùåãî óêàçàòåëÿ
            if (i_time < 2) {
                if (time[i_time] == nullptr) {
                    break;
                }
            }
        }
        else {
            //-----------------  ïðîâåðÿåì âàëèäíîñòü ñòðîêè 
            if (iStr[i] != ':') {
                is_valid = false;
                break;
            }
            i++;//ïåðåìåñòèëè "êóðñîð" ÷òåíèÿ
        }
    }
    if (!is_valid) for (int j{ 0 }; j < 3; ++j) *time[j] = -1; //îáíóëåíèå äàííûõ ïðè íåâàëèäíîñòè
    return int(is_valid);
}
void print_read_time(char* iStr) {
    int h{ 0 }, m{ 0 }, s{ 0 };
    int status{ readTime(iStr, &h, &m, &s) };
    int tmp[]{ h, m, s };
    for (int i{ 3 }; i > 0; --i) {
        cout << status << " ";
        for (int j{ 0 }; j < i; ++j) cout << tmp[j] << ' ';
        cout << endl;
    }
}

//---------------------------------------------------------------- thred task
struct DateStruct
{
    int datetime[6];
    void print_date() {
        for (int i{ 0 }; i < 6; ++i) {
            cout << datetime[i] << ' ';
        }
        cout << endl;
    }
};
bool operator>(const DateStruct& a, const  DateStruct& b) {
    for (int i{ 0 }; i < 6; ++i) {
        if (a.datetime[i] > b.datetime[i]) {
            return true;
        }
        else if (a.datetime[i] != b.datetime[i]) { return false; }

    }
    return false;
}
bool operator<(const DateStruct& a, const  DateStruct& b) {
    for (int i{ 0 }; i < 6; ++i) {
        if (a.datetime[i] < b.datetime[i]) {
            return true;
        }
        else if (a.datetime[i] != b.datetime[i]) { return false; }

    }

    return false;
}
DateStruct min(const DateStruct* arr, int len) {
    int i_min{ 0 };
    for (int i{ 1 }; i < len; ++i) {
        if (arr[i] < arr[i_min]) {
            i_min = i;
        }
    }
    return arr[i_min];
}
int main_3ed() {
    int a;
    cin >> a;
    DateStruct* datestimes{ new DateStruct[a] };
    for (int i{ 0 }; i < a; ++i) {
        for (int j{ 0 }; j < 6; ++j) {
            cin >> datestimes[i].datetime[j];
        }
    }

    min(datestimes, a).print_date();

    delete[] datestimes;
    return 0;
}


//---------------------------------------------------------------- 4ed task
struct Author {
    char name[16];
    int age;
};
struct DataAutors {
    int total{ 0 };
    int long_name{ 0 };
    int adults{ 0 };
    int kids{ 0 };
    void input(char* name, int age) {
        total++;
        if (age >= 18) {
            adults++;
        }
        else if (age < 14) {
            kids++;
        }

        if (strlen(name) > 10) {
            long_name++;
        }
    }
};
int main_4ed() {
    int a;
    cin >> a;
    DataAutors data;
    Author* autors{ new Author[a] };
    for (int i{ 0 }; i < a; ++i) {
        cin >> autors[i].name;
        char tmp[5];
        cin >> tmp;
        autors[i].age = stoi(tmp);
        cin >> tmp;
        data.input(autors[i].name, autors[i].age);
    }

    cout << "names: total = " << data.total << "\nnames: long = " << data.long_name << "\nages: total = " << data.total << "\nages: adult = " << data.adults << "\nages: kid = " << data.kids << endl;

    return 0;
}

//---------------------------------------------------------------- 5ed task
#include <fstream>
int status_char(char a) {
    if (isdigit(a)) return 0;
    int ascii = int(a);
    if ((ascii >= int('A') && ascii <= int('Z')) || (ascii >= int('А') && ascii <= int('Я'))) {
        return 1;
    }
    else if ((ascii >= int('a') && ascii <= int('z')) || (ascii >= int('а') && ascii <= int('я'))) {
        return 2;
    }
    return 3;
}

void print_the_date_of_each_line() {
    ifstream file("input.txt");
    char str[101];
    int num{ 0 };
    do {
        num++;
        file.getline(str, 101);
        if (file.eof()) break;

        int len{ int(strlen(str)) };
        int low{ 0 }, upp{ 0 }, dig{ 0 };
        for (int i{ 0 }; i < len; ++i) {
            int status = status_char(str[i]);
            if (status == 0) {
                dig++;
            }
            else if (status == 1) {
                upp++;
            }
            else if (status == 2) {
                low++;
            }
        }

        cout << "Line " << num << " has " << len << " chars: " << low + upp << " are letters (" << low << " lower, " << upp << " upper), " << dig << " are digits." << endl;

    } while (1);
}

//---------------------------------------------------------------- 6ed task
void rev(char arr[101], int len)
{

    for (int i = len-1; i >= 0; --i)
    {
        cout << arr[i];
    }
    cout << endl;
}
int main_6ed() {
    int len;
    cin >> len;
    char str[101];
    for (int i = 0; i < len; i++)
    {
        cin >> str;
        rev(str, int(strlen(str)));

    }


    return 0;
}

//---------------------------------------------------------------- 7ed task
// https://youtu.be/dQw4w9WgXcQ


typedef struct Tokens_s {
    int num; //количество слов в строке
    char** arr; //массив слов (каждый элемент –- строка, т.е. char*)
    int word_count{ 0 };
    

    void add_word(char* w, int len) {
        word_count++;

        delete[] arr;
        arr = new char*[word_count];
        arr[word_count-1] = new char[len];
        arr[word_count - 1] = w;
    }
} Tokens;

void tokensSplit(Tokens* tokens, const char* str, const char* delims) {
    
}
int main() {
    Tokens t;
    char a[100];
    cin >> a;

    t.add_word(a, int(strlen(a)));
    cout << t.arr[t.word_count - 1];
    /*t.word_count++;


    t.arr = new char* [t.word_count];


    t.arr[t.word_count - 1] = new char[int(strlen(a))];
    t.arr[t.word_count - 1] = a;
    cout << t.arr[t.word_count - 1];*/
    return 0;
}


