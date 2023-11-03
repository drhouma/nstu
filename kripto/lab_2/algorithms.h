#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <exception>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <set>

typedef std::string code_string;

void noNoiseCypher(std::fstream &file_in, std::fstream &file_out, const std::map<std::string, code_string>& coded_alphabet);

void checkErrorsDecypher(std::fstream &input, std::fstream &output, std::map<std::string, code_string> alph);

// функция преобразует данный ансамбль элементов в взаимосоответствующие пары (символ - код)
std::map<std::string, code_string> get_coded_alphabet(std::fstream &prob, double& redundancy, double& mid_len);

// алгоритм гильберта
std::map<char, std::string> gilbert_alg(std::vector<std::pair<double, char>> probs);

// функция преобразует данный ансамбль элементов в взаимосоответствующие пары (символ - код)
std::map<char,std::string> shennon_alg(std::multimap<double, char, std::greater<double>> probs, std::string code, char next);
// функция расшифровывает текст input через коды alph, записывает результат в output
void decypher(std::fstream &input, std::fstream &output, std::map<std::string, code_string> alph);

// функция считывает данные из файла prob и получает коды шифрования символов, также записывает избыточность в redundancy
std::map<std::string, code_string> gilbert_alg(std::vector<std::pair<double, std::string>> probs) ;
// шифрует файл file_in через коды шифрования символов coded_alphabet, результат записывает в file_out
void cypher_file(std::fstream &file_in, std::fstream &file_out, const std::map<std::string, code_string>& coded_alphabet);

// вычисляет избыточность ансамбля probs
double eval_redundancy(const std::vector<std::pair<double, std::string>>& probs, double mid_len) ;

// проверяет неравенство Крафта
bool check_kraft(std::map<std::string, code_string> &M);