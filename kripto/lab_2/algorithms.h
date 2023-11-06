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
