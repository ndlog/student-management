#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void trim(char *str)
{
    int start = 0;
    while (isspace(str[start]))
        start++;

    int end = strlen(str) - 1;
    while (end >= start && isspace(str[end]))
        end--;

    int i = 0;
    while (start <= end)
    {
        str[i++] = str[start++];
    }
    str[i] = '\0';
}

void normalize_spaces(char *str)
{
    int i = 0, j = 0;
    int space_flag = 0;

    while (str[i])
    {
        if (isspace(str[i]))
        {
            if (!space_flag)
            {
                str[j++] = ' ';
                space_flag = 1;
            }
        }
        else
        {
            str[j++] = str[i];
            space_flag = 0;
        }
        i++;
    }

    str[j] = '\0';
}

void to_uppercase(char str[])
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = toupper(str[i]);
    }
}   

int is_back_command(const char *str)
{
    return strcmp(str, "0") == 0;
}

int input_required(char *buffer, int size, const char *message)
{
    while (1)
    {
        printf("%s", message);
        fgets(buffer, size, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';
        trim(buffer);
        normalize_spaces(buffer);
        to_uppercase(buffer); // optional

        if (is_back_command(buffer))
        {
            return 0; // BACK
        }

        if (strlen(buffer) == 0)
        {
            printf("Input cannot be empty (0 to cancel).\n");
            continue;
        }

        return 1; // OK
    }
}

float input_float(const char *message, float min, float max)
{
    char input[50];

    while (1)
    {
        printf("%s", message);
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';
        trim(input);
        normalize_spaces(input);

        if (strlen(input) == 0)
        {
            printf("Input cannot be empty.\n");
            continue;
        }

        // đổi , → .
        for (int i = 0; input[i]; i++)
        {
            if (input[i] == ',')
                input[i] = '.';
        }

        float value;
        char extra;

        if (sscanf(input, "%f %c", &value, &extra) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (value < min || value > max)
        {
            printf("Value must be between %.1f and %.1f.\n", min, max);
            continue;
        }

        return value;
    }
}

int input_float_optional(const char *message, float min, float max, float *out)
{
    char input[50];

    printf("%s", message);
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';
    trim(input);
    normalize_spaces(input);
    
    if (is_back_command(input))
        return 0; // BACK

    if (strlen(input) == 0)
        return 0; // skip

    for (int i = 0; input[i]; i++)
    {
        if (input[i] == ',')
            input[i] = '.';
    }

    float value;
    char extra;

    if (sscanf(input, "%f %c", &value, &extra) != 1)
    {
        printf("Invalid input.\n");
        return -1;
    }

    if (value < min || value > max)
    {
        printf("Invalid range.\n");
        return -1;
    }

    *out = value;
    return 1;
}

int input_int(const char *message, int min, int max)
{
    char input[50];

    while (1)
    {
        printf("%s", message);
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';
        trim(input);
        normalize_spaces(input);

        if (strlen(input) == 0)
        {
            printf("Input cannot be empty.\n");
            continue;
        }

        int value;
        char extra;

        if (sscanf(input, "%d %c", &value, &extra) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (value < min || value > max)
        {
            printf("Value must be between %d and %d.\n", min, max);
            continue;
        }

        return value;
    }
}

int input_int_optional(const char *message, int min, int max, int *out)
{
    char input[50];

    printf("%s", message);
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';
    trim(input);
    normalize_spaces(input);

    if (is_back_command(input))
        return 0; // BACK

    if (strlen(input) == 0)
        return 0; // skip

    int value;
    char extra;

    if (sscanf(input, "%d %c", &value, &extra) != 1)
    {
        printf("Invalid input.\n");
        return -1;
    }

    if (value < min || value > max)
    {
        printf("Invalid range.\n");
        return -1;
    }

    *out = value;
    return 1;
}

int is_id_format(char str[])
{
    if (strlen(str) != 8)
        return 0;

    if (str[0] != 'S' || str[1] != 'T')
        return 0;

    for (int i = 2; i < 8; i++)
    {
        if (!isdigit(str[i]))
            return 0;
    }

    return 1;
}

int is_valid_name(char name[])
{
    if (strlen(name) == 0)
        return 0;

    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!(isalpha(name[i]) || name[i] == ' '))
        {
            return 0; // not valid
        }
    }
    return 1; // Valid
} 

int verify_yes_or_no()
{
    char input[10];

    while (1)
    {
        printf("Are you sure? (y/n): ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')   // bỏ qua enter
            continue;

        if (tolower(input[0]) == 'y')
            return 1;

        if (tolower(input[0]) == 'n')
            return 0;

        printf("Invalid input. Please enter y or n.\n");
    }
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}