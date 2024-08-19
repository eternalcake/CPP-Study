#include <iostream>
#include <string>

bool leapYear(int year);
int fillArray(int array[6][7], int daysInMonth, int row, int column, int daysOffset);
void printArray(int array[6][7], int days, int row, int column, std::string dateBaseOffset, int daysOffset);
void printMonth(int year, std::string monthName, const std::string dayOfWeek[], int weekLenght, std::string baseOffset);
std::string switchName(int monthNumber);

int main(){

    bool isContinue;

    do {
        // Setup variables
        int year, firstDayOfWeek;

        std::cout << "Enter a year: ";
        std::cin >> year;
        std::cout << "Enter first day of the year as number [1 : Monday 2 : Tuesday ... ]: ";
        std::cin >> firstDayOfWeek;
        std::cout << std::endl;

        if (firstDayOfWeek < 1 || firstDayOfWeek > 7) {
            std::cout << "You can specify the day of the week only between 1 and 7." << std::endl << std::endl;
            return main();
        }

        int fe {leapYear(year) ? 29 : 28};
        
        const int ja = 31, ma = 31,
                ap = 30, may = 31, june = 30,
                july = 31, au = 31, sept = 30,
                oc = 31, no = 30, de = 31;

        const int months [12] = {ja, fe, ma,
                                ap, may, june,
                                july, au, sept,
                                oc, no, de};

        const int weekLenght = 7;
        const std::string daysOfWeek[weekLenght] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

        const int row = 6, column = 7;
        int dateOfMonth[row][column];

        std::string monthName;

        // Offset for formatting output, change only baseOffset
        std::string baseOffset = "";
        std::string dateBaseOffset = baseOffset + " ";

        // Start printing
        std::cout << "Calendar for " << year << " year" << std::endl << std::endl;
        for (int i = 0; i < 12; i++) {

            // Setup date of month array
            fillArray(dateOfMonth, months[i], row, column, firstDayOfWeek);

            // Setup month name
            monthName = switchName(i);

            // Printing Calendar
            printMonth(year, monthName, daysOfWeek, weekLenght, baseOffset);
            printArray(dateOfMonth, months[i], row, column, dateBaseOffset, firstDayOfWeek);

            // Change first day of week as last column at previous month
            firstDayOfWeek = fillArray(dateOfMonth, months[i], row, column, firstDayOfWeek);
        }

        // Should print another year
        std::string answer;
        std::cout << "Print another year (Yes [y] | No [n]) ? ";
        std::cin >> answer;

        if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes" || answer == "YES") {
            isContinue = true;
        } else {
            if (answer == "n" || answer == "N" || answer == "no" || answer == "No" || answer == "NO") {
                isContinue = false;
            } else {
                std::cout << "Answer is not walid. Abort retrying.";\
                isContinue = false;
            }
        }

    } while (isContinue);

    return 0;
}

bool leapYear(int year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        return true;
    } else {
        return false;
    }
}

int fillArray(int array[6][7], int daysInMonth, int row, int column, int daysOffset)
{
    // While (- (daysOffset - 1)) < 0, array[i][j] will be set to 0 
    int pastDaysCounter = - (daysOffset - 1);
    int daysOffsetReturn;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            // Filling the array with dates
            // if the date is less than 1 and more than the number of days
            // the array is filled with 0
            if (pastDaysCounter < daysInMonth) {
                pastDaysCounter++;
                daysOffsetReturn = j + 2;
                if (pastDaysCounter >= 0) {
                    array[i][j] = pastDaysCounter;
                } else {
                    array[i][j] = 0;
                }
            } else {
                //break;
                array[i][j] = 0;
            }
        }
    }
    // Return last column index to use as new firstDayOfWeek
    return daysOffsetReturn;
}

void printArray(int array[6][7], int daysInMonth, int row, int column, std::string dateBaseOffset, int daysOffset)
{
    // If (- (daysOffset - 1)) > 0, printing array[i][j]
    int pastDaysCounter = - (daysOffset - 1);

    std::string dateBaseOffsetTemp;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (pastDaysCounter < daysInMonth) {
                // Print only valid days of month
                pastDaysCounter++;
                // If first column - decrease offset
                if (j == 0) {
                    // If one digit in date - decrease offset
                    if (array[i][j] / 10 == 0) {
                        dateBaseOffsetTemp = dateBaseOffset + " ";
                    } else {
                        dateBaseOffsetTemp = dateBaseOffset + "";
                    }
                } else {
                    if (array[i][j] / 10 == 0) {
                        dateBaseOffsetTemp = dateBaseOffset + "   ";
                    } else {
                        dateBaseOffsetTemp = dateBaseOffset + "  ";
                    }
                }
                // Print non 0 days of month
                if (pastDaysCounter > 0) {
                    std::cout << dateBaseOffsetTemp << array[i][j];
                } else {
                    // Decrease offset if first digit of array
                    if (i == 0 && j == 0) {
                        std::cout << dateBaseOffset + "  ";
                    } else {
                        std::cout << dateBaseOffset + "    ";
                    }
                }
            } else {
                break;
            }
        }
        // If last line starts with 0, newline will not be printed
        if (array[i][0] != 0 || i == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl << std::endl;
}

void printMonth(int year, std::string monthName, const std::string dayOfWeek[], int weekLenght, std::string baseOffset)
{
    std::cout << "-- " << monthName << " " << year << " --"<< std::endl << std::endl;
    for (int i = 0; i < weekLenght; ++i) {
        // Not print "  " at the end of last day of week
        if (weekLenght != i + 1){
            std::cout << baseOffset << dayOfWeek[i] << "  ";
        } else {
            std::cout << baseOffset << dayOfWeek[i];
        }
    }
    std::cout << std::endl << std::endl;
}

std::string switchName(int monthNumber)
{
    std::string monthNameTemp;
    switch (monthNumber) {
        case 0:
            monthNameTemp = "January";
        break;
        case 1:
            monthNameTemp = "February";
        break;
        case 2:
            monthNameTemp = "March";
        break;
        case 3:
            monthNameTemp = "April";
        break;
        case 4:
            monthNameTemp = "May";
        break;
        case 5:
            monthNameTemp = "June";
        break;
        case 6:
            monthNameTemp = "July";
        break;
        case 7:
            monthNameTemp = "August";
        break;
        case 8:
            monthNameTemp = "September";
        break;
        case 9:
            monthNameTemp = "October";
        break;
        case 10:
            monthNameTemp = "November";
        break;
        case 11:
            monthNameTemp = "December";
        break;
        default:
        break;
    }
    return monthNameTemp;
}
