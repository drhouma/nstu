#include "cycle_polynom.h"
#include <iostream>
CyclePolynom::CyclePolynom(std::string filename) {
    std::fstream in(filename);
    int power;
    if (!in.is_open()) throw std::invalid_argument("Bad file (Cycle polynom)");
    while (!in.eof()) {
        in >> power;
        _powers.push_back(power == 1 ? true : false);
        rang++;
    }
    // rang--;
    in.close();
}
CyclePolynom::CyclePolynom(const CyclePolynom& other) {
    _powers = other._powers;
    rang = other.rang;
}
CyclePolynom::CyclePolynom() {

}
CyclePolynom::CyclePolynom(const std::initializer_list<int>& l) {
    for (auto elem : l) {
        _powers.push_back(elem == 1);
        rang++;
    }

}
CyclePolynom::CyclePolynom(const int power) {
    // _powers.reserve(power + 1);
    for (int i = 0; i < power; i++) {
        _powers.push_back(false);
    }
    _powers.push_back(true);
    rang = power + 1;
}

CyclePolynom CyclePolynom::operator *(const int power) {
    CyclePolynom res;
    res.rang = power + rang;
    res._powers.reserve(res.rang);
    for (int i = 0; i < power; i++) {
        res._powers[i] = false;
    }
    for (int i = 0; i < rang; i++) {
        res._powers[i + power] = _powers[i];
    }

    return res;
}


CyclePolynom CyclePolynom::operator+(const CyclePolynom &other) {
    CyclePolynom res(other.rang > rang ? other : *this);
    int lesserRang = other.rang < rang ? other.rang : rang;
    for (int i = 0; i < lesserRang + 1; i++) {
        res._powers[i] = this->_powers[i] xor other._powers[i];
    }
    int updateRang{0};
    for (int i = 0; i < res.rang; i++) {
        if (res._powers[i]) updateRang = i + 1;
    }
    res.rang = updateRang;
    return res;
}

CyclePolynom& CyclePolynom::operator=(const CyclePolynom& other) {
    rang = other.rang;
    _powers = other._powers;
    return *this;
}

CyclePolynom CyclePolynom::operator / (const CyclePolynom &other) {
    CyclePolynom tmp(*this);
    CyclePolynom tmpo(other);
    while (tmp.rang >= other.rang) {

        int diff = tmp.rang - other.rang;
        CyclePolynom tmp2(tmpo * diff);
        tmp = tmp + tmp2;

    }
    return tmp;
}

std::string CyclePolynom::GetStringRepresentation() {
    std::string res("");
    bool need_plus = false;
    if (rang != 0 && _powers[0]) {
        res += "1";
        need_plus = true;
    } else if (rang == 0) {
        res += '0';
    }
    for (int i = 1; i < rang; i++) {
        if (_powers[i]) {
            if (need_plus) res += " + ";
            res += "x^" + std::to_string(i); 
            need_plus = true;
        }
    }
    return res;
}