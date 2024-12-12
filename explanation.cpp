#include <iostream>
using namespace std;

// Struct to hold a reminder
// It stores the day, month, year, and the reminder message
struct Reminder
{
    int day = 0;      // Day of the reminder
    int month = 0;    // Month of the reminder
    int year = 0;     // Year of the reminder
    
    char message[100];  // Message associated with the reminder
};

// Class to manage calendar operations
class Calendar
{
private:
    // Helper function to determine if a year is a leap year
    // Returns true if the year is a leap year, otherwise false
    bool isLeapYear(int year)
    {
        // A year is a leap year if divisible by 400, or divisible by 4 but not 100
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
    
    // Helper function to calculate the first day of the month
    // Uses Zeller's congruence to find the day of the week for the 1st day of the month
    int firstDayOfMonth(int month, int year)
    {
        int a = year % 100;  // Last two digits of the year
        
        // Array to hold the values for each month to adjust the day calculation
        int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        
        // Adjust the calculation if the month is January or February
        if (month < 3)
        {
            a--;
        }
        
        // Zeller's congruence algorithm to calculate the first day of the month
        int firstDay = (a + a / 4 - a / 100 + a / 400 + t[month - 1] + 1) % 7;
        
        return firstDay;  // Returns the day of the week (0 = Sunday, 1 = Monday, ...)
    }
    
public:
    // Function to return the number of days in a given month and year
    // Takes into account leap years for February
    int daysInMonth(int month, int year)
    {
        // Array containing the number of days for each month
        int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // If the month is February, check if it’s a leap year to determine if it has 29 days
        if (month == 2 && isLeapYear(year))
        {
            return 29;
        }
        
        // Return the number of days in the given month
        return daysInMonths[month - 1];
    }
    
    // Function to generate the calendar for a given month and year
    // Populates a 2D array 'calendar' with day numbers
    void generateCalendar(int month, int year, int calendar[6][7])
    {
        // Find the day of the week for the first day of the month
        int firstDay = firstDayOfMonth(month, year);
        
        int day = 1;  // Day to be displayed on the calendar
        
        // Fill the calendar grid (6 rows x 7 columns)
        // First loop goes through weeks (rows), second loop goes through days (columns)
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                // If we are at the first week and in a valid day of the month, start filling with days
                if ((i == 0 && j >= firstDay) || (i > 0 && day <= daysInMonth(month, year)))
                {
                    calendar[i][j] = day++;  // Fill day and increment it
                }
                else
                {
                    calendar[i][j] = 0;  // Fill the empty cells with 0 (no day)
                }
            }
        }
    }
    
    // Function to display the calendar in a user-friendly format
    // Takes the month, year, and the 2D calendar array as input
    void displayCalendar(int month, int year, int calendar[6][7])
    {
        // Print the header of the calendar showing the month and year
        cout << "Calendar for " << month << " in " << year << endl;
        cout << " Su Mo Tu We Th Fr Sa " << endl;
        
        // Loop through the calendar grid to print the day numbers
        for (int i = 0; i < 6; ++i)
        {
            for (int j = 0; j < 7; ++j)
            {
                if (calendar[i][j] == 0)
                {
                    cout << "   ";  // If the cell is empty, print spaces
                }
                else
                {
                    // If the day number is less than 10, print a leading space
                    if (calendar[i][j] < 10)
                    {
                        cout << "  " << calendar[i][j];
                    }
                    else
                    {
                        cout << " " << calendar[i][j];  // Otherwise, print the day number
                    }
                }
            }
            cout << endl;  // Move to the next line after each week
        }
    }
};

// Class to manage reminder operations
class ReminderManager
{
private:
    // Array to store reminders (maximum of 100)
    Reminder reminders[100];
    int reminderCount = 0;  // Counter to keep track of number of reminders
    
public:
    Calendar c;  // Calendar object to access calendar functionality
    
