#include "myFunction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFF_SIZE 1024

void bold()
{
    printf("\033[1m");
}

void blue()
{
    printf("\033[34m");
}

void reset()
{
    printf("\033[0m");
}




char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        *(str + index) = ch;
        size++;
        index++;
        str = (char *)realloc(str, size * sizeof(char));
    }
    *(str + index) = '\0';

    return str;
}
char **splitArgument(char *str)
{
    char *subStr;
    int size = 2;
    int index = 0;
    subStr = strtok(str, " ");
    char **argumnts = (char **)malloc(size * sizeof(char *));
    *(argumnts + index) = subStr;
    while ((subStr = strtok(NULL, " ")) != NULL)
    {
        size++;
        index++;
        *(argumnts + index) = subStr;
        argumnts = (char **)realloc(argumnts, size * sizeof(char *));
    }
    *(argumnts + (index + 1)) = NULL;

    return argumnts;
}


void getLocation()
{
    char location[BUFF_SIZE];

    if (getcwd(location, BUFF_SIZE) == NULL)
    {
        puts("Error");
    }
    else
    {
        // הדפסת נתיב התיקייה הנוכחית
        bold();
        blue();
        printf("%s", location);
        reset();
        printf("$ ");
        
        // הדפסת שם המשתמש
        struct passwd *pw = getpwuid(getuid());
        if (pw != NULL)
        {
            printf("%s", pw->pw_name);
        }
        
        // הדפסת שם המחשב
        struct utsname unameData;
        if (uname(&unameData) != -1)
        {
            printf("@%s", unameData.nodename);
        }
        
        // הדפסת התו הנוסף לסיום השורה
        printf(": ");
    }
}


void logout(char *input)
{
    free(input);
    puts("log out");
    exit(EXIT_SUCCESS);
}
void echo(char **arg)
{
    while (*(++arg))
        printf("%s ", *arg);
    puts("");
}
void cd(char **arg)
{
    if (strncmp(arg[1], "\"", 1) != 0 && arg[2] != NULL)
        puts("-myShell: cd: too many arguments");
    else if (strncmp(arg[1], "\"", 1) == 0)
    {
        // input =  cd "OneDrive - Ariel University"\0
        // [cd, "OneDrive, - , Ariel, University", NULL]
        if (chdir(arg[1]) != 0)
            printf("-myShell: cd: %s: No such file or directory\n", arg[1]);
    }
    if (chdir(arg[1]) != 0)
        printf("-myShell: cd: %s: No such file or directory\n", arg[1]);
}
void cp(char **arguments)
{
    char ch;
    FILE *src, *des;
    if ((src = fopen(arguments[1], "r")) == NULL)
    {
        puts("Erorr");
        return;
    }
    if ((des = fopen(arguments[2], "w")) == NULL)
    {
        puts("Erorr");
        fclose(src);
        return;
    }

    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, des);
    }
    fclose(src);
    fclose(des);
}
void get_dir()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./")) == NULL)
    {
        /* could not open directory */
        perror("");
        return;
    }
    /* print all the files and directories within directory */
    while ((ent = readdir(dir)) != NULL)
    {
        printf("%s ", ent->d_name);
    }
    puts("");
    closedir(dir);
}
void delete(char **arg)
{
    if (unlink(arg[1]) != 0)
        printf("-myShell: unlink: %s: No such file or directory\n", arg[1]);
}
void systemCall(char **arg)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("fork err\n");
        return;
    }
    if (pid == 0 && execvp(arg[0], arg) == -1)
        exit(1);
}
void mypipe(char **argv1, char **argv2)
{
    int fildes[2];
    if (fork() == 0)
    {
        pipe(fildes);
        if (fork() == 0)
        {
            /* first component of command line */
            close(STDOUT_FILENO);
            dup(fildes[1]);
            close(fildes[1]);
            close(fildes[0]);
            /* stdout now goes to pipe */
            /* child process does command */
            execvp(argv1[0], argv1);
        }
        /* 2nd command component of command line */
        close(STDIN_FILENO);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
        /* standard input now comes from pipe */
        execvp(argv2[0], argv2);
    }
}



// אני הוספתי
int main()
{
    char *input;
    char **arguments;

    while (1)
    {
        getLocation();
        input = getInputFromUser();
        arguments = splitArgument(input);

        // הוספת קוד לטיפול במצבים שונים, לדוגמה:
        // if (arguments[0] == "logout")
        // {
        //     logout(input);
        // }
        // else if (arguments[0] == "echo")
        // {
        //     echo(arguments);
        // }
        // else if (arguments[0] == "cd")
        // {
        //     cd(arguments);
        // }
        // וכן הלאה עבור כל פקודה אחרת...

        free(input);
        free(arguments);
    }

    return 0;
}