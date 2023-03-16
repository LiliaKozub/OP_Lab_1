//
// Created by user on 09.03.2023.
//
#include <iostream>
#include "c_style_program.h"
#include <string.h>
#include <string>
#include <conio.h>
#include <windows.h>
#define MAX_IDENTIFIERS 1000
using namespace std;

//Функція, що зчитує текст з клавіатури
char* input_code_c(char* input) {
    cout << "Input text of code and press Ctrl+D to stop input:\n" << endl;
    while (1) {
        if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('D')) {
            break;
        }
        else {
            char c = _getch();
            if (c == '\r') {
                printf("\n");
                strcat(input, "\n");
            }
            else if (!(GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('D'))) { // додано умову для перевірки ctrl+d
                cout << c;
                strncat(input, &c, 1);
            }
        }
    }
    return input;
}

//Функція, що записує зчитаний текст у файл
void write_data_to_file_c(char *filename, char *input) {
    FILE *outfile;
    outfile = fopen(filename, "w");
    if (outfile == NULL) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    fputs(input, outfile);
    fclose(outfile);
}

//Функція, що виводить вміст файлу на екран
void output_data_from_file_c(char* filename) {
    cout<< "\nThe contents of file: " << filename << endl;
    FILE* input_file = fopen(filename, "r");
    if (input_file == NULL) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    char line[1024];
    while (fgets(line, 1024, input_file)) {
        cout << line;
        if((ftell(input_file))==0)
            printf("The file is empty\n");
    }

    fclose(input_file);
}

//Функція для доповнення файлу
void append_text_c(char* filename) {
    char append_input[1024];
    int choice = -1;
    while (choice != 1 && choice != 0) {
        cout << "\nDo you want to add to file?\nYes - enter ""1""\nNo - enter ""0""\n";
        cin >> choice;
        if (choice != 1 && choice != 0) {
            cout <<"Invalid input! Please enter either ""1"" or ""0""\n";
        }
    }
    if (choice == 1) {
        cout << "\nWrite text you want add\n";
        input_code_c(append_input);
        FILE* outfile = fopen(filename, "a");
        if (outfile == NULL) {
            cout << "Unable to open file!\n";
            exit(EXIT_FAILURE);
        }
        fputs(append_input, outfile);
        fclose(outfile);
    }
    output_data_from_file_c(filename);
}

// Функція, яка перевіряє, чи перед "=" стоїть логічний оператор
int is_logical_operator_c(char* sub_str, char* sub_str2) {
    return (strcmp(sub_str, "<=") == 0 || strcmp(sub_str, ">=") == 0 || strcmp(sub_str, "!=") == 0 || strcmp(sub_str2, "=") == 0);
}

// Функція, яка шукає ідентифікатор у рядку
/*char* find_identifier_c(char* line, size_t pos) {
    char* identifier = (char*) malloc(100 * sizeof(char));
    memset(identifier, '\0', 100);
    size_t assign_pos = strstr(line, "=") - line;
    if (assign_pos != -1) {
        while (assign_pos > 0 && line[assign_pos - 1] == ' ') {
            memmove(&line[assign_pos - 1], &line[assign_pos], strlen(line) - assign_pos + 1);
            assign_pos--;
        }
    }
    if (pos < strlen(line) && line[pos] == '=') {
        while (pos + 1 < strlen(line) && line[pos + 1] == ' ') {
            memmove(&line[pos + 1], &line[pos + 2], strlen(line) - pos);
        }
    }
    size_t space_pos = strcspn(line, " ");
    if (space_pos != -1 && space_pos < pos) {
        strncpy(identifier, &line[space_pos + 1], pos - space_pos - 1);
    }
    else {
        strncpy(identifier, line, pos);
    }
    size_t assign_pos2 = strrchr(identifier, '=') - identifier;
    if (assign_pos2 != -1) {
        identifier[assign_pos2] = '\0';
    }
    return identifier;
}*/


