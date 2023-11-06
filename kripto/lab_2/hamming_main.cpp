#include "hamming_algo.h"
#include "interface.h"

int main () {
    // std::map<std::string, code_string> coded_alphabet; 
    HammingCoding coder("files/hammingFiles/ham_my.txt", 9, 5);
    std::map<std::string, code_str> alph;


    int action = -1;
    
    while (action != 0) {
        std::cout << 
        "|****************************************************************************|\n"
        "|                                    MENU                                    |\n"
        "|    1.Выбрать файл с порождающей матрицей/полиномом                         |\n"
        "|    2.Зашифровать текст                                                     |\n"
        "|    3.Дешифровать текст                                                     |\n"
        "|    0.Выход                                                                 |\n"
        "|                                                                            |\n"
        "|____________________________________________________________________________|\n"
        " >>> ";
        action = get_input(0, 3);
        if (action != INCORRECT_INPUT) {
            if (action == 1) {
                std::cout << 
                "|****************************************************************************|\n"
                "|                                    MENU                                    |\n"
                "|     Выберите файл:                                                         |\n"
                "|     1.ham_my.txt                                                           |\n"
                "|     2.Ввести имя файла с полиномом                                         |\n"
                "|     3.Ввести имя файла с порождающей матрицей                              |\n"
                "|                                                                            |\n"
                "|                                                                            |\n"
                "|____________________________________________________________________________|\n"
                " >>> ";
                action = get_input(1, 3);
                if (action != INCORRECT_INPUT) {
                    std::string filename;
                    if (action == 1) {
                        filename = "files/hammingFiles/ham_my.txt";
                    } else if (action == 2) {
                        std::cin >> filename;
                        filename = "files/hammingFiles/" + filename;
                    } else if (action == 3) {
                        std::cin >> filename;
                        filename = "files/polynoms/" + filename;
                    }
                    int n, k;
                    std::cout << "Введите n\n >>> ";
                    std::cin >> n;
                    std::cout << "Введите k\n >>> ";
                    std::cin >> k;
                    std::fstream file(filename, std::ios::in);
                    coder = HammingCoding(filename, n, k);
                }
            } else if (action == 2) {
                std::cout << 
                "|****************************************************************************|\n"
                "|                                    MENU                                    |\n"
                "|     Выберите текст для кодирования:                                        |\n"
                "|     1.ham_text.txt                                                        |\n"
                "|     2.Ввести имя файла самостоятельно                                      |\n"
                "|                                                                            |\n"
                "|                                                                            |\n"
                "|                                                                            |\n"
                "|____________________________________________________________________________|\n"
                " >>> ";
                action = get_input(1, 4);
                if (action != INCORRECT_INPUT) {
                    std::string filename;
                    if (action == 1) {
                        filename = "ham_text.txt";
                    } else if (action == 2) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::getline(std::cin, filename);
                        std::cin >> filename; 
                    } 
                    std::fstream file("files/hammingFiles/" + filename, std::ios::in);
                    if (file.is_open()) {
                        std::fstream file_to_write("files/hammingFiles/output_coding.txt" , std::ios::out);
                        coder.Coding(file, file_to_write);
                    } else {
                        read_file_error();
                    }
                }
            } else if (action == 3) {
                std::cout << 
                "|****************************************************************************|\n"
                "|                                    MENU                                    |\n"
                "|     Выберите текст для декодирования:                                      |\n"
                "|     1.ham_coded_text.tx                                                    |\n"
                "|     2.output_coding.txt                                                    |\n"
                "|     3.ham_coded_with_error.txt                                             |\n"
                "|     4.Ввести имя файла самостоятельно                                      |\n"
                "|____________________________________________________________________________|\n"
                " >>> ";
                action = get_input(1, 4);
                if (action != INCORRECT_INPUT) {
                    std::string filename;
                    if (action == 1) {
                        filename = "ham_coded_text.txt";
                    } else if (action == 2) {
                        filename = "output_coding.txt";
                    } else if (action == 3) {
                        filename = "ham_coded_with_error.txt";
                    } else if (action == 4) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::getline(std::cin, filename);
                        std::cin >> filename; 
                    } 
                    std::fstream file("files/hammingFiles/" + filename, std::ios::in);
                    if (file.is_open()) {
                        std::fstream file_to_write("files/hammingFiles/output_decoding.txt" , std::ios::out);
                        coder.Decoding(file, file_to_write);
                    } else {
                        read_file_error();
                    }
                }
            }
        }
    }
    return 0;
}