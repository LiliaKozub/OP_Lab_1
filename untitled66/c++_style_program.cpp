#include "c++_style_program.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

//Функція, що зчитує текст з клавіатури
 string input_code(string input){
     bool loop = true;
     cout << "Input text of code and press Ctrl+D to stop input:\n";
     while (loop) {
         if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('D')) {
             loop = false;
         }
         else {
             char c = _getch();
             if (c == '\r') {
                 cout << "\n";
                 input += "\n";
             }
             else if (!(GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('D'))) {
                 cout << c;
                 input += c;
             }
         }
     }
     return input;
 }

//Функція, що записує зчитаний текст у файл
void write_data_to_file(string filename, string input){
    ofstream outfile;
    outfile.open(filename);
    if (!outfile) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    outfile << input;
    outfile.close();

    cout << "Data written to file: " << filename << endl;
}

//Функція, що виводить вміст файлу на екран
void output_data_from_file(string filename){
     cout<< "\n\nThe contents of \"" << filename <<"\"" << " file:" << endl;
    ifstream input_file(filename);
    if (!input_file) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(input_file, line)) {
        cout << line << endl;
    }
    input_file.close();
}

//Функція для доповнення файлу
void append_text(string filename){
    string append_input = "";
    int choice = -1;
    while (choice != 1 && choice != 0) {
        cout << "\nDo you want to add to file?" << endl
             << "Yes - enter \"1\"\nNo - enter \"0\"" << endl;
        cin >> choice;
        if (choice != 1 && choice != 0) {
            cout << "Invalid input! Please enter either ""1"" or ""0""" << endl;
        }
    }
    if(choice == 1){
        cout << "\nWrite text you want add" << endl;
        append_input = input_code(append_input);
        ofstream outfile;
        outfile.open(filename, ios_base::app);
        if (!outfile) {
            cout << "Unable to open file!\n";
            exit(EXIT_FAILURE);
        }
        outfile << append_input;
        outfile.close();
    }
    output_data_from_file(filename);
}


// Функція, яка перевіряє, чи перед "=" стоїть логічний оператор
bool is_logical_operator(string sub_str, string sub_str2) {
    return (sub_str == "<=" || sub_str == ">=" || sub_str == "!=" || sub_str2 == "=");
}

// Функція, яка шукає ідентифікатор у рядку
string find_identifier(string line, size_t pos) {
    string identifier;

    size_t first_non_space = line.find_first_not_of(" ");
    if (first_non_space != string::npos && first_non_space > 0) {
        line.erase(0, first_non_space);
        pos -= first_non_space;
    }

    size_t assign_pos = line.find("=");
    if (assign_pos != string::npos) {
        while (assign_pos > 0 && line[assign_pos - 1] == ' ') {
            line.erase(assign_pos - 1, 1);
            assign_pos--;
        }
    }
    if (pos < line.length() && line[pos] == '=') {
        while (pos + 1 < line.length() && line[pos + 1] == ' ') {
            line.erase(pos + 1, 1);
        }
    }
    size_t space_pos = line.find(" ");
    if (space_pos != string::npos && space_pos < pos) {
        identifier = line.substr(space_pos + 1, pos - space_pos - 1);
    }
    else {
        identifier = line.substr(0, pos);
    }

    size_t assign_pos2 = identifier.find_last_of("=");
    if (assign_pos2 != string::npos) {
        identifier.erase(assign_pos2, 1);
    }

    return identifier;
}



// Функція, яка перевіряє, чи є ідентифікатор у масиві ідентифікаторів
bool is_unique_identifier(string identifier, string *identifiers, int num_identifiers, size_t pos, string line) {
    bool is_unique = true;
    for (int i = 0; i < num_identifiers; i++) {
        if (identifier == identifiers[i]) {
            is_unique = false;
            break;
        }
    }
    if (is_unique) {
        if (!is_logical_operator(line.substr(pos - 1, 2), line.substr(pos + 1, 1))) {
            return true;
        }
    }
    return false;
}

// Функція, яка знаходить унікальні ідентифікатори в файлі
void find_unique_identifiers(string filename, string *identifiers, int &num_identifiers) {
    ifstream infile;
    infile.open(filename);
    if (!infile) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(infile, line)) {
        size_t pos = line.find("=");
        if (pos != string::npos) {
            string sub_str = line.substr(pos - 1, 2);
            string sub_str2 = line.substr(pos + 1, 1);
            if (is_logical_operator(sub_str, sub_str2)) {
                continue;
            }
            string identifier = find_identifier(line, pos);
            if (is_unique_identifier(identifier, identifiers, num_identifiers, pos, line)) {
                identifiers[num_identifiers++] = identifier;
            }
        }
    }
    infile.close();
}

//Функція, яка створює файл з ідентифікаторами
void make_file_with_identifiers(string filename, int &num_identifiers, string *identifiers){
    ofstream ident_file;
    ident_file.open(filename);
    if (!ident_file) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_identifiers; i++) {
        ident_file << identifiers[i] << endl;
    }
    ident_file.close();
}

//Функція, яка сортує ідентифікатори в лексикографічному порядку
void sort_identifiers(int &num_identifiers, string *identifiers){
    for (int i = 0; i < num_identifiers - 1; i++) {
        for (int j = 0; j < num_identifiers - i - 1; j++) {
            if (identifiers[j] > identifiers[j + 1]) {
                swap(identifiers[j], identifiers[j + 1]);
            }
        }
    }
}

//Функція, яка записує вже відсортовані ідентифікатори в новий файл
void write_sorted_identifiers_to_file(string filename, int &num_identifiers, string *identifiers){
    ofstream sortfile;
    sortfile.open(filename);
    if (!sortfile) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_identifiers; i++) {
        sortfile << identifiers[i] << endl;
    }
    sortfile.close();
}
