#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100
#define FILE_NAME "students.txt"

typedef struct
{
    char id[9];
    char name[50];
    int age;
    float gpa;
} Student;

// global
extern Student students[MAX_STUDENTS];
extern int student_count;

// functions
void show_student();
void add_student();
void delete_student();
void update_student();
void search_student();
void sort_by_gpa();
void sort_by_name();
void save_students_to_file();
void load_students_from_file();

#endif