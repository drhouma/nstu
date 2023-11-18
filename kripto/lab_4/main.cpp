#include "interface.h"
#include "digram_coder.h"

int main () {
    Coder coder(123);


    int action = -1;
    
    while (action != 0) {
        std::cout << 
        "|****************************************************************************|\n"
        "|                                    MENU                                    |\n"
        "|    1.Выбрать ключ                                                          |\n"
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
                "|     Выберите ключ:                                                         |\n"
                "|     1.key1                                                                 |\n"
                "|     2.Ввести имя файла самостоятельно                                      |\n"
                "|                                                                            |\n"
                "|                                                                            |\n"
                "|____________________________________________________________________________|\n"
                " >>> ";
                action = get_input(1, 2);
                if (action != INCORRECT_INPUT) {
                    std::string filename;
                    if (action == 1) {
                        filename = "files/keys/key1";
                    } else if (action == 2) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::cin >> filename;
                        filename = "files/keys/" + filename; 
                    } 
                    std::fstream file(filename, std::ios::in);
                    if (file.is_open()) {
                        try {
                            coder = Coder(file);
                        } catch(const std::exception& e) {
                            std::cerr << e.what() << '\n';
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
                "|     1.sequence                                                             |\n"
                "|     2.false_sequence                                                       |\n"
                "|     3.Ввести имя файла самостоятельно                                      |\n"
                "|                                                                            |\n"
                "|                                                                            |\n"
                "|____________________________________________________________________________|\n"
                " >>> ";
                action = get_input(1, 3);
                if (action != INCORRECT_INPUT) {
                    std::string filename;
                    if (action == 1) {
                        filename = "sequence";
                    } else if (action == 2) {
                        filename = "false_sequence";
                    }  else if (action == 3) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::getline(std::cin, filename);
                        std::cin >> filename; 
                    } 
                    std::fstream file("files/" + filename, std::ios::in);
                    bool out = 0;
                    if (file.is_open()) {
                        if (!out) {
                            std::fstream file_to_write("files/output_coding", std::ios::out);
                            try {
                                coder.CodeFile(file, file_to_write);
                                std::cout << "Файл закодирован и сохранен в files/output_coding\n";
                            } catch(const std::exception& e) {
                                std::cerr << e.what() << '\n';
                            }  
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
                "|     1.output_coding                                                        |\n"
                "|     2.Ввести имя файла самостоятельно                                      |\n"
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
                        filename = "output_coding";
                    } else if (action == 2) {
                        std::cout << "Введите имя файла\n>>> ";
                        std::getline(std::cin, filename);
                        std::cin >> filename; 
                    } 
                    std::fstream file("files/" + filename, std::ios::in);
                    if (!file.is_open()) {
                        read_file_error();
                        continue;
                    }
                    std::fstream file_to_write("files/output_decoding", std::ios::out);
                    try {
                        coder.DecodeFile(file, file_to_write);
                        std::cout << "Файл декодирован и сохранен в files/output_decoding\n";
                    } catch (const std::exception& e) {
                        std::cerr << e.what() << '\n';
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