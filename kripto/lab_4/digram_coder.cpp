#include "digram_coder.h"

auto Coder::ConvertIntToDigram(int number) -> digram {
    int first, second;
    for (int i = 0; i < _N; i++) {
        if (number < (i + 1) * _N ) {
            first = i;
            if (i == 26) first = 30; // нижнее подчеркивание
            second = number - i * _N;
            if (second == 26) second = 30;
            break;
        }
    }
    std::string ret("AA");
    ret[0] = ret[0] +  first;
    ret[1] = ret[1] + second;
    return ret;
}

Coder::Coder(int key) {
    GenerateAlphabet(key);
}

Coder::Coder(std::fstream &keyFile) {
    std::string tmp;
    keyFile >> tmp;
    int key = std::stoi(tmp);
    GenerateAlphabet(key);
}

auto Coder::GenerateAlphabet(int key) -> void {
    srand(key);
    _key = key;
    for (int i = 0; i < _N - 1; i++) {
        char letter = 65 + i;
        _letters[letter] = i;
    }
    _letters['_'] = 26;
    std::fstream file("./codes");
    std::vector<int> vec;
    vec.reserve(_N * _N);
    for (int i = 0; i < _N * _N; i++) {
        int number =  rand() % (_N * _N);
        while (std::find(vec.begin(), vec.end(), number) != vec.end()) {
            number = (number + 1) % (_N * _N);
        }
        vec.push_back(number);
        _alphabet[ConvertIntToDigram(i)] = ConvertIntToDigram(number);
        file << i  << ' ' << number << " " +ConvertIntToDigram(i) <<  " " + ConvertIntToDigram(number)  << '\n';
    }
    file.close();
}


auto Coder::CodeFile(std::fstream &file_in, std::fstream &file_out) -> void {
    std::string source;
    int len = 2;
    file_out << _key << '\n';
    while (!file_in.eof()) {
        std::string output{""};
        std::getline(file_in, source);
        for (int cur_pos{0}; cur_pos < source.length();) {
            auto tmp = source.substr(cur_pos, len);
            if (_alphabet.count(tmp)) {
                file_out << _alphabet[tmp];
                cur_pos += len;
            } else {
                throw std::invalid_argument("cannot cypher with this alphabet");
            }
        }
    }
}


auto Coder::DecodeFile(std::fstream &file_in, std::fstream &file_out) -> void {
    std::string source;
    int len = 2;
    std::string tmp;
    file_in >> tmp;
    int key = std::stoi(tmp);
    GenerateAlphabet(key);
    std::map<code, digram> help;
    for (auto elem : _alphabet) {
        help[elem.second] = elem.first;
    }

    while (!file_in.eof()) {
        std::string output{""};
        std::getline(file_in, source);
        for (int cur_pos{0}; cur_pos < source.length();) {
            auto tmp = source.substr(cur_pos, len);
            if (help.count(tmp)) {
                file_out << help[tmp];
                cur_pos += len;
            } else {
                throw std::invalid_argument("cannot cypher with this alphabet");
            }
        }
    }
}