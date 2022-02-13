#include <iostream>
#include <iomanip>
#include <string>

#include <stdio.h>
#include <stdlib.h>

#include <fstream>

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
int cnt_digits(int num) { return (num /= 10) ? 1 + cnt_digits(num) : 1; }

int readTime(string iStr, int* oHours, int* oMinutes, int* oSeconds) {

    int* time[]{ oHours, oMinutes, oSeconds, };

    int len{ int(iStr.length()) }, i{ 0 }, i_time{ 0 };

    bool is_valid{ true };

    while (i < len) {

        if (isdigit(iStr[i])) {

            while (iStr[i] == '0')
            {
                i++;
            }

            if (i_time > 2) {
                is_valid = false;
                break;
            }
            *time[i_time] = stoi(&iStr[i]);

            i += cnt_digits(*time[i_time]);

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
            i_time++;
            if (i_time < 2) {
                if (time[i_time] == nullptr) {
                    break;
                }
            }
        }
        else {

            if (iStr[i] != ':') {
                is_valid = false;
                break;
            }
            else if (i != 0 && iStr[i - 1] == ':') {
                is_valid = false;
                break;
            }
            i++;
        }
    }
    if (!is_valid) for (int j{ 0 }; j < 3; ++j) *time[j] = -1;
    return int(is_valid);
}
void print_read_time(string iStr) {
    int h{ 0 }, m{ 0 }, s{ 0 };
    int status{ readTime(iStr, &h, &m, &s) };
    int tmp[]{ h, m, s };
    for (int i{ 3 }; i > 0; --i) {
        cout << status << " ";
        for (int j{ 0 }; j < i; ++j) cout << tmp[j] << ' ';
        cout << endl;
    }
}

int main_2ed() {
    string a;
    getline(cin, a);
    print_read_time(a);


    return 0;
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

int status_char(char a) {
    if (isdigit(a)) return 0;

    if ((a >= 'A' && a <= 'Z') || (a >= 'А' && a <= 'Я')) {
        return 1;
    }
    else if ((a >= 'a' && a <= 'z') || (a >= 'а' && a <= 'я')) {
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
    file.close();
}

//---------------------------------------------------------------- 6ed task
void rev(char arr[101], int len)
{

    for (int i = len - 1; i >= 0; --i)
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



int main_7ed() {
    ifstream file("input.txt");
    char str[1000001];
    file.getline(str, 1000001);
    int tmp{ 0 };
    bool strick = false;
    for (int i{ 0 }; str[i] != '\0'; ++i) {
        if (status_char(str[i]) != 3) {
            if (!strick) tmp++;
            strick = true;

        }
        else {
            strick = false;
        }
    }
    cout << tmp << endl;
    strick = false;
    for (int i{ 0 }; str[i] != '\0'; ++i) {
        if (status_char(str[i]) != 3) {
            cout << str[i];
            strick = false;
        }
        else {
            if (!strick) cout << endl;
            strick = true;
        }
    }
    return 0;
}

//---------------------------------------------------------------- 8ed task
string concat(string pref, string suff) {
    return pref + suff;
}


int main_8ed() {
    int num{ 0 };
    string tmp;
    cin >> num;
    for (int i = 0; i < num; ++i) {
        cin >> tmp;
        cout << tmp;
    }
    return 0;
}

//---------------------------------------------------------------- 9ed task
class String_storage {

public:
    string* arr;
    int id{ 0 };



    void add_str() {
        cin >> arr[id];
        id++;
    }

    void del_str(int num) {
        arr[num].clear();
    }

    string return_str(int num) {
        return arr[num];
    }

    int len_str(int num) {
        char smv;
        cin >> smv;
        int l{ 0 }, len{ int(arr[num].length()) };
        for (int i{ 0 }; i < len; ++i) {
            if (arr[num][i] == smv) l++;
        }
        return l;
    }

    void update(int len) {
        arr = new string[len];
    }

    void UI(int first, int second) {

        switch (first)
        {
        case 0:
            add_str();
            break;
        case 1:
            del_str(second);
            break;
        case 2:
            cout << return_str(second) << endl;
            break;
        case 3:
            cout << len_str(second) << endl;
            break;
        default:
            break;
        }
    }

}Ss;

int main_9ed() {
    int a;
    cin >> a;
    String_storage bd;
    bd.update(a);
    for (int i = 0; i < a; ++i) {
        int f, s;

        cin >> f >> s;
        bd.UI(f, s);
    }

    return 0;
}

#define _CRT_SECURE_NO_WARNINGS


int main() {
    unsigned long long input_xor{0};
    int numer, denom, n;
    char tmp[8];
    int i_tmp, factor;
    bool is_denom;
    cin >> n;
    for (int i{ 0 }; i < n; ++i) {
        //scanf("%d/%d xor %llx", &numer, &denom, &input_xor);
        cin >> tmp;
        is_denom = true;
        factor = 1;
        numer = 0;
        denom = 0;
        for (i_tmp = strlen(tmp)-1; i_tmp >= 0; --i_tmp) {
            if (tmp[i_tmp] == '/') {
                is_denom = false;
                factor = 1;
            }
            else if (is_denom) {

                denom += int(tmp[i_tmp] - '0') * factor;
                factor *= 10;
            }
            else {
                numer += int(tmp[i_tmp] - '0') * factor;
                factor *= 10;
            }
        }
        cin >> tmp;
        //delete[] tmp;
        //cin >> input_xor;
        scanf("%llx", &input_xor);
        
        double val = (double)numer / denom;

        unsigned long long btz;
        memcpy(&btz, &val, sizeof(val));

        unsigned long long rez { btz  ^ input_xor};

        double xored;
        memcpy(&xored, &rez, sizeof(rez));
        printf("%0.15g\n", xored);
        //printf("%0.15g\n", double(unsigned long long(unsigned long long(double(numer / denom)) ^ input_xor)));
    }
    return 0;
}