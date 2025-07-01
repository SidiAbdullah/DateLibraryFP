#include <iostream>
#include <string>
using namespace std;

// year
short getYear() {
    short year = 0;
    cout << "Enter a year: ";
    cin >> year;
    return year;
}
bool isLeapYear(short year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}
short numberOfDaysInYear(short year) {
    return isLeapYear(year) ? 366 : 365;
}
int numberOfHoursInYear(short year) {
    return numberOfDaysInYear(year) * 24;
}
int numberOfMinutesInYear(short year) {
    return numberOfHoursInYear(year) * 60;
}
int numberOfSecondsInYear(short year) {
    return numberOfMinutesInYear(year) * 60;
}

// month
short getMonth() {
    short month = 0;
    cout << "Enter a month: ";
    cin >> month;
    return month;
}
short numberOfDaysInMonth(short month, short year) {
    if (month > 12 || month < 1) return -1;
    return (month == 2) ? (isLeapYear(year) ? 29 : 28) : ((month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31);
}
int numberOfHoursInMonth(short month, short year) {
    return numberOfDaysInMonth(month, year) * 24;
}
int numberOfMinutesInMonth(short month, short year) {
    return numberOfHoursInMonth(month, year) * 60;
}
int numberOfSecondsInMonth(short month, short year) {
    return numberOfMinutesInMonth(month, year) * 60;
}

// day
short getDay() {
    short day;
    cout << "Enter a day: ";
    cin >> day;
    return day;
}
string getDayOfWeek() {
    int d = getDay();
    int m = getMonth();
    int y = getYear();
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    int K = y % 100;
    int J = y / 100;

    int h = (d + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

    string days[] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
    return days[h];
}
short getDayOrder() {
    string d = getDayOfWeek();
    if (d == "Sunday") return 1;
    else if (d == "Monday") return 2;
    else if (d == "Tuesday") return 3;
    else if (d == "Wednesday") return 4;
    else if (d == "Thursday") return 5;
    else if (d == "Friday") return 6;
    else return 7;
}
//string getDayName() {}

// date
string getDate(string sep = "/") {
    short day = getDay();
    short month = getMonth();
    short year = getYear();
    return to_string(day) + sep + to_string(month) + sep + to_string(year);
}


//int main()
//{
//    //short year = getYear();
//    //cout << numberOfDaysInYear(year) << endl;
//    //short month = getMonth();
//    //cout << numberOfDaysInMonth(month, year) << endl;
//    //short day = getDay();
//    //cout << getDayOfWeek() << endl;
//    //cout << getDayOrder() << endl;
//}








int binomial(int n, int k) {
    int result = 1;
    for (int i = 0; i < k; i++) {
        result *= (n - i);
        result /= i + 1;
    }
    return result;
}
int getNumber() {
    int n = 0;
    cout << "Enter a number: ";
    cin >> n;
    return n;
}

int main() {
    int n = getNumber();

    for (int i = 0; i <= n; i++) {
        cout << binomial(n, i) << " ";
    }
    cout << endl;
}