char* find_identifier_c(char* line, size_t pos) {
    char* identifier = (char*) malloc(sizeof(char) * strlen(line) + 1);
    strcpy(identifier, "");

    // видаляємо всі пробіли перед першим символом у рядку
    size_t first_non_space = strspn(line, " ");
    if (first_non_space != strlen(line) && first_non_space > 0) {
        memmove(line, line + first_non_space, strlen(line) - first_non_space + 1);
        pos -= first_non_space;
    }

    size_t assign_pos = strstr(line, "=") - line;
    if (assign_pos != strlen(line)) {
        while (assign_pos > 0 && line[assign_pos - 1] == ' ') {
            memmove(line + assign_pos - 1, line + assign_pos, strlen(line) - assign_pos + 1);
            assign_pos--;
        }
    }
    if (pos < strlen(line) && line[pos] == '=') {
        while (pos + 1 < strlen(line) && line[pos + 1] == ' ') {
            memmove(line + pos + 1, line + pos + 2, strlen(line) - pos);
        }
    }
    size_t space_pos = strstr(line, " ") - line;
    if (space_pos != strlen(line) && space_pos < pos) {
        strncpy(identifier, line + space_pos + 1, pos - space_pos - 1);
        identifier[pos - space_pos - 1] = '\0';
    }
    else {
        strncpy(identifier, line, pos);
        identifier[pos] = '\0';
    }

    size_t assign_pos2 = strrchr(identifier, '=') - identifier;
    if (assign_pos2 != strlen(identifier)) {
        memmove(identifier + assign_pos2, identifier + assign_pos2 + 1, strlen(identifier) - assign_pos2);
    }

    return identifier;
}


// Функція, яка перевіряє, чи є ідентифікатор у масиві ідентифікаторів
int is_unique_identifier_c(char* identifier, char** identifiers, int num_identifiers, size_t pos, char* line) {
    int is_unique = 1;
    for (int i = 0; i < num_identifiers; i++) {
        if (strcmp(identifier, identifiers[i]) == 0) {
            is_unique = 0;
            break;
        }
    }
    if (is_unique) {
        if (!is_logical_operator_c(line + pos - 1, line + pos + 1)) {
            return 1;
        }
    }
    return 0;
}

// Функція, яка знаходить унікальні ідентифікатори в файлі
void find_unique_identifiers_c(char* filename, char** identifiers, int* num_identifiers) {
    FILE* infile = fopen(filename, "r");
    if (!infile) {
        printf("Error opening file\n");
        exit(1);
    }

    char line[1000];
    while (fgets(line, 1000, infile)) {
        size_t pos = strcspn(line, "=");
        if (pos != strlen(line) && line[pos] == '=') {
            char sub_str[3] = {0};
            strncpy(sub_str, line + pos - 1, 2);
            char sub_str2[2] = {0};
            strncpy(sub_str2, line + pos + 1, 1);
            if (is_logical_operator_c(sub_str, sub_str2)) {
                continue;
            }
            char* identifier = find_identifier_c(line, pos);
            if (is_unique_identifier_c(identifier, identifiers, *num_identifiers, pos, line)) {
                identifiers[*num_identifiers] = identifier;
                (*num_identifiers)++;
            }
            else {
                free(identifier);
            }
        }
    }
    fclose(infile);
}

//Функція, яка створює файл з ідентифікаторами
void make_file_with_identifiers_c(char* filename, int* num_identifiers, char** identifiers) {
    FILE* ident_file;
    ident_file = fopen(filename, "w");
    if (ident_file == NULL) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < *num_identifiers; i++) {
        fprintf(ident_file, "%s\n", identifiers[i]);
    }
    fclose(ident_file);
}

//Функція, яка сортує ідентифікатори в лексикографічному порядку
void sort_identifiers_c(int *num_identifiers, char **identifiers){
    for (int i = 0; i < *num_identifiers - 1; i++) {
        for (int j = 0; j < *num_identifiers - i - 1; j++) {
            if (strcmp(identifiers[j], identifiers[j + 1]) > 0) {
                char *temp = identifiers[j];
                identifiers[j] = identifiers[j + 1];
                identifiers[j + 1] = temp;
            }
        }
    }
}

//Функція, яка записує вже відсортовані ідентифікатори в новий файл
void write_sorted_identifiers_to_file_c(char *filename, int *num_identifiers, char **identifiers){
    FILE *sortfile = fopen(filename, "w");
    if (sortfile == NULL) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < *num_identifiers; i++) {
        fprintf(sortfile, "%s\n", identifiers[i]);
    }
    fclose(sortfile);
}
