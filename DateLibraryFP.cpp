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
string getMonthName(int m) {
    string arrMonths[12] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    return arrMonths[m - 1];
}

// day (s)
short getDay() {
    short day;
    cout << "Enter a day: ";
    cin >> day;
    return day;
}
string getDayOfWeek(int d, int m, int y) {
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
short getDayOrder(int d, int m, int y) {
    string dayName = getDayOfWeek(d, m, y);
    if (dayName == "Sunday") return 1;
    else if (dayName == "Monday") return 2;
    else if (dayName == "Tuesday") return 3;
    else if (dayName == "Wednesday") return 4;
    else if (dayName == "Thursday") return 5;
    else if (dayName == "Friday") return 6;
    else return 7;
}
int yearGoneDays(int d, int m, int y) {
    int yearGoneDays = d - 1; // d is not done yet so - 1
    while (m > 1) {
        yearGoneDays += numberOfDaysInMonth(m - 1, y);
        --m;
    }
    return yearGoneDays;
}
int yearRemainingDays(int d, int m, int y) {
    return numberOfDaysInYear(y) - yearGoneDays(d, m, y);
}

// date
void printDate(int d, int m, int y, string sep = "/") {
    cout << "Date is : " << to_string(d) + sep + to_string(m) + sep + to_string(y) << endl;
}
void getDate(int goneDays, int y) {
    int m = 1;
    while (goneDays >= numberOfDaysInMonth(m, y)) {
        goneDays -= numberOfDaysInMonth(m, y);
        m++;
    }
    int d = goneDays;
    printDate(d, m, y);
}

// calender
void printMonthCalander(int m, int y) {
    int daysInMonth = numberOfDaysInMonth(m, y);
    int firstDayOrder = getDayOrder(1, m, y); // to help with formating

    cout << "\n______________________" << getMonthName(m) << "________________________\n" << endl;
    cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;

    for (int i = 1; i < firstDayOrder; ++i) {
        cout << "     ";
    }

    for (int day = 1; day <= daysInMonth; ++day) {
        printf("%5d", day);

        if ((day + firstDayOrder - 1) % 7 == 0)
            cout << endl;
    }
    cout << "\n\n_____________________________________________________\n\n" << endl;
}
void printYearCalander(int y) {
    cout << "\n______________________" << y << "________________________\n" << endl;
    for (int i = 1; i <= 12; i++) {
        printMonthCalander(i, y);
    }
}


// test
int main()
{
    int d = getDay();
    int m = getMonth();
    int y = getYear();
    printDate(d, m, y);
    cout << "Gone days are : " << yearGoneDays(d, m, y) << endl;
    //cout << "Remaining days are : " << yearRemainingDays(d, m, y) << endl;
    //cout << "\nDate by gone days is : " << endl;
    getDate(yearGoneDays(d, m, y) + 1, y);
}
