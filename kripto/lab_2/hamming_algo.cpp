#include "hamming_algo.h"

void setErrorsTable(std::map<int, int> &table) {
    table.insert(std::make_pair(5, 1));
    table.insert(std::make_pair(11, 2));
    table.insert(std::make_pair(12, 3));
    table.insert(std::make_pair(6, 4));
    table.insert(std::make_pair(3, 5));
    table.insert(std::make_pair(8, 6));
    table.insert(std::make_pair(4, 7));
    table.insert(std::make_pair(2, 8));
    table.insert(std::make_pair(1, 9));
}


std::string integerToBinaryStr(int num, int size) {
    std::string res;
    for (int i = size - 1; i >= 0; i--) {
        if (num >= pow(2, i)) {
            res += '1';
            num -= pow(2, i);
        } else {
            res += '0';
        }
    }
    return res;
}


void HammingCoding::EvalCheckMatrix() {
    Matrix tmp(_k, _n -_k);
    for (int i = 0; i < tmp.row(); i++) {
        for (int j = 0; j < tmp.col(); j++) {
            tmp[i][j] = _generative[i][j + _k];
        }
    }
    tmp = tmp.transpose();
    Matrix ID(_n - _k, _n - _k);
    ID.SetIdentityMatrix();
    _H = tmp.Concatenation(ID);
    _Checking = Matrix(_H).transpose();
    setErrorsTable(errors_table);
}

void HammingCoding::GenerateAlhpabet() {
    for (int i = 0; i < pow(2, _generative.row()); i++) {
        std::string binaryNum = integerToBinaryStr(i, _generative.row());
        _alph[binaryNum] = GenerateCode(binaryNum); 
    }
}

std::string HammingCoding::GenerateCode(const std::string& number) {
    Matrix tmp(1, _generative.row());
    std::string res;
    for (int i = 0; i < tmp.col(); i++) {
        tmp[0][i] = number[i] - 48;
    }

    auto res_m = tmp * _generative;

    for (int i = 0; i < res_m.col(); i++) {
        res += static_cast<int>(res_m[0][i]) % 2 + 48;
    }
    return res;
}


HammingCoding& HammingCoding::operator =(const  HammingCoding& other) {
    _generative = other._generative;
    _n = other._n;
    _k = other._k;
    _H = other._H;
    _alph = other._alph;
    return *this;
}

HammingCoding::HammingCoding(Matrix &P, int n, int k) :_n(n), _k(k) {
    _generative = P;
    GenerateAlhpabet();
    EvalCheckMatrix();
}

HammingCoding::HammingCoding(const std::string& fileWithMatrix, int n, int k) :_n(n), _k(k) {
    std::fstream in(fileWithMatrix);
    int rows, cols;
    in >> rows;
    in >> cols;
    _generative = Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            in >> _generative[i][j];
        }
    }
    GenerateAlhpabet();
    EvalCheckMatrix();
}

void HammingCoding::ViewAlph() {
    for (auto &elem : _alph) {
        std::cout << elem.first << " -> " << elem.second << '\n';
    }
}
HammingCoding::HammingCoding(CyclePolynom &poly, int n, int k) : _n(n), _k(k) {
    // _generative = Matrix(k, n);
    Matrix tmp(k, n - k);
    for (int i = 0; i < tmp.row(); i++) {
        CyclePolynom help(n - 1 - i);
        auto powers = (help / poly).GetPowers();
        powers.reserve(n - k);
        for (int j = 0; j < n - k; j++) {
            tmp[i][j] = powers[n - k - j - 1] ? 1 : 0;
        }
    }
    _generative = Matrix(k, k);
    _generative = _generative.SetIdentityMatrix().Concatenation(tmp);
    GenerateAlhpabet();
    EvalCheckMatrix();
}


void HammingCoding::Coding(std::fstream &file_in, std::fstream &file_out) {
    std::string source;
    int len = _generative.row(); 
    while (!file_in.eof()) {
        std::string output{""};
        std::getline(file_in, source);
        for (int cur_pos{0}; cur_pos < source.length();) {
            auto tmp = source.substr(cur_pos, len);
            if (_alph.count(tmp)) {
                file_out << _alph[tmp];
                cur_pos += len;
            } else {
                throw std::invalid_argument("cannot cypher with this alphabet");
            }
        }
    }
}

void HammingCoding::Decoding(std::fstream &file_in, std::fstream &file_out) {
    std::string source;
    std::experimental::filesystem::resize_file("files/errors/hamming_errors.txt", 0);
    std::fstream errors("files/errors/hamming_errors.txt");
    int len = _generative.col();
    std::map<code_str, std::string> help;
    for (auto &elem : _alph) {
        help[elem.second] = elem.first;
    }

    while (!file_in.eof()) {
        std::string output{""};
        std::getline(file_in, source);
        for (int cur_pos{0}; cur_pos < source.length();) {
            auto str = source.substr(cur_pos, len);
            // std::cout << str  << " " << cur_pos << '\n';
            if (help.count(str) == 0) {
                Matrix tmp(1, _generative.col());
                for (int i = 0; i < tmp.col(); i++) {
                    tmp[0][i] = str[i] - 48;
                }
                auto S = tmp * _Checking;
                // _Checking.show();
                S.show();
                int degenerate_bit_index{0};
                for (int i = 0; i < S.col(); i++) {
                    int bit = static_cast<int>(S[0][i]) % 2;
                    degenerate_bit_index += pow(2, S.col() - 1 - i) * bit;
                }
                errors << "найдена ошибка в позиции " << cur_pos + errors_table[degenerate_bit_index] << ", исправлена: " << str;
                if (degenerate_bit_index > 0) {
                    str[errors_table[degenerate_bit_index] - 1] = str[errors_table[degenerate_bit_index] - 1] == '1' ? '0' : '1'; 
                }
                errors << " -> "<< str << '\n';

            }
            file_out << help[str];
            cur_pos+=len;
        }
    }
    errors.close();
}


void HammingCoding::ViewMatrices() {
    std::cout << "generative matrix:\n";
    _generative.show();
    std::cout << "Check matrix:\n";
    _H.show();
    _Checking.show();
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

int HammingCoding::hammingDistance() {
    int sum{0};
    for (auto &elem1 : _alph) {
        for (auto &elem2 : _alph) {
            if (elem1.second != elem2.second) {
                auto temp = hammingDistanceStr(elem1.second, elem2.second);
                if (LesserDistance > temp) {
                    LesserDistance = temp;
                }
            }
        }
    }
    return LesserDistance;
}

bool HammingBorder(int n, int k, int q) {
    int sum{0};
    for (int i = 0; i <= q; i++) {
        sum += numberOfCombinations(n, i);
    }
    return n - k >= log2(sum);
}

bool PlotkinBorder(int n, int k, int d) {
    return d <= n * (pow(2, k - 1) / (pow(2, k) - 1));
}

bool VarshamovGilbertBorder(int n, int k, int d) {
    int sum{0};
    for (int i = 0; i <= d - 2; i++) {
        sum += numberOfCombinations(n - 1, i);
    }
    return pow(2, n - k) > sum;
}