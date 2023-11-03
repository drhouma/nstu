#include "algorithms.h"
#include "interface.h"

int main () {
    std::map<std::string, code_string> coded_alphabet; 


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
                "|     1.probability1.txt                                                     |\n"
                "|     2.probability2.txt                                                     |\n"
                "|     3.p_ravn.txt                                                           |\n"
                "|     4.Ввести имя файла самостоятельно                                      |\n"
                "|____________________________________________________________________________|\n"
                " >>> ";
                action = get_input(1, 4);
                if (action != INCORRECT_INPUT) {
                    std::string filename;
                    if (action == 1) {
                        filename = "files/probability1.txt";
                    } else if (action == 2) {
                        filename = "files/probability2.txt";
                    } else if (action == 3) {
                        filename = "files/p_ravn.txt";
                    } else if (action == 4) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::cin >> filename; 
                    } 
                    std::fstream file(filename, std::ios::in);
                    if (file.is_open()) {
                        // переменная для избыточности
                        double redundancy{0}, mid_len;
                        try {
                            coded_alphabet = get_coded_alphabet(file,redundancy, mid_len);
                        } catch (std::invalid_argument e)  {
    
                            read_file_error();
                            // continue;
                        }
                        double len{0};
                        std::cout << "Полученный алфавит:\n";
                        for (auto& elem : coded_alphabet) {
                            std::cout << elem.first << ' ' << elem.second << '\n';
                        }
                        std::cout << "Средняя длина символа: " << mid_len << '\n';
                        std::cout << "Избыточность: " << redundancy << '\n';
                        if (check_kraft(coded_alphabet)) {
                            std::cout << "Неравенство крафта истинно\n";
                        } else {
                            std::cout << "Неравенство крафта ложно\n";
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
                "|     1.text1.txt                                                            |\n"
                "|     2.text2.txt                                                            |\n"
                "|     3.text_ravn.txt                                                        |\n"
                "|     4.Ввести имя файла самостоятельно                                      |\n"
                "|                                                                            |\n"
                "|____________________________________________________________________________|\n"
                " >>> ";
                action = get_input(1, 4);
                if (action != INCORRECT_INPUT) {
                    std::string filename;
                    if (action == 1) {
                        filename = "files/text1.txt";
                    } else if (action == 2) {
                        filename = "files/text2.txt";
                    } else if (action == 3) {
                        filename = "files/text_ravn.txt";
                    } else if (action == 4) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::getline(std::cin, filename);
                        std::cin >> filename; 
                    } 
                    std::fstream file(filename, std::ios::in);
                    bool out = 0;
                    if (file.is_open()) {
                        while (!file.eof() && !out) {
                            std::string tmp;
                            std::getline(file, tmp);
                            // for (int i = 0; i < tmp.size() && !out; i++) {
                            //     if (coded_alphabet.count(tmp[i]) == 0) {
                            //         unknown_symbols_in_text();
                            //         out = 1;
                            //     }
                            // }
                        }
                        if (!out) {
                            std::fstream file(filename, std::ios::in);
                            std::fstream file_to_write(choose_filename(), std::ios::out);
                            cypher_file(file, file_to_write, coded_alphabet);
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
                "|     1.coded_t1_p1.txt                                                      |\n"
                "|     2.coded_t1_p2.txt                                                      |\n"
                "|     3.coded_t2_p1.txt                                                      |\n"
                "|     4.coded_t2_p2.txt                                                      |\n"
                "|     5.Ввести имя файла самостоятельно                                      |\n"
                "|                                                                            |\n"
                "|                                                                            |\n"
                "|____________________________________________________________________________|\n"
                " >>> ";
                action = get_input(1, 5);
                if (action != INCORRECT_INPUT) {
                    std::string filename;
                    if (action == 1) {
                        filename = "files/coded_t1_p1.txt";
                    } else if (action == 2) {
                        filename = "files/coded_t1_p2.txt";
                    } else if (action == 3) {
                        filename = "files/coded_t2_p1.txt";
                    } else if (action == 4) {
                        filename = "files/coded_t2_p2.txt";
                    } else if (action == 5) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::getline(std::cin, filename);
                        std::cin >> filename; 
                    } 
                    std::fstream file(filename, std::ios::in);
                    if (!file.is_open()) {
                        read_file_error();
                        continue;
                    }
                    std::fstream file_to_write(choose_filename(), std::ios::out);
                    try {
                        decypher(file, file_to_write, coded_alphabet);
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