#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// -------------------- struct --------------------

struct stDate {
    short day;
    short month;
    short year;
};

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

bool isLastMonthInYear(int month) {
    return month == 12;
}

short numberOfDaysInMonth(short month, short year) {
    if (month < 1 || month > 12)
        return 0;

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

string getMonthName(int month) {
    if (month < 1 || month > 12)
        return "Invalid Month";

    string months[12] = {
        "January","February","March","April","May","June",
        "July","August","September","October","November","December"
    };

    return months[month - 1];
}

// -------------------- day(s) --------------------

short getDay() {
    short day = 0;
    cout << "Enter a day: ";
    cin >> day;
    return day;
}

stDate readFullDate() {
    stDate date;

    cout << "\nEnter Day: ";
    cin >> date.day;

    cout << "Enter Month: ";
    cin >> date.month;

    cout << "Enter Year: ";
    cin >> date.year;

    return date;
}

bool isValidDate(stDate date) {
    if (date.year < 1)
        return false;

    if (date.month < 1 || date.month > 12)
        return false;

    if (date.day < 1 || date.day > numberOfDaysInMonth(date.month, date.year))
        return false;

    return true;
}

// Zeller Formula
int getDayIndex(stDate date) {
    int d = date.day;
    int m = date.month;
    int y = date.year;

    if (m < 3) {
        m += 12;
        y--;
    }

    int K = y % 100;
    int J = y / 100;

    return (d + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
}

// Sunday = 1 ... Saturday = 7
short getDayOrder(stDate date) {
    int h = getDayIndex(date);
    return (h == 0) ? 7 : h;
}

int numberOfPassedDays(stDate date) {
    int daysBeforeMonth[] = {
        0,31,59,90,120,151,181,212,243,273,304,334
    };

    int total = daysBeforeMonth[date.month - 1] + date.day - 1;

    if (date.month > 2 && isLeapYear(date.year))
        total++;

    return total;
}

int numberOfRemainingDays(stDate date) {
    return numberOfDaysInYear(date.year) - numberOfPassedDays(date);
}

bool isLastDayInMonth(stDate date) {
    return date.day == numberOfDaysInMonth(date.month, date.year);
}

// -------------------- date --------------------

void printDate(stDate date, string separator = "/") {
    cout << "Date is : "
        << date.day << separator
        << date.month << separator
        << date.year << endl;
}

stDate getDateByPassedDays(int passedDays, int year) {
    stDate date;
    date.month = 1;
    date.year = year;

    while (passedDays >= numberOfDaysInMonth(date.month, year)) {
        passedDays -= numberOfDaysInMonth(date.month, year);
        date.month++;
    }

    date.day = passedDays + 1;
    return date;
}

stDate getDateByAddingDays(stDate date, int daysToAdd) {
    date.day += daysToAdd;

    while (date.day > numberOfDaysInMonth(date.month, date.year)) {
        date.day -= numberOfDaysInMonth(date.month, date.year);
        date.month++;

        if (date.month > 12) {
            date.month = 1;
            date.year++;
        }
    }

    return date;
}

stDate getDateByAddingOneDay(stDate date) {
    if (isLastDayInMonth(date)) {
        if (isLastMonthInYear(date.month)) {
            date.day = 1;
            date.month = 1;
            date.year++;
        }
        else {
            date.day = 1;
            date.month++;
        }
    }
    else {
        date.day++;
    }

    return date;
}

bool isDatesEqual(stDate date1, stDate date2) {
    return (
        date1.day == date2.day &&
        date1.month == date2.month &&
        date1.year == date2.year
        );
}

bool isDate1BeforeDate2(stDate date1, stDate date2) {
    if (date1.year < date2.year)
        return true;

    if (date1.year == date2.year && date1.month < date2.month)
        return true;

    if (date1.year == date2.year &&
        date1.month == date2.month &&
        date1.day < date2.day)
        return true;

    return false;
}

bool isDate1AfterDate2(stDate date1, stDate date2) {
    return !isDate1BeforeDate2(date1, date2) && !isDatesEqual(date1, date2);
}

// -------------------- calendar --------------------

void printMonthCalendar(int month, int year) {
    int daysInMonth = numberOfDaysInMonth(month, year);

    stDate firstDayDate;
    firstDayDate.day = 1;
    firstDayDate.month = month;
    firstDayDate.year = year;

    int firstDayOrder = getDayOrder(firstDayDate);

    cout << "\n__________ "
        << getMonthName(month)
        << " __________\n\n";

    cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

    for (int i = 1; i < firstDayOrder; i++)
        cout << "     ";

    for (int day = 1; day <= daysInMonth; day++) {
        cout << setw(5) << day;

        if ((day + firstDayOrder - 1) % 7 == 0)
            cout << endl;
    }

    cout << "\n\n";
}

void printYearCalendar(int year) {
    cout << "\n=========== "
        << year
        << " ===========\n";

    for (int i = 1; i <= 12; i++)
        printMonthCalendar(i, year);
}

// -------------------- main --------------------

int main() {
    stDate date1 = readFullDate();

    if (isValidDate(date1))
        cout << "\nValid Date\n";
    else
        cout << "\nInvalid Date\n";

    return 0;
}