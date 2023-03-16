//
// Created by user on 09.03.2023.
//

#ifndef UNTITLED66_C__STYLE_PROGRAM_H
#define UNTITLED66_C__STYLE_PROGRAM_H

#endif //UNTITLED66_C__STYLE_PROGRAM_H
#include <string>
using namespace std;

//Функція, що зчитує текст з клавіатури
string input_code(string input);

//Функція, що записує зчитаний текст у файл
void write_data_to_file(string filename, string input);

//Функція, що виводить вміст файлу на екран
void output_data_from_file(string filename);

//Функція для доповнення файлу
void append_text(string filename);

// Функція, яка перевіряє, чи перед "=" стоїть логічний оператор
bool is_logical_operator(string sub_str, string sub_str2);

// Функція, яка шукає ідентифікатор у рядку
string find_identifier(string line, size_t pos);

// Функція, яка перевіряє, чи є ідентифікатор у масиві ідентифікаторів
bool is_unique_identifier(string identifier, string *identifiers, int num_identifiers, size_t pos, string line);

// Функція, яка знаходить унікальні ідентифікатори в файлі
void find_unique_identifiers(string filename, string *identifiers, int &num_identifiers);

//Функція, яка створює файл з ідентифікаторами
void make_file_with_identifiers(string filename, int &num_identifiers, string *identifiers);

//Функція, яка сортує ідентифікатори в лексикографічному порядку
void sort_identifiers(int &num_identifiers, string *identifiers);

//Функція, яка записує вже відсортовані ідентифікатори в новий файл
void write_sorted_identifiers_to_file(string filename, int &num_identifiers, string *identifiers);