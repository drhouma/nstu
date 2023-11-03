#include "algorithms.h"



std::string getBinaryDouble(double sigma, int count_symbs_in_res) {
   std::string res = "";
   double help = 0.5;

   for (int i = 1; i < count_symbs_in_res + 1; ++i) {
        if (sigma - help >= 0) {
            res+= '1';
            sigma -= help;
        } else {
            res += '0';
        }
        help = help / 2;
    }
 
   
   return res;
}


int get_number_of_chars(double p) {
    return ceil(-1 * log2(p/2));
}

/// @brief 
/// @param probs<std::pair<double, std::string>> double - вероятность, std::String - символ алфавита
/// @return 
std::map<std::string, code_string> gilbert_alg(std::vector<std::pair<double, std::string>> probs) {
    std::map<std::string, code_string> res;
    double sum{0};

    // для 0 элемента
    std::string help = getBinaryDouble(probs[0].first / 2, get_number_of_chars(probs[0].first));
    res.insert(std::make_pair(probs[0].second, help));

    for (int i = 1; i < probs.size(); i++) {
        double q = probs[i - 1].first + sum;
        sum += probs[i-1].first;
        help = getBinaryDouble(q + probs[i].first / 2, get_number_of_chars(probs[i].first)); // sigma to string
        res.insert(std::make_pair(probs[i].second, help));
    }
    return res;
}


void decypher(std::fstream &input, std::fstream &output, std::map<std::string, code_string> alph) {
    // сортирую данные в лексикографическом порядке для более удобной обработки
    // (сортировка по 1 аргументу мапа)
 
    std::string source, res;
    while (!input.eof()) {
        int len = 0, cur_pos = 0;
        std::getline(input, source);
        while( cur_pos < source.size() ) {
            res.clear();
            bool end = false;
            for (auto it = alph.begin(); !end &&  it != alph.end(); ++it) {
                len = it->second.size();
                if (!source.compare(cur_pos, len, it->second) ){
                    end = true;
                    res += it->first;
                }
            }
            if (end == false) {
                throw std::invalid_argument("can not decode text with given alphabet");
            }

            output << res;
            cur_pos += len;
        }
    }
}

std::map<std::string, code_string> get_coded_alphabet(std::fstream &prob, double& redundancy, double& mid_len) {
    // first is letter, second is code
    std::map<std::string, code_string> coded_alphabet; 

    std::vector<std::pair<double, std::string>> probs;

 
    double prob_l;
    char prev;
    std::string help;
    std::vector<std::string> tokens;
    double sum{0}; 
    while (!prob.eof()) {
        tokens.clear();
        std::string tmp;
        std::getline(prob, tmp);
        // проверка на пустые строки в файле
        if (tmp != "") {
            std::stringstream buf(tmp);
            while (getline(buf, help, ' ')) {
                tokens.push_back(help);
            }
            if (prob_l < 0 || prob_l > 1) {
                throw std::invalid_argument("incorrect probability: " + std::to_string(prob_l) + '\n');
            }
            prob_l = std::stod(tokens[1]);
            sum += prob_l;

            probs.emplace_back(std::make_pair(prob_l,tokens[0]));
        }

    }
    if (abs(sum - 1) > 0.0000001) {
        throw std::invalid_argument("sum of the probabilities != 1: " + std::to_string(sum) + '\n');
    }

    prob.close();
    coded_alphabet = gilbert_alg(probs);
    mid_len = 0;
    for (auto elem : probs) {
        mid_len += elem.first * coded_alphabet[elem.second].length();
    }
    redundancy = eval_redundancy(probs, mid_len);
    return coded_alphabet;
}

void cypher_file(std::fstream &file_in, std::fstream &file_out, const std::map<std::string, code_string>& coded_alphabet) {
    std::string tmp;
    std::set<int> help;
    for (auto &elem : coded_alphabet) {
        help.emplace(elem.first.length());
    }
    
    while (!file_in.eof()) {
        std::string output{""};
        std::getline(file_in, tmp);
        for (int cur_pos{0}; cur_pos < tmp.length();) {
            bool end = false;
            for (auto it = help.begin(); !end && it != help.end(); ++it) {
                for (auto &elem : coded_alphabet) {
                    if (!end && elem.first.length() == *it && !tmp.compare(cur_pos, *it, elem.first)) {
                        end = true;
                        cur_pos += *it;
                        file_out << elem.second;
                    }
                }
            }  
            if (!end) throw std::invalid_argument("cannot cypher with this alphabet");
        }
    }
    
}
// подсчет избыточности
double eval_redundancy(const std::vector<std::pair<double, std::string>>& probs, double mid_len) {
    double H{};
    // подсчет энтропии H
    for (auto &elem : probs) {
        H -= elem.first * log2(elem.first);

    }
    return mid_len - H;
}

//
bool check_kraft(std::map<std::string, code_string> &M) {
    double sum{0};
    for (auto &elem1 : M) {
        for (auto &elem2 : M) {
            if (elem1.second != elem2.second && elem1.second.length() < elem2.second.length()) {
                if (!elem2.second.compare(0, elem1.second.length() ,elem1.second)) {
                    return false;
                }
            }
        }
        double r{1};
        for (int i = 0; i < elem1.second.length(); i++) {
            r = r / 2;
        }
        // r = pow(2, -1 * elem1.second.length()); не работает
        sum += r;
    }
    if (sum > 1) return false;
    return true;
}