#include <fstream>
#include <iostream>
#include "interface.h"

void incorrect_input () {
    std::cout << 
        "|****************************************************************************|\n"
        "|                                    MENU                                    |\n"
        "|                               Incorrect input                              |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "Enter something to continue ...                                             |\n"
        " >>> ";
        std::string tmp;
        std::cin.get();
        std::getline(std::cin, tmp);
}
void read_file_error () {
    std::cout << 
        "|****************************************************************************|\n"
        "|                                    MENU                                    |\n"
        "|                           Error with reading file                          |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "|____________________________________________________________________________|\n"
        "Enter something to continue ...                                              \n"
        " >>> ";
        std::string tmp;
        std::cin.get();
        std::getline(std::cin, tmp);
}

void unknown_symbols_in_text() {
    std::cout << 
        "|****************************************************************************|\n"
        "|                                    MENU                                    |\n"
        "|                 Error: There are unknown symbols in text                   |\n"
        "|                 (symbols are not in the alphabet)                          |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "|____________________________________________________________________________|\n"
        "Enter something to continue ...                                             |\n"
        " >>> ";
        std::string tmp;
        std::cin.get();
        std::getline(std::cin, tmp);
}

void decode_error() {
    std::cout << 
        "|****************************************************************************|\n"
        "|                                    MENU                                    |\n"
        "|                 Error: cannot decode text with given alphabet              |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "|____________________________________________________________________________|\n"
        "Enter something to continue ...                                             |\n"
        " >>> ";
        std::string tmp;
        std::cin.get();
        std::getline(std::cin, tmp);
}

std::string choose_filename() {
    std::string res;
    std::cout << 
        "|****************************************************************************|\n"
        "|                                    MENU                                    |\n"
        "|                 Введите имя файла с закодированным текстом                 |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "|                                                                            |\n"
        "|____________________________________________________________________________|\n"
        " >>> ";
        std::cin >> res;
        return res;
}

int get_input(int min, int max) {
    int res;
    std::string input;
    std::cin >> input;
    // порядковый номер в таблице аски для цифры равен 48 + номинал цифры
    res = int(input[0]) - 48;

    if (res < min  || res > max) {
        res = INCORRECT_INPUT;
    }
    return res;
}
