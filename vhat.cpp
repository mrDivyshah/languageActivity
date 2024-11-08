#include <stdio.h>
#include <string.h>

// Define the maximum number of students
#define MAX_STUDENTS 100

// Structure to hold each student's details
struct Student
{
    int rollNo;
    char name[50];
    char className[5];
    char dob[11];
    char gender;
    char city[50];
    int marks;
};

// Function to print line separator with given width
void printLine(int widths[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("+");
        for (int j = 0; j < widths[i] + 2; j++)
            printf("-");
    }
    printf("+\n");
}

int main()
{
    struct Student students[MAX_STUDENTS];
    int n;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    // Input student data
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details for student %d\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &students[i].rollNo);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name); // Read full name with spaces
        printf("Class: ");
        scanf("%s", students[i].className);
        printf("DOB (YYYY-MM-DD): ");
        scanf("%s", students[i].dob);
        printf("Gender (M/F): ");
        scanf(" %c", &students[i].gender);
        printf("City: ");
        scanf("%s", students[i].city);
        printf("Marks: ");
        scanf("%d", &students[i].marks);
    }

    // Calculate maximum width for each column based on data
    int rollNoWidth = 7, nameWidth = 4, classWidth = 5, dobWidth = 3, genderWidth = 6, cityWidth = 4, marksWidth = 5;
    for (int i = 0; i < n; i++)
    {
        if (snprintf(NULL, 0, "%d", students[i].rollNo) > rollNoWidth)
            rollNoWidth = snprintf(NULL, 0, "%d", students[i].rollNo);
        if (strlen(students[i].name) > nameWidth)
            nameWidth = strlen(students[i].name);
        if (strlen(students[i].className) > classWidth)
            classWidth = strlen(students[i].className);
        if (strlen(students[i].dob) > dobWidth)
            dobWidth = strlen(students[i].dob);
        if (1 > genderWidth)
            genderWidth = 1; // Since gender is one character
        if (strlen(students[i].city) > cityWidth)
            cityWidth = strlen(students[i].city);
        if (snprintf(NULL, 0, "%d", students[i].marks) > marksWidth)
            marksWidth = snprintf(NULL, 0, "%d", students[i].marks);
    }

    // Array of column widths
    int widths[] = {rollNoWidth, nameWidth, classWidth, dobWidth, genderWidth, cityWidth, marksWidth};

    // Print header
    printLine(widths, 7);
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           rollNoWidth, "RollNo", nameWidth, "Name", classWidth, "Class", dobWidth, "DOB",
           genderWidth, "Gender", cityWidth, "City", marksWidth, "Marks");
    printLine(widths, 7);

    // Print each student's data in table format
    for (int i = 0; i < n; i++)
    {
        printf("| %-*d | %-*s | %-*s | %-*s | %-*c | %-*s | %-*d |\n",
               rollNoWidth, students[i].rollNo,
               nameWidth, students[i].name,
               classWidth, students[i].className,
               dobWidth, students[i].dob,
               genderWidth, students[i].gender,
               cityWidth, students[i].city,
               marksWidth, students[i].marks);
    }
    printLine(widths, 7);

    return 0;
}
    