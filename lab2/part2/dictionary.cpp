#include "dictionary.h"
#include <iostream>

Dictionary::Dictionary(int hashFunc) : m_hash_func(hashFunc) {
    if (m_hash_func < 1 || m_hash_func > 3) {
        m_hash_func = 1;
        // send error message
    }
}

Dictionary::~Dictionary() {
}

auto Dictionary::init() -> void {
   
}

auto Dictionary::set(const std::string &key, const std::string &val) -> void {
    int index = this->hash(key);
    m_table[index].emplace_back(key, val);
}

auto Dictionary::get(const std::string &key) -> IsInserted {
    int index = this->hash(key);
    IsInserted res;
    res.res = false;
    for (auto iter = m_table[index].begin(); iter != m_table[index].end(); ++iter) {
        if (key == (*iter).first) {
            res.value = (*iter).second;
            res.res = true;
            break;
        }
    }
    return res;
}


auto Dictionary::hash(const std::string &str) -> int {
    if (m_hash_func == 1) {
        return hash_1(str);
    } else if (m_hash_func == 2) {
        return hash_2(str);
    } else if (m_hash_func == 3) {
        return hash_3(str);
    }
}

auto Dictionary::hash_1(const std::string &str) -> int {
    int sum{0}; 
    for (auto symb : str) {
        sum += abs(symb);
    }
    return sum % m_max_size;
}

auto Dictionary::hash_2(const std::string &str) -> int {
    int sum{0}; 
    for (int i = 0; i < str.size();i++) {
        sum += pow(str[i], i);
    }
    return sum % m_max_size;
}

auto Dictionary::hash_3(const std::string &str) -> int {
    int sum{0}; 
    for (int i = 0; i < str.size();i++) {
        sum += pow(str[i], i);
    }
    return sum % m_max_size;
}