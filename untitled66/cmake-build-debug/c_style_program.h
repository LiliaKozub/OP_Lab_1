//
// Created by user on 09.03.2023.
//

#ifndef UNTITLED66_C_STYLE_PROGRAM_H
#define UNTITLED66_C_STYLE_PROGRAM_H

#endif //UNTITLED66_C_STYLE_PROGRAM_H
#include <iostream>
using namespace std;

//Функція, що зчитує текст з клавіатури
char *input_code_c(char *input);

//Функція, що записує зчитаний текст у файл
void write_data_to_file_c(char *filename, char *input);

//Функція, що виводить вміст файлу на екран
void output_data_from_file_c(char* filename);

//Функція для доповнення файлу
void append_text_c(char* filename);

// Функція, яка перевіряє, чи перед "=" стоїть логічний оператор
int is_logical_operator_c(char* sub_str, char* sub_str2);

// Функція, яка шукає ідентифікатор у рядку
char* find_identifier_c(char* line, size_t pos);

// Функція, яка перевіряє, чи є ідентифікатор у масиві ідентифікаторів
int is_unique_identifier_c(char* identifier, char** identifiers, int num_identifiers, size_t pos, char* line);

// Функція, яка знаходить унікальні ідентифікатори в файлі
void find_unique_identifiers_c(char* filename, char** identifiers, int* num_identifiers);

//Функція, яка створює файл з ідентифікаторами
void make_file_with_identifiers_c(char* filename, int* num_identifiers, char** identifiers);

//Функція, яка сортує ідентифікатори в лексикографічному порядку
void sort_identifiers_c(int *num_identifiers, char **identifiers);

//Функція, яка записує вже відсортовані ідентифікатори в новий файл
void write_sorted_identifiers_to_file_c(char *filename, int *num_identifiers, char **identifiers);