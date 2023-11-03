#include "algorithms.h"
// #include <filesystem>
#include <experimental/filesystem> 

namespace fs = std::experimental::filesystem;

int getCheckBit(const code_string& s1, const code_string &s2) {
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
void noNoiseCypher(std::fstream &file_in, std::fstream &file_out, const std::map<std::string, code_string>& coded_alphabet) {
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

void checkErrorsDecypher(std::fstream &input, std::fstream &output, std::map<std::string, code_string> alph) {
    std::string source;
    std::fstream errors("errors.txt");
    std::string zeros = "0000";
    fs::resize_file("errors.txt", 0);
    errors.seekp(0);
    std::pair<std::string, code_string> f, s;
    int ctr = 1;
    int edge = 3, row = 0;
    while (!input.eof()) {
        int len = 0, cur_pos = 0;
        // std::string first, second;
        std::getline(input, source);
        while( cur_pos < source.size() ) {
            bool end = false;
            if (ctr != edge) {
                ctr++;
                if (source.length() - cur_pos == 1) {
                    end = true;
                    ctr--;
                }
                for (auto it = alph.begin(); !end &&  it != alph.end(); ++it) {
                    len = it->second.size();
                    if (!source.compare(cur_pos, len, it->second) ){
                        end = true;
                        // output << it->first;
                        if (ctr == 2) {
                            f = *it;
                        } else if (ctr == 3) {
                            s = *it;
                        }
                    }
                }
                if (end == false) {
                    throw std::invalid_argument("can not decode text with given alphabet");
                }
                cur_pos += len;
                row++;
            } else {
                ctr = 1;
                int bit = getCheckBit(f.second, s.second);
                // std::cout << bit  << " source_bit: " << source[cur_pos] << '\n';
                if (source[cur_pos] - 48 != bit) {
                    // write error
                    errors << "error in source file in words: '" << f.second << "' and '" << s.second << "'\n";
                } else {
                    output << f.first << s.first;
                }
                cur_pos++;
            } 

            // output << res;
        }
    }
    if (ctr == 3) {
        int bit = getCheckBit(f.second, s.second);
        if (source[source.size() - 1] - 48 != bit) {
            // write error
            errors << "error in source file in words: '" << f.second << "' and '" << s.second << "'\n";
            } else {
                output << f.first << s.first;
            }
    } else if (ctr == 2) {
        int bit = getCheckBit(f.second, zeros);
        if (source[source.size() - 1] - 48 != bit) {
            // write error
            errors << "error in source file in word: '" << f.second << "'\n";
        } else {
            output << f.first;
        }
    }
    errors.close();
}