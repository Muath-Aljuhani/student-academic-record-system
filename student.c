#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

/*
 * Displays the main menu choices to the user.
 */
void display_menu(void) {
    printf("\n=== Student Academic Record System ===\n");
    printf("1. Add New Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student by ID\n");
    printf("4. Save Records to File\n");
    printf("5. Load Records from File\n");
    printf("6. Exit\n");
    printf("Select an option (1-6): ");
}

/*
 * Prompts user for student data and appends it to the array.
 */
void add_student(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Error: Maximum student capacity reached.\n");
        return;
    }

    Student new_student;
    printf("\nEnter Student ID: ");
    scanf("%d", &new_student.id);

    /* Clear input buffer */
    while (getchar() != '\n');

    printf("Enter Student Name: ");
    fgets(new_student.name, MAX_NAME_LENGTH, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0;

    printf("Enter GPA (0.00 - 4.00): ");
    scanf("%f", &new_student.gpa);

    printf("Enter Credit Hours: ");
    scanf("%d", &new_student.credit_hours);

    students[*count] = new_student;
    (*count)++;

    printf("Student record added successfully.\n");
}

/*
 * Prints all recorded student records in a formatted table.
 */
void display_all_students(const Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n%-10s %-25s %-10s %-12s\n", "ID", "Name", "GPA", "Credit Hours");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10d %-25s %-10.2f %-12d\n",
               students[i].id,
               students[i].name,
               students[i].gpa,
               students[i].credit_hours);
    }
}

/*
 * Searches for a student by ID and displays their details.
 */
void search_student_by_id(const Student students[], int count) {
    if (count == 0) {
        printf("\nNo records available to search.\n");
        return;
    }

    int search_id;
    printf("\nEnter Student ID to search: ");
    scanf("%d", &search_id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == search_id) {
            printf("\n--- Student Found ---\n");
            printf("ID:           %d\n", students[i].id);
            printf("Name:         %s\n", students[i].name);
            printf("GPA:          %.2f\n", students[i].gpa);
            printf("Credit Hours: %d\n", students[i].credit_hours);
            return;
        }
    }

    printf("Student with ID %d not found.\n", search_id);
}

/*
 * Saves all student array records into a CSV formatted file.
 */
void save_records_to_file(const Student students[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%.2f,%d\n",
                students[i].id,
                students[i].name,
                students[i].gpa,
                students[i].credit_hours);
    }

    fclose(file);
    printf("Records saved successfully to '%s'.\n", filename);
}

/*
 * Reads student records from a CSV formatted file.
 */
void load_records_from_file(Student students[], int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Notice: No existing data file found (%s).\n", filename);
        return;
    }

    *count = 0;
    while (fscanf(file, "%d,%49[^,],%f,%d\n",
                  &students[*count].id,
                  students[*count].name,
                  &students[*count].gpa,
                  &students[*count].credit_hours) == 4) {
        (*count)++;
        if (*count >= MAX_STUDENTS) break;
    }

    fclose(file);
    printf("Loaded %d record(s) from '%s'.\n", *count, filename);
}