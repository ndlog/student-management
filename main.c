#include <stdio.h>
#include <string.h>
#include "student.h"

void display_menu()
{
    printf("\n----Student management system-----\n");
    printf("1. Display list of students\n");
    printf("2. Add student\n");
    printf("3. Delete student\n");
    printf("4. Update student\n");
    printf("5. Search student\n");
    printf("6. Sort students by GPA\n");
    printf("7. Sort students by name\n");
    printf("8. Save students to file\n");
    printf("9. Load students from file\n");
    printf("0. Exit\n");
    printf("---------------------------------\n");
    printf("Select a function: ");
}

int main()
{
    load_students_from_file();

    int choice;
    char input[50];

    do
    {
        display_menu();

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        int value;
        char extra;

        if (sscanf(input, "%d %c", &value, &extra) != 1)
        {
            printf("Invalid input.\n");
            continue;
        }

        choice = value;

        switch (choice)
        {
            case 1: show_student(); break;
            case 2: add_student(); break;
            case 3: delete_student(); break;
            case 4: update_student(); break;
            case 5: search_student(); break;
            case 6: sort_by_gpa(); break;
            case 7: sort_by_name(); break;
            case 8: save_students_to_file(); break;
            case 9: load_students_from_file(); break;
            case 0:
                if (student_count > 0)
                save_students_to_file();
                printf("Exit program.\n");
                break;  
            default: printf("Invalid choice, Please choose again.\n");
        }

    } while (choice != 0);

    return 0;
}