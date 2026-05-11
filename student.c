#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "student.h"
#include "utils.h"

Student students[MAX_STUDENTS];
int student_count = 0;
static int next_id = 1;

// check if ID exists
int id_exists(char id[])
{
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(students[i].id, id) == 0)
            return 1;
    }
    return 0;
}

// generate new ID 
void generate_id(char id[])
{
    // ưu tiên tái sử dụng ID nhỏ bị thiếu
    for (int num = 1; num < next_id; num++)
    {
        sprintf(id, "ST%06d", num);
        if (!id_exists(id))
            return;
    }

    // nếu không thiếu → dùng ID mới
    sprintf(id, "ST%06d", next_id++);
}

int find_student_by_id(char id[])
{
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(students[i].id, id) == 0)
            return i;
    }
    return -1;
}

int find_student_by_name(char name[])
{
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(students[i].name, name) == 0)
            return i;
    }                
    return -1; // "-1" is not found yet
}


void show_student() {
    if (student_count == 0)
    {
        printf("There are no students to display\n");
        return;
    }

    printf("\nLIST OF STUDENTS\n");
    printf("\n%-10s %-20s %-5s %-5s\n", "ID", "NAME", "AGE", "GPA");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < student_count; i++)
    {
        printf("%-10s %-20s %-5d %-5.2f\n",
           students[i].id,
           students[i].name,
           students[i].age,
           students[i].gpa);
    }
    printf("\nTotal students: %d\n", student_count);
}

void add_student()
{
    if (student_count >= MAX_STUDENTS)
    {
        printf("No more students can be added.\n");
        return;
    }

    Student temp;

    // NAME
    while (1)
    {
        if (!input_required(temp.name, sizeof(temp.name),
                            "Enter name (0 to cancel): "))
        {
            printf("Add cancelled.\n");
            return;
        }

        if (!is_valid_name(temp.name))
        {
            printf("Invalid name.\n");
            continue;
        }
        break;
    }

    // AGE
    int age;
    int result = input_int_optional(
        "Enter age (0 to cancel): ", 18, 59, &age);

    if (result == 0)
    {
        printf("Add cancelled.\n");
        return;
    }
    if (result == -1)
    {
        printf("Invalid age.\n");
        return;
    }

    temp.age = age;

    // GPA
    float gpa;
    result = input_float_optional(
        "Enter GPA (0 to cancel): ", 0, 4, &gpa);

    if (result == 0)
    {
        printf("Add cancelled.\n");
        return;
    }
    if (result == -1)
    {
        printf("Invalid GPA.\n");
        return;
    }

    temp.gpa = gpa;

    generate_id(temp.id);

    // CONFIRM
    printf("\nPreview: %s | %s | %d | %.2f\n",
           temp.id, temp.name, temp.age, temp.gpa);

    if (!verify_yes_or_no())
    {
        printf("Add cancelled.\n");
        return;
    }

    students[student_count++] = temp;

    printf("Student added successfully.\n");
}

void delete_student() {
    if (student_count == 0)
    {
        printf("No students to delete.\n");
        return;
    }

    char id[9];
    input_required(id, sizeof(id), "Enter student ID to delete: ");
    trim(id);
    normalize_spaces(id);
    to_uppercase(id);
    clear_input_buffer();    

    int index = find_student_by_id(id);

    if (index == -1)
    {
        printf("Student not found.\n");
        return;
    }

    printf("Student found: %s (%s) | Age: %d | GPA: %.2f\n",
       students[index].name,
       students[index].id,
       students[index].age,
       students[index].gpa);

    if (!verify_yes_or_no())
    {
        printf("Delete cancelled.\n");
        show_student();
    }
    else
    {
        for (int i = index; i < student_count - 1; i++)
        {
            students[i] = students[i + 1];
        }

        student_count--;
        printf("Student deleted successfully.\n");
        show_student();
    }
}
    
void update_student() {
    if (student_count == 0)
    {
        printf("No students to update.\n");
        return;
    }

    char id[9];
    input_required(id, sizeof(id), "Enter student ID to update: ");  
    trim(id);
    normalize_spaces(id);
    to_uppercase(id);
    clear_input_buffer();    

    int index = find_student_by_id(id);

    if (index == -1)
    {
        printf("Student not found.\n");
        return;
    }

    printf("Student found: %s (%s) | Age: %d | GPA: %.2f\n",
       students[index].name,
       students[index].id,
       students[index].age,
       students[index].gpa);
    
    if (!verify_yes_or_no())
    {
        printf("Update cancelled.\n");
        return;
    }

    char input[50];

    // update new name
    while (1)
    {
        printf("Enter new name (leave blank to keep current): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        trim(input);
        normalize_spaces(input);
        to_uppercase(input);

        if (strlen(input) == 0)
            break;

        if (!is_valid_name(input))
        {
            printf("Invalid name. Please enter again.\n");
            continue;
        }

        strcpy(students[index].name, input);
        break;
    }
    
    // update new age
    while (1)
    {
        int age;
        int result = input_int_optional(
            "Enter new age (leave blank to keep current): ",
            18, 59, &age);

        if (result == 0) break;      // skip
        if (result == -1) continue;  // lỗi → nhập lại

        students[index].age = age;
        break;
    }

    // update new GPA
    while (1)
    {
        float gpa;
        int result = input_float_optional(
            "Enter new GPA (leave blank to keep current): ",
            0, 4, &gpa);

        if (result == 0) break;
        if (result == -1) continue;

        students[index].gpa = gpa;
        break;
    }

    printf("Student updated successfully.\n");
    show_student();
}

void search_student() {
    if (student_count == 0)
    {
        printf("No student to search.\n");
        return;
    }

    char keyword[50];
    input_required(keyword, sizeof(keyword), "Enter name keyword: ");
    trim(keyword);
    normalize_spaces(keyword);
    to_uppercase(keyword);

    // search by id
    if (is_id_format(keyword))
    {
        int index = find_student_by_id(keyword);

        if (index == -1)
        {
            printf("Student not found.\n");
            return;
        }

        printf("\nStudent found:\n");
        printf("%-10s %-20s %-5s %-5s\n", "ID", "NAME", "AGE", "GPA");
        printf("%-10s %-20s %-5d %-5.2f\n",
               students[index].id,
               students[index].name,
               students[index].age,
               students[index].gpa);

        return;
    }

    // search by name
    int found = 0;

    printf("\nMATCHING STUDENTS:\n");
    printf("%-10s %-20s %-5s %-5s\n", "ID", "NAME", "AGE", "GPA");

    for (int i = 0; i < student_count; i++)
    {
        char temp[50];
        strcpy(temp, students[i].name);
        to_uppercase(temp);

        if (strstr(temp, keyword) != NULL)
        {
            printf("%-10s %-20s %-5d %-5.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].age,
                   students[i].gpa);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No student found.\n");
    }
    else
    {
        printf("\nFound %d student(s).\n", found);
    }

}

void sort_by_gpa() {
    if (student_count == 0)
    {
        printf("No student to sort.\n");
        return;
    }

    int swapped;

    for (int i = 0; i < student_count - 1; i++)
    {
        swapped = 0;

        for (int j = 0; j < student_count - i - 1; j++)
        {
            if (students[j].gpa > students[j + 1].gpa)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped) break; // đã sorted
    }

    printf("Sort students by GPA successfully.\n");
    show_student();
}

void sort_by_name() {
    if (student_count == 0)
    {
        printf("No student to sort.\n");
        return;
    }

    for (int i = 0; i < student_count - 1; i++)
    {
        for (int j = 0; j < student_count - i - 1; j++)
        {
            if (strcmp(students[j].name, students[j + 1].name) > 0)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("Sort by name successfully.\n");
    show_student();
}

void save_students_to_file() {
    if (student_count == 0)
    {
        printf("No data to save.\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL)
    {
        printf("Cannot open file to save data.\n");
        return;
    }

    fprintf(file, "ID,NAME,AGE,GPA\n");

    for (int i = 0; i < student_count; i++)
    {
        fprintf(file, "%s,%s,%d,%.2f\n", 
            students[i].id,
            students[i].name,
            students[i].age,
            students[i].gpa);
    }

    fclose(file);
    printf("Saved %d students.\n", student_count);
}

void load_students_from_file() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Cannot open file. Starting with empty list.\n");
        return;
    }

    student_count = 0;
    next_id = 1;

    char line[100];

    fgets(line, sizeof(line), file); // skip header

    while (fgets(line, sizeof(line), file)) {
        Student student;

        if (sscanf(line, "%8[^,],%49[^,],%d,%f",
                   student.id,
                   student.name,
                   &student.age,
                   &student.gpa) == 4)
        {
            if (student_count >= MAX_STUDENTS)
            {
                printf("Max students reached. Stop loading.\n");
                break;
            }

            students[student_count++] = student;

            int num;
            if (sscanf(student.id, "ST%d", &num) == 1)
            {
                if (num >= next_id)
                    next_id = num + 1;
            }
        }
    }

    fclose(file);
    printf("Loaded %d students.\n", student_count);
}