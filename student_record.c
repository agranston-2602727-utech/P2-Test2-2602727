/*
 * 2602727 - Anthony Granston
 * LabTest 2
 * Program Name: ABC Pre Primary - Student Record System
 *
 * This program lets the user:
 *   1. Add a student record
 *   2. Calculate a student's average
 *   3. Print a student's report card
 *   4. Print the class average and rank the students
 *   5. Exit the program
 */

#include <stdio.h>

#define MAX_STUDENTS 5   /* Maximum number of students the system can hold */

/* Struct declarations */
struct Student;  
struct Grade;     

/* Struct to hold a student's personal details */
struct Student
{
    int  student_id;
    char dob[11];           
    char first_name[30];
    char last_name[30];
    char student_class[20];
};

/* Struct to hold a student's scores and average */
struct Grade
{
    int   student_id;
    float reading_score;
    float phonics_score;
    float mathematics_score;
    float student_average;
};

/* Function prototypes */
void displayMenu(void);
void clearInputBuffer(void);
int  findStudent(struct Student *student_ptr, int student_count, int id);
int  findGrade(struct Grade *grade_ptr, int grade_count, int id);
float getScore(char subject[]);
void addStudent(struct Student *student_ptr, int *student_count);
void calculateAverage(struct Student *student_ptr, int student_count,
                      struct Grade *grade_ptr, int *grade_count);
void printReport(struct Student *student_ptr, int student_count,
                 struct Grade *grade_ptr, int grade_count);
void classAverage(struct Grade *grade_ptr, int grade_count);

int main(void)
{
    struct Student students[MAX_STUDENTS];   /* Array of student records */
    struct Grade grades[MAX_STUDENTS];       /* Array of grade records */

    /* Pointers to the arrays of structs */
    struct Student *student_ptr = students;
    struct Grade *grade_ptr = grades;

    int student_count = 0;   
    int grade_count = 0;     
    int choice = 0;

    /* Keep showing the menu until the user chooses to exit */
    do
    {
        displayMenu();

        if (scanf("%d", &choice) != 1)
        {
            clearInputBuffer();
            choice = 0;  
        }

        switch (choice)
        {
            case 1:
                addStudent(student_ptr, &student_count);
                break;
            case 2:
                calculateAverage(student_ptr, student_count, grade_ptr, &grade_count);
                break;
            case 3:
                printReport(student_ptr, student_count, grade_ptr, grade_count);
                break;
            case 4:
                classAverage(grade_ptr, grade_count);
                break;
            case 5:
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid option. Please enter a number from 1 to 5.\n");
        }

    } while (choice != 5);

    return 0;
}

/* Displays the main menu */
void displayMenu(void)
{
    printf("\n===== ABC Pre Primary Student Record System =====\n");
    printf("1. Add student record\n");
    printf("2. Calculate student average\n");
    printf("3. Print student report\n");
    printf("4. Print class average\n");
    printf("5. Exit program\n");
    printf("Enter your choice: ");
}

/* Removes any leftover characters from the input after a bad entry */
void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        
    }
}

/* Searches the student array for an id.
   Returns the position if found, or -1 if not found. */
int findStudent(struct Student *student_ptr, int student_count, int id)
{
    int i;
    for (i = 0; i < student_count; i++)
    {
        if ((student_ptr + i)->student_id == id)
        {
            return i;
        }
    }
    return -1;
}

/* Searches the grade array for an id.
   Returns the position if found, or -1 if not found. */
int findGrade(struct Grade *grade_ptr, int grade_count, int id)
{
    int i;
    for (i = 0; i < grade_count; i++)
    {
        if ((grade_ptr + i)->student_id == id)
        {
            return i;
        }
    }
    return -1;
}


float getScore(char subject[])
{
    float score;

    printf("Enter %s score (0 - 100): ", subject);
    while (scanf("%f", &score) != 1 || score < 0 || score > 100)
    {
        clearInputBuffer();
        printf("Invalid score. Enter %s score (0 - 100): ", subject);
    }
    return score;
}

//  Option 1 - Adds a new student record to the array 
void addStudent(struct Student *student_ptr, int *student_count)
{
    int id;
    struct Student *new_student;

    // Check if the array is full 
    if (*student_count >= MAX_STUDENTS)
    {
        printf("\nThe student list is full. No more students can be added.\n");
        return;
    }

    printf("\nEnter student id: ");
    if (scanf("%d", &id) != 1)
    {
        clearInputBuffer();
        printf("Invalid id. Student not added.\n");
        return;
    }

    // Check if Id was already Used
    if (findStudent(student_ptr, *student_count, id) != -1)
    {
        printf("A student with id %d already exists. Student not added.\n", id);
        return;
    }

    /* Point to the next empty position in the array */
    new_student = student_ptr + *student_count;
    new_student->student_id = id;

    printf("Enter date of birth (dd/mm/yyyy): ");
    scanf("%10s", new_student->dob);

    printf("Enter first name: ");
    scanf("%29s", new_student->first_name);

    printf("Enter last name: ");
    scanf("%29s", new_student->last_name);

    printf("Enter student class: ");
    scanf("%19s", new_student->student_class);

    (*student_count)++;
    printf("Student added successfully. (%d of %d spaces used)\n",
           *student_count, MAX_STUDENTS);
}

/* Gets the scores for a registered student and calculates the average */
void calculateAverage(struct Student *student_ptr, int student_count,
                      struct Grade *grade_ptr, int *grade_count)
{
    int id;
    int position;
    struct Grade *grade;

    printf("\nEnter student id: ");
    if (scanf("%d", &id) != 1)
    {
        clearInputBuffer();
        printf("Invalid id.\n");
        return;
    }

    /* Only registered students can have an average */
    if (findStudent(student_ptr, student_count, id) == -1)
    {
        printf("Student with id %d is not registered.\n", id);
        return;
    }

    /* If the student already has grades, update them; otherwise add a new entry */
    position = findGrade(grade_ptr, *grade_count, id);
    if (position == -1)
    {
        position = *grade_count;
        (*grade_count)++;
    }

    grade = grade_ptr + position;
    grade->student_id = id;
    grade->reading_score = getScore("Reading");
    grade->phonics_score = getScore("Phonics");
    grade->mathematics_score = getScore("Mathematics");

    grade->student_average = (grade->reading_score +
                              grade->phonics_score +
                              grade->mathematics_score) / 3;

    printf("Average for student %d is %.2f\n", id, grade->student_average);
}

/* Option 3 - Prints the report card for one student */
void printReport(struct Student *student_ptr, int student_count,
                 struct Grade *grade_ptr, int grade_count)
{
    int id;
    int student_pos;
    int grade_pos;
    struct Student *student;
    struct Grade *grade;

    printf("\nEnter student id: ");
    if (scanf("%d", &id) != 1)
    {
        clearInputBuffer();
        printf("Invalid id.\n");
        return;
    }

    student_pos = findStudent(student_ptr, student_count, id);
    if (student_pos == -1)
    {
        printf("Student with id %d is not registered.\n", id);
        return;
    }

    grade_pos = findGrade(grade_ptr, grade_count, id);
    if (grade_pos == -1)
    {
        printf("Student %d does not have an average yet. Use option 2 first.\n", id);
        return;
    }

    student = student_ptr + student_pos;
    grade = grade_ptr + grade_pos;

    /* Print the report card */
    printf("\n%-10s %-15s %-15s %-14s %-14s %-12s %-15s\n",
           "Id number", "First name", "Last name", "phonics_score",
           "reading_score", "maths_score", "student_average");
    printf("------------------------------------------------------------"
           "--------------------------------------\n");
    printf("%-10d %-15s %-15s %-14.2f %-14.2f %-12.2f %-15.2f\n",
           student->student_id, student->first_name, student->last_name,
           grade->phonics_score, grade->reading_score,
           grade->mathematics_score, grade->student_average);
}

/* Option 4 - Calculates the class average and ranks students by their average */
void classAverage(struct Grade *grade_ptr, int grade_count)
{
    struct Grade ranked[MAX_STUDENTS];   /* Copy of grades used for ranking */
    struct Grade temp;
    float total = 0;
    int i, j;

    if (grade_count == 0)
    {
        printf("\nNo student averages have been calculated yet.\n");
        return;
    }

    /* Add up all the averages and copy the grades into the ranking array */
    for (i = 0; i < grade_count; i++)
    {
        total = total + (grade_ptr + i)->student_average;
        ranked[i] = *(grade_ptr + i);
    }

    /* Bubble sort: highest average first */
    for (i = 0; i < grade_count - 1; i++)
    {
        for (j = 0; j < grade_count - 1 - i; j++)
        {
            if (ranked[j].student_average < ranked[j + 1].student_average)
            {
                temp = ranked[j];
                ranked[j] = ranked[j + 1];
                ranked[j + 1] = temp;
            }
        }
    }

    printf("\nClass average: %.2f\n", total / grade_count);

    /* Print the ranking */
    printf("\n%-6s %-10s %-15s\n", "Rank", "Id number", "student_average");
    printf("--------------------------------\n");
    for (i = 0; i < grade_count; i++)
    {
        printf("%-6d %-10d %-15.2f\n", i + 1, ranked[i].student_id,
               ranked[i].student_average);
    }
}
