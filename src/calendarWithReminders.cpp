// Core Functionalities :
// View Calendar: Display a calendar for a given month and year
// Add Reminder: Add a reminder for a specific date
// View Reminders: Display all reminders for a specific date
// Navigate Calendar: Allow users to move between months and years

#include <iostream>
using namespace std;

struct Reminder
{
    int day = 0;
    int month = 0;
    int year = 0;
    
    char message[100];
};

class Calendar
{
private:
    bool isLeapYear(int year)
    {
        if (year % 400 == 0)
        {
            return true;
        }
        
        else if (year % 100 == 0)
        {
                return false;
        }
        
        else if (year % 4 == 0)
        {
            return true;
        }
        
        else
        {
            return false;
        }
    }
    
    int firstDayOfMonth(int month, int year)
    {
        int a = year % 100;
        
        int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        
        if (month < 3)
        {
            a--;
        }
        
        int firstDay = (a + a / 4 - a / 100 + a / 400 + t[month - 1] + 1) % 7;
        
        return firstDay;
    }
    
public:
    int daysInMonth(int month, int year)
    {
        int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year))
        {
            return 29;
        }
        
        return daysInMonths[month - 1];
    }
    
    void generateCalendar(int month, int year, int calendar[6][7])
    {
        int firstDay = firstDayOfMonth(month, year);
        
        int day = 1;
        
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if ((i == 0 && j >= firstDay) || (i > 0 && day <= daysInMonth(month, year)))
                {
                    calendar[i][j] = day++;
                }
                
                else
                {
                    calendar[i][j] = 0;
                }
            }
        }
    }
    
    void displayCalendar(int month, int year, int calendar[6][7])
    {
        cout << "Calendar for " << month << " in " << year << endl;
        cout << " Su Mo Tu We Th Fr Sa " << endl;
        
        for (int i = 0; i < 6; ++i)
        {
            for (int j = 0; j < 7; ++j)
            {
                if (calendar[i][j] == 0)
                {
                    cout << "   ";
                }
                else
                {
                    if (calendar[i][j] < 10)
                    {
                        cout << "  " << calendar[i][j];
                    }
                    
                    else
                    {
                        cout << " " << calendar[i][j];
                    }
                }
            }
            
            cout << endl;
        }
    }
};

class ReminderManager
{
private:
    Reminder reminders[100];
    int reminderCount = 0;
    
public:
    ReminderManager() : reminderCount(0) {}
    Calendar c;
    
    void addReminder(int day, int month, int year, const char* message)
    {
        if (month < 1 || month > 12 || day < 1 || day > c.daysInMonth(month, year))
        {
            cout << "Invalid date" << endl;
            return;
        }
        
        if(reminderCount >= 100)
        {
            cout << "Reminders storage is full!" << endl;
            return;
        }
        
        reminders[reminderCount].day = day;
        reminders[reminderCount].month = month;
        reminders[reminderCount].year = year;
        
        strncpy(reminders[reminderCount].message, message, sizeof(reminders[reminderCount].message) - 1);
        reminders[reminderCount].message[sizeof(reminders[reminderCount].message) - 1] = '\0';
        
        reminderCount++;
        cout << "Reminder added" << endl;
    }
    
    void viewReminders(int day, int month, int year)
    {
        bool found = false;
        for(int i = 0; i<reminderCount; i++)
        {
            if (reminders[i].day == day && reminders[i].month == month && reminders[i].year == year)
            {
                cout << "Reminder: " << reminders[i].message << endl;
                found = true;
            }
        }
        
        if(!found)
        {
            cout << "No reminders for this date" << endl;
        }
    }
    
    void deleteReminder(int day, int month, int year)
    {
        for(int i = 0; i<reminderCount; i++)
        {
            if (reminders[i].day == day && reminders[i].month == month && reminders[i].year == year)
            {
                for (int j = i; j < reminderCount - 1; ++j)
                {
                    reminders[j] = reminders[j + 1];
                }
                
                reminderCount--;
                cout<< "Reminder deleted" << endl;
                return;
            }
        }
        
        cout << "No reminders for this date" << endl;
    }
};

int main()
{
    Calendar calendar;
    ReminderManager reminderManager;

    int month, year, choice;
    int day;
    char message[100];
    int calendarGrid[6][7];

    month = 12;
    year = 2024;

    do {
        cout << "Calendar Application" << endl;
        cout << "1. View Calendar" << endl;
        cout << "2. Add Reminder" << endl;
        cout << "3. View Reminders" << endl;
        cout << "4. Delete Reminder" << endl;
        cout << "5. Go to next month" << endl;
        cout << "6. Go to previous month" << endl;
        cout << "7. Change year" << endl;
        cout << "8. Exit" << endl;
        
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                calendar.generateCalendar(month, year, calendarGrid);
                calendar.displayCalendar(month, year, calendarGrid);
                break;
                
            case 2:
                cout << "Enter date (day month year): ";
                cin >> day >> month >> year;
                cin.ignore();
                
                cout << "Enter reminder message: ";
                cin.getline(message, 100);
                
                reminderManager.addReminder(day, month, year, message);
                break;
                
            case 3:
                cout << "Enter date (day month year): ";
                cin >> day >> month >> year;
                
                reminderManager.viewReminders(day, month, year);
                break;
                
            case 4:
                cout << "Enter date (day month year): ";
                cin >> day >> month >> year;
                
                reminderManager.deleteReminder(day, month, year);
                break;
                
            case 5:
                if (month == 12)
                {
                    month = 1;
                    year++;
                }
                
                else
                {
                    month++;
                }
                cout << "Going to the next month" << endl;
                break;
                
            case 6:
                if (month == 1)
                {
                    month = 12;
                    year--;
                }
                
                else
                {
                    month--;
                }
                cout << "Going to the previous month" << endl;
                break;
                
            case 7:
                cout << "Enter new year: ";
                cin >> year;
                break;
                
            case 8:
                cout << "Exiting" << endl;
                break;
                
            default:
                cout << "Invalid, Try again" << endl;
        }
    } while (choice != 8);

    return 0;
}
