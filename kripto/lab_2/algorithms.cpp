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
    return coded_alphabet;
}
