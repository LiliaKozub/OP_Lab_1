#include <iostream>
#include "c++_style_program.h"
#include "c_style_program.h"
#include <string>
#include <string.h>


#define MAX_IDENTIFIERS 1000
using namespace std;

int main(int argc, char* argv[]) {

    char mode[]="-mode";
    char mode1[]="FilePointer";
    char mode2[]="FileStream";

    if(argc!=3 || strcmp(argv[1], mode)!=0){
        cout<< "Run the program with particular mode!\n" << ".exe -mode FilePointer/FileStream\n";
    }
    else if(!strcmp(argv[2], mode1)){
        cout << "FilePointer\n";
        char filename1_c[17] = "text_code_c.txt";
        char filename2_c[17] = "identifiers.txt";
        char filename3_c[25] = "sorted_identifiers.txt";
        char *input_c = new char[MAX_IDENTIFIERS]{};
        char* identifiers_c[100] = {0};
        int num_identifiers = 0;

        input_c = input_code_c(input_c);
        cout << "\nYour code:" << endl;
        cout << input_c << endl;
        write_data_to_file_c(filename1_c, input_c);
        append_text_c(filename1_c);
        find_unique_identifiers_c(filename1_c, identifiers_c, &num_identifiers);
        make_file_with_identifiers_c(filename2_c, &num_identifiers, identifiers_c);
        output_data_from_file_c(filename2_c);
        sort_identifiers_c(&num_identifiers, identifiers_c);
        write_sorted_identifiers_to_file_c(filename3_c, &num_identifiers, identifiers_c);
        output_data_from_file_c(filename3_c);

        delete [] input_c;
    }
    else if(!strcmp(argv[2], mode2)){
        cout << "FileStream\n";
        string input = "";
        string filename1 =  "text_code.txt";
        string filename2 = "identifiers.txt";
        string filename3 = "sorted_identifiers.txt";
        string identifiers[MAX_IDENTIFIERS];
        int num_identifiers = 0;

        input = input_code(input);
        cout << "\nYour code:" << endl;
        cout << input << endl;
        write_data_to_file(filename1, input);
        append_text(filename1);
        find_unique_identifiers(filename1, identifiers, num_identifiers);
        make_file_with_identifiers(filename2, num_identifiers, identifiers);
        output_data_from_file(filename2);
        sort_identifiers(num_identifiers, identifiers);
        write_sorted_identifiers_to_file(filename3, num_identifiers, identifiers);
        output_data_from_file(filename3);

    }
    else{
        cout << "The only modes are FilePointer/FileStream\n";
    }


    return 0;
}

