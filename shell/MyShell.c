#include <stdio.h>
#include "MyShell.h"
#include "MyFunctionShell.h"

// הוספת הפונקציה wellcome לקובץ הכותרת של הפונקציות
void wellcome();

// הוספת הפונקציה wellcome בקובץ הכותרת של הפונקציות
void wellcome()
{
    printf("   W   W EEEEE L     CCCC OOOOO MMMMM EEEEE\n");
    printf("   W W W E     L     C    O   O M   M E    \n");
    printf("   W W W EEEE  L     C    O   O MMMMM EEEE \n");
    printf("   W   W E     L     C    O   O M   M E    \n");
    printf("    W W  EEEEE LLLLL CCCC OOOOO M   M EEEEE\n");
    printf("Welcome to myShell v2.4.3\n");
    printf("Craft packets like it is your last day on earth.\n");
    printf("-- Lao-Tze\n");
}

// ראש התוכנית main
int main()
{
    // קריאה לפונקציה wellcome לפני הכניסה ללולאה
    wellcome();
    
    // התחלת לולאת אינסון
    while (1)
    {
        getLocation(); // קריאה לפונקציה לקבלת מיקום
        char *str = inputFromUser(); // קריאה לפונקציה לקבלת קלט מהמשתמש
        if (strcmp(str, "exit") == 0) // בדיקה האם המשתמש הקליד "exit"
            logout(str); // קריאה לפונקציה להתנתקות
        char **arguments = splitString(str); // פיצול הקלט לארגומנטים
        
        // בדיקת איזו פונקציה לקרוא בהתאם לפעולה שביצע המשתמש
        if (strcmp(str, "echo") == 0)
            echo(arguments);
        if (strcmp(str, "cd") == 0)
            cd(arguments);
        if (strcmp(str, "cp") == 0)
            cp(arguments);

        // שיחרור זיכרון
        free(str);
        free(arguments);
    }

    // סיום התוכנית
    return 0;
}