    // Function to add a reminder for a specific date
    void addReminder(int day, int month, int year, const char* message)
    {
        // Check if the entered date is valid (within the month range)
        if (month < 1 || month > 12 || day < 1 || day > c.daysInMonth(month, year))
        {
            cout << "Invalid date" << endl;  // If invalid, print an error message
            return;
        }
        
        // Check if the reminder storage is full (maximum 100 reminders)
        if(reminderCount >= 100)
        {
            cout << "Reminders storage is full!" << endl;  // If full, print an error message
            return;
        }
        
        // Store the reminder data (day, month, year, message)
        reminders[reminderCount].day = day;
        reminders[reminderCount].month = month;
        reminders[reminderCount].year = year;
        
        // Copy the reminder message into the message field
        strncpy(reminders[reminderCount].message, message, sizeof(reminders[reminderCount].message) - 1);
        reminders[reminderCount].message[sizeof(reminders[reminderCount].message) - 1] = '\0';
        // Null-terminate the message
        
        reminderCount++;  // Increment the reminder count
        cout << "Reminder added" << endl;
    }
    
    // Function to view reminders for a specific date
    void viewReminders(int day, int month, int year)
    {
        bool found = false;  // Flag to check if any reminder exists for the date
        
        // Loop through all reminders to find a matching date
        for(int i = 0; i<reminderCount; i++)
        {
            if (reminders[i].day == day && reminders[i].month == month && reminders[i].year == year)
            {
                cout << "Reminder: " << reminders[i].message << endl;  // Print the reminder message
                found = true;
            }
        }
        
        // If no reminder was found for the given date, notify the user
        if(!found)
        {
            cout << "No reminders for this date" << endl;
        }
    }
    
    // Function to delete a reminder for a specific date
    void deleteReminder(int day, int month, int year)
    {
        // Loop through the reminders array to find a matching date
        for(int i = 0; i<reminderCount; i++)
        {
            if (reminders[i].day == day && reminders[i].month == month && reminders[i].year == year)
            {
                // Shift the remaining reminders to fill the deleted reminder's spot
                for (int j = i; j < reminderCount - 1; ++j)
                {
                    reminders[j] = reminders[j + 1];
                }
                
                reminderCount--;  // Decrease the reminder count
                cout<< "Reminder deleted" << endl;
                return;
            }
        }
        
        // If no reminder was found for the given date, notify the user
        cout << "No reminders for this date" << endl;
    }
};

// Main function to control the application flow
int main()
{
    Calendar calendar;  // Calendar object
    ReminderManager reminderManager;  // Reminder manager object

    int month, year, choice;
    int day;
    char message[100];
    int calendarGrid[6][7];  // 2D array to store the calendar grid

    month = 12;  // Initialize month (default December)
    year = 2024;  // Initialize year (default 2024)

    // Main menu loop for the calendar application
    do {
        // Display the main menu options
        cout << "Calendar Application" << endl;
        cout << "1. View Calendar" << endl;
        cout << "2. Add Reminder" << endl;
        cout << "3. View Reminders" << endl;
        cout << "4. Delete Reminder" << endl;
        cout << "5. Go to next month" << endl;
        cout << "6. Go to previous month" << endl;
        cout << "7. Change year" << endl;
        cout << "8. Exit" << endl;
        
        // Get user's menu choice
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:  // View Calendar
                calendar.generateCalendar(month, year, calendarGrid);
                calendar.displayCalendar(month, year, calendarGrid);
                break;
                
            case 2:  // Add Reminder
                cout << "Enter date (day month year): ";
                cin >> day >> month >> year;
                cin.ignore();
                
                cout << "Enter reminder message: ";
                cin.getline(message, 100);
                
                reminderManager.addReminder(day, month, year, message);
                break;
                
            case 3:  // View Reminders
                cout << "Enter date (day month year): ";
                cin >> day >> month >> year;
                
                reminderManager.viewReminders(day, month, year);
                break;
                
            case 4:  // Delete Reminder
                cout << "Enter date (day month year): ";
                cin >> day >> month >> year;
                
                reminderManager.deleteReminder(day, month, year);
                break;
                
            case 5:  // Go to next month
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
                
            case 6:  // Go to previous month
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
                
            case 7:  // Change year
                cout << "Enter new year: ";
                cin >> year;
                break;
                
            case 8:  // Exit
                cout << "Exiting" << endl;
                break;
                
            default:  // Invalid choice
                cout << "Invalid, Try again" << endl;
        }
    } while (choice != 8);  // Continue until the user chooses to exit

    return 0;  // Exit the program
}
