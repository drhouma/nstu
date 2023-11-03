#include <iostream>
#include "algorithms.h"
#include <sstream>

int main () {
    std::fstream file("files/probability2.txt"), output("files/text2.txt");
    double prob_l;
    char prev;
    std::string help;
    std::vector<std::string> tokens;
    double sum{0};
    std::vector<std::pair<double, std::string>> probs; 
    while (!file.eof()) {
        tokens.clear();
        std::string tmp;
        std::getline(file, tmp);
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
    for (auto &elem : probs) {
        int count = 1000 * elem.first;
        for (int j = 0; j < count; j++) {
            output << elem.second;
        }
    }
}