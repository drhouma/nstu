#pragma once
#include <string>
#define INCORRECT_INPUT -2

// Выводит сообщение о неверных входных данных
void incorrect_input ();
// Выводит сообщение о ошибке чтения файла
void read_file_error ();
// Выводит сообщение о символах, для которых нет кода шифрования
void unknown_symbols_in_text();

// выводит ошибку 
void decode_error();

// пользователь выбирает имя файла
std::string choose_filename();

// получение и проверка ввода
int get_input(int min, int max);

