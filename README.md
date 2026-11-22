# ABC Pre Primary – Student Record System

A menu-driven C program that keeps student records for ABC Pre Primary. It stores each student's personal details and their scores in Reading, Phonics and Mathematics. It can work out each student's average, print a report card, and show the class average with students ranked from highest to lowest.

The program uses functions, arrays of structs and pointers.

## Project files

| File | Description |
|------|-------------|
| `student_record.c` | The full source code for the program |
| `README.md` | This file: project introduction and user manual |

## How the program stores data

The program uses two structs:

- **`struct Student`**: a student's personal details (ID, date of birth, first name, last name and class).
- **`struct Grade`**: a student's scores in Reading, Phonics and Mathematics, plus their average. Each grade record is linked to a student by the student ID.

Both are kept in arrays that hold up to **5 students** (`MAX_STUDENTS`). The data is kept in memory only, so all records are lost when the program exits.

---

# User Manual

## 1. Compiling and running

You need a C compiler such as `gcc`.

```bash
gcc -Wall -Wextra -o student_record student_record.c
./student_record
```

## 2. The main menu

When the program starts, it shows this menu:

```
===== ABC Pre Primary Student Record System =====
1. Add student record
2. Calculate student average
3. Print student report
4. Print class average
5. Exit program
Enter your choice:
```

Type the number of an option and press **Enter**. After each option finishes, the menu appears again. If you enter anything other than 1 to 5, the program shows `Invalid option` and asks again.

## 3. Option 1: Add student record

Adds a new student to the system. You will be asked for:

| Prompt | What to enter | Example |
|--------|---------------|---------|
| Student id | A whole number that has not been used before | `101` |
| Date of birth | In the form dd/mm/yyyy (up to 10 characters) | `15/03/2021` |
| First name | One word, up to 29 characters | `Maria` |
| Last name | One word, up to 29 characters | `Brown` |
| Student class | One word, up to 19 characters | `K1` |

**Notes**

- Names and class must be a **single word with no spaces**. Anything after a space is taken as the answer to the next prompt.
- If the ID is not a number, or is already used by another student, the student is **not** added.
- Only 5 students can be added. When the list is full, the program says so and adds no more.
- After a student is added, the program shows how many of the 5 spaces are used.

## 4. Option 2: Calculate student average

Enters a student's scores and works out their average.

1. Enter the student's ID. The student must already have been added with option 1.
2. Enter the **Reading**, **Phonics** and **Mathematics** scores. Each score must be between **0 and 100**. Decimals such as `87.5` are allowed. If a score is out of range or not a number, the program asks for it again.
3. The program prints the average of the three scores, rounded to 2 decimal places.

**Example**

```
Enter student id: 101
Enter Reading score (0 - 100): 90
Enter Phonics score (0 - 100): 85
Enter Mathematics score (0 - 100): 80
Average for student 101 is 85.00
```

If you use option 2 again for a student who already has scores, the old scores are **replaced** with the new ones.

## 5. Option 3: Print student report

Prints a report card for one student.

1. Enter the student's ID.
2. The program prints the student's ID, first and last name, each score and their average.

**Example**

```
Id number  First name      Last name       phonics_score  reading_score  maths_score  student_average
--------------------------------------------------------------------------------------------------
101        Maria           Brown           85.00          90.00          80.00        85.00
```

The report will not print if:

- no student has that ID, or
- the student has no scores yet. Use option 2 first.

## 6. Option 4: Print class average

Shows the average of all students who have scores, then lists them ranked from the highest average to the lowest.

**Example**

```
Class average: 81.67

Rank   Id number  student_average
--------------------------------
1      101        85.00
2      102        78.33
```

- Only students who have scores (option 2) are included.
- If no averages have been calculated yet, the program says so.
- Students with the same average keep the order in which their scores were first entered.

## 7. Option 5: Exit program

Prints `Exiting program. Goodbye!` and closes the program. All records are lost when the program exits.

## 8. Quick start

A typical session:

1. Choose **1** to add each student.
2. Choose **2** to enter scores for each student.
3. Choose **3** to print a student's report card.
4. Choose **4** to see the class average and ranking.
5. Choose **5** to exit.

## 9. Troubleshooting

| Message | What it means | What to do |
|---------|---------------|------------|
| `Invalid option. Please enter a number from 1 to 5.` | The menu choice was not 1 to 5 | Enter a number from 1 to 5 |
| `A student with id ... already exists.` | That ID is already used | Use a different ID |
| `The student list is full.` | 5 students have already been added | No more students can be added |
| `Student with id ... is not registered.` | No student has that ID | Add the student with option 1 first |
| `Student ... does not have an average yet.` | No scores have been entered for this student | Use option 2 first |
| `Invalid score.` | The score was not a number from 0 to 100 | Enter a number from 0 to 100 |
| `No student averages have been calculated yet.` | No student has scores | Use option 2 first |
