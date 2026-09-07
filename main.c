#include <stdio.h>
#include "student.h"

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice = 0;
    const char *filename = "students.csv";

    /* Load initial records if data file exists */
    load_records_from_file(students, &count, filename);

    while (choice != 6) {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                add_student(students, &count);
                break;
            case 2:
                display_all_students(students, count);
                break;
            case 3:
                search_student_by_id(students, count);
                break;
            case 4:
                save_records_to_file(students, count, filename);
                break;
            case 5:
                load_records_from_file(students, &count, filename);
                break;
            case 6:
                save_records_to_file(students, count, filename);
                printf("Exiting application. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please select between 1 and 6.\n");
        }
    }

    return 0;
}