#include <iostream>
#include <string>
#include <iomanip>
using namespace std;



// -------------------- year --------------------

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



// -------------------- month --------------------

short getMonth() {
    short month = 0;
    cout << "Enter a number of a month (1 for January): ";
    cin >> month;
    return month;
}

short numberOfDaysInMonth(short month, short year) {
    int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if (month == 2 && isLeapYear(year))
        return 29;

    return days[month - 1];
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
        "January","February","March","April","May","June",
        "July","August","September","October","November","December"
    };
    return arrMonths[m - 1];
}



// -------------------- day(s) --------------------

short getDay() {
    short day;
    cout << "Enter a day: ";
    cin >> day;
    return day;
}

// Zeller formula → returns index (0=Saturday ... 6=Friday)
int getDayIndex(int d, int m, int y) {
    if (m < 3) {
        m += 12;
        y -= 1;
    }

    int K = y % 100;
    int J = y / 100;

    return (d + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
}

// convert to Sunday=1 ... Saturday=7
short getDayOrder(int d, int m, int y) {
    int h = getDayIndex(d, m, y);
    return (h == 0) ? 7 : h;
}

int numberOfPassedDays(int d, int m, int y) {
    int daysBeforeMonth[] = { 0,31,59,90,120,151,181,212,243,273,304,334 };

    int total = daysBeforeMonth[m - 1] + d - 1;

    if (m > 2 && isLeapYear(y))
        total++;

    return total;
}

int numberOfRemainingDays(int d, int m, int y) {
    return numberOfDaysInYear(y) - numberOfPassedDays(d, m, y);
}



// -------------------- date --------------------

void printDate(int d, int m, int y, string sep = "/") {
    cout << "Date is : " << d << sep << m << sep << y << endl;
}

void getDateByPassedDays(int PassedDays, int y) {
    int m = 1;

    while (PassedDays >= numberOfDaysInMonth(m, y)) {
        PassedDays -= numberOfDaysInMonth(m, y);
        m++;
    }

    int d = PassedDays + 1; // fix off-by-one
    printDate(d, m, y);
}

void getDateByAddingDays(int d, int m, int y, int daysToAdd) {
    d += daysToAdd;

    while (true) {
        int daysInMonth = numberOfDaysInMonth(m, y);

        if (d <= daysInMonth)
            break;

        d -= daysInMonth;
        m++;

        if (m > 12) {
            m = 1;
            y++;
        }
    }

    printDate(d, m, y);
}

void compareDates(int d, int m, int y, int d2, int m2, int y2) {
    if (y2 > y) cout << "date 2 is bigger\n";
    else if (y2 < y) cout << "date 1 is bigger\n";
    else {
        if (m2 > m) cout << "date 2 is bigger\n";
        else if (m2 < m) cout << "date 1 is bigger\n";
        else {
            if (d2 > d) cout << "date 2 is bigger\n";
            else if (d2 < d) cout << "date 1 is bigger\n";
            else cout << "dates are equal\n";
        }
    }
}



// -------------------- calendar --------------------

void printMonthCalander(int m, int y) {
    int daysInMonth = numberOfDaysInMonth(m, y);
    int firstDayOrder = getDayOrder(1, m, y);

    cout << "\n__________ " << getMonthName(m) << " __________\n\n";
    cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

    for (int i = 1; i < firstDayOrder; ++i)
        cout << "     ";

    for (int day = 1; day <= daysInMonth; ++day) {
        cout << setw(5) << day;

        if ((day + firstDayOrder - 1) % 7 == 0)
            cout << endl;
    }

    cout << "\n\n";
}

void printYearCalander(int y) {
    cout << "\n=========== " << y << " ===========\n";

    for (int i = 1; i <= 12; i++)
        printMonthCalander(i, y);
}



// -------------------- main --------------------

int main() {
    printYearCalander(2026);
}