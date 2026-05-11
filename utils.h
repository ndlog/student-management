#ifndef UTILS_H
#define UTILS_H

void trim(char *str);
void normalize_spaces(char *str);
void to_uppercase(char str[]);
int is_back_command(const char *str);

int input_required(char *buffer, int size, const char *message);
int input_int(const char *message, int min, int max);
int input_int_optional(const char *message, int min, int max, int *out);

float input_float(const char *message, float min, float max);
int input_float_optional(const char *message, float min, float max, float *out);

int verify_yes_or_no();
int is_valid_name(char name[]);
int is_id_format(char str[]);
void clear_input_buffer();

int find_student_by_id(char id[]);
int find_student_by_name(char name[]);

#endif