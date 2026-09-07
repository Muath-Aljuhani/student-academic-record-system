#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

/*
 * Student Structure Definition
 * Represents an academic record for an individual student.
 */
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float gpa;
    int credit_hours;
} Student;

/* Function Declarations */
void display_menu(void);
void add_student(Student students[], int *count);
void display_all_students(const Student students[], int count);
void search_student_by_id(const Student students[], int count);
void save_records_to_file(const Student students[], int count, const char *filename);
void load_records_from_file(Student students[], int *count, const char *filename);

#endif /* STUDENT_H */