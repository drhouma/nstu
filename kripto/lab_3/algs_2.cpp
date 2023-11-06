#include "hamming_algo.h"
#include "matrix/matrix_oop.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int getCheckBit(const code_str& s1, const code_str &s2) {
    int counter {0};
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] == '1') {
            counter++;
        }
        if (s2[i] == '1') {
            counter++;
        }
    }
    return (counter % 2) == 0 ? 0 : 1; // если четное - 0, иначе 1
}
// помехоустойчивое кодирование
void noNoiseCypher(std::fstream &file_in, std::fstream &file_out, const std::map<std::string, code_str>& coded_alphabet) {
    std::string tmp;
    std::set<int> help;
    std::string zeros = "0000"; // zeros str with size equal to code string size
    for (auto &elem : coded_alphabet) {
        help.emplace(elem.first.length());
    }
    int edge = 3; // каждый третий символ будет суммой по модулю 2 двух предыдущих
    int counter = 1;
    std::string first_code;
    std::string second_code;
    while (!file_in.eof()) {
        std::string output{""};
        std::getline(file_in, tmp);
        for (int cur_pos{0}; cur_pos < tmp.length();) {
            bool end = false;
            if (counter < 3) {
                counter++;         
                for (auto it = help.begin(); !end && it != help.end(); ++it) {
                    for (auto &elem : coded_alphabet) {
                        if (!end && elem.first.length() == *it && !tmp.compare(cur_pos, *it, elem.first)) {
                            end = true;
                            cur_pos += *it;
                            file_out << elem.second;
                            if (counter == 2) {
                                first_code = elem.second;
                            } else if (counter == 3) {
                                second_code = elem.second;
                            }
                        }
                    }
                }

                if (!end) throw std::invalid_argument("cannot cypher with this alphabet");
            } else {
                counter = 1;
                file_out << getCheckBit(first_code, second_code);
            }
        }
    }
    // to check last character, if they weren't checked in cycle
    if (counter == 3) {
        file_out << getCheckBit(first_code, second_code);
    } else if (counter == 2) {
        file_out << getCheckBit(first_code, zeros);
    }
}

void checkErrorsDecypher(std::fstream &input, std::fstream &output, std::map<std::string, code_str> alph) {
    std::string source;
    std::fstream errors("files/errors/no_noise_errors.txt");
    std::string zeros = "0000";
    fs::resize_file("files/errors/no_noise_errors.txt", 0);
    errors.seekp(0);
    std::pair<std::string, code_str> f, s;
    int ctr = 1;
    int len = 4, edge = 3, word = 0;
    while (!input.eof()) {
        int cur_pos = 0;
        // std::string first, second;
        std::getline(input, source);
        while( cur_pos < source.size() ) {
            if (source.size() - cur_pos >= len*2 + 1) {
                bool finded1{false}, finded2{false};
                auto str1 = source.substr(cur_pos, len);
                auto str2 = source.substr(cur_pos + len, len);

                for (auto it = alph.begin(); (!finded1 || !finded2) && it != alph.end(); ++it) {
                    if (str1 == it->second) {
                        f = *it;
                        finded1 = true;
                    }
                    if (str2 == it->second) {
                        s = *it;
                        finded2 = true;
                    }
                }
                int bit{-1};
                if (finded1 && finded2) {
                    bit = getCheckBit(str1, str2);
                }
                if (finded1 && finded2 && (source[cur_pos + len * 2] - 48) == bit) {
                    output << f.first << s.first;
                } else {
                    errors << "error in source file in positions : '" << str1 << "' and '" << str2 << "'\n";
                }
                word+=2;
                cur_pos += 9;
            } else if (source.size() - cur_pos >= len + 1) {
                bool finded1{false};
                auto str1 = source.substr(cur_pos, len);

                for (auto it = alph.begin(); !finded1 && it != alph.end(); ++it) {
                    if (str1 == it->second) {
                        f = *it;
                        finded1 = true;
                    }
                }
                int bit{-1};
                if (finded1) {
                    bit = getCheckBit(str1, zeros);
                }
                if (finded1 && (source[cur_pos + len] - 48) == bit) {
                    output << f.first;
                } else {
                    errors << "error in source file in words : '" << str1 << "'\n";
                }
                cur_pos += 5;
            } else {
                errors << "error in source file: invalid number of symbols";
                cur_pos += 5;
            }

        }
    }
    errors.close();
}

int hammingDistanceStr(const std::string &str1, const std::string &str2) {
    int sum{0};
    for (int i = 0; i < str1.size(); i++) {
        if (str1[i] != str2[i]) {
            sum++;
        }
    }
    return sum;
}
int factorial(int n) {
    int res = 1;
    for (int i = 1; i < n + 1; i++) {
        res *= i;
    }
    return res;
}

int numberOfCombinations(int n, int k) {
    return factorial(n) / (factorial(n-k) * factorial(k));
}

int hammingDistance(std::map<std::string, code_str> alph, int& lessDistance) {
    lessDistance = 1000000;
    int sum{0};
    for (auto &elem1 : alph) {
        for (auto &elem2 : alph) {
            if (elem1 != elem2) {
                auto tmp = hammingDistanceStr(elem1.second, elem2.second);
                sum += tmp;
                if (lessDistance < tmp) {
                    lessDistance = tmp;
                }
            }
        }
    }
    return sum;
}

/// @brief считает границу Хэмминга  
/// @param q кол-во ошибок источника    
/// @param n кол-во символов в закодированном сообщении
/// @param k кол-во информационных разрядов
/// @return выполняется или нет
bool hammingBorder(int q, int n, int k) {
    int right{0}, left{0};
    for (int i = 0; i <= q; i++) {
        right += log2(numberOfCombinations(n, q));
    }
    left = n - k;
    return left >= right;
}