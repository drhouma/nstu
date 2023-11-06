#include "algorithms.h"
#include "interface.h"
#include "hamming_algo.h"

int main () {
    std::map<std::string, code_str> alph;


    int action = -1;
    
    while (action != 0) {
        std::cout << 
        "|****************************************************************************|\n"
        "|                                    MENU                                    |\n"
        "|    1.Выбрать файл с алфавитом и вероятностью символов                      |\n"
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
                "|     Выберите алфавит:                                                      |\n"
                "|     1.p_ravn.txt                                                           |\n"
                "|     2.Ввести имя файла самостоятельно                                      |\n"
                "|                                                                            |\n"
                "|                                                                            |\n"
                "|____________________________________________________________________________|\n"
                " >>> ";
                action = get_input(1, 4);
                if (action != INCORRECT_INPUT) {
                    std::string filename;
                    if (action == 1) {
                        filename = "files/noNoiseFiles/p_ravn.txt";
                    } else if (action == 2) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::cin >> filename; 
                    } 
                    std::fstream file(filename, std::ios::in);
                    if (file.is_open()) {
                        // переменная для избыточности
                        double redundancy{0}, mid_len;
                        try {
                            alph = get_coded_alphabet(file, redundancy, mid_len);
                        } catch (std::invalid_argument e)  {
    
                            read_file_error();
                            // continue;
                        }
                        double len{0};
                        std::cout << "Полученный алфавит:\n";
                        for (auto& elem : alph) {
                            std::cout << elem.first << ' ' << elem.second << '\n';
                        }
                        std::cout << "Enter something to continue ... \n";
                        std::cout << " >>> ";
                        std::string tmp;
                        std::cin.get();
                        std::getline(std::cin, tmp);
        
                    } else {
                        read_file_error();
                    }
                } else {
                    incorrect_input();
                }

            } else if (action == 2) {
                std::cout << 
                "|****************************************************************************|\n"
                "|                                    MENU                                    |\n"
                "|     Выберите текст для кодирования:                                        |\n"
                "|     1.text_ravn.txt                                                        |\n"
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
                        filename = "text_ravn.txt";
                    } else if (action == 2) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::getline(std::cin, filename);
                        std::cin >> filename; 
                    } 
                    std::fstream file("files/noNoiseFiles/" + filename, std::ios::in);
                    bool out = 0;
                    if (file.is_open()) {
                        if (!out) {
                            std::fstream file_to_write("files/noNoiseFiles/" + choose_filename(), std::ios::out);
                            noNoiseCypher(file, file_to_write, alph);
                        }
                    } else {
                        read_file_error();
                    }
                } else {
                    incorrect_input();
                }
            } else if (action == 3) {
                std::cout << 
                "|****************************************************************************|\n"
                "|                                    MENU                                    |\n"
                "|     Выберите текст для декодирования:                                      |\n"
                "|     1.c_ravn.txt                                                           |\n"
                "|     2.c_ravn_err.txt                                                       |\n"
                "|     3.Ввести имя файла самостоятельно                                      |\n"
                "|                                                                            |\n"
                "|                                                                            |\n"
                "|                                                                            |\n"
                "|                                                                            |\n"
                "|____________________________________________________________________________|\n"
                " >>> ";
                action = get_input(1, 2);
                if (action != INCORRECT_INPUT) {
                    std::string filename;
                    if (action == 1) {
                        filename = "c_ravn.txt";
                    } else if (action == 2) {
                        filename = "c_ravn_err.txt";
                    }  else if (action == 3) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::getline(std::cin, filename);
                        std::cin >> filename; 
                    } 
                    std::fstream file("files/noNoiseFiles/" + filename, std::ios::in);
                    if (!file.is_open()) {
                        read_file_error();
                        continue;
                    }
                    std::fstream file_to_write("files/noNoiseFiles/" + choose_filename(), std::ios::out);
                    try {
                        checkErrorsDecypher(file, file_to_write, alph);
                    } catch (std::invalid_argument) {
                        decode_error();
                    }
                } else {
                    incorrect_input();
                }
            }

        } else if (0){
            return 0;
        } else {
            incorrect_input();
        }
    }
    return 0;
}