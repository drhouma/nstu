#include "dictionary.h"
#include <iostream>

Dictionary::Dictionary(HashFunc index) : m_hash_func(index) {
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
    if (m_hash_func == HashFunc::hash1) {
        return hash_1(str);
    } else if (m_hash_func == HashFunc::hash2) {
        return hash_2(str);
    } else if (m_hash_func == HashFunc::shift) {
        return hash_3(str);
    }
    return HashFunc::hash1;
}

auto Dictionary::hash_1(const std::string &str) -> int {
    int hash = 7; 
    int alpha = 5;
    for (int i = 0; i < str.size(); i++) {
        hash = (hash << alpha) - hash + str[i];  // hash * 31 + str[i]
    }
    return hash % m_max_size;
}

auto Dictionary::hash_2(const std::string &str) -> int {
    int hash{3}; 
    int alpha = 121,beta = 155;
    for (int i = 0; i < str.size();i++) {
        hash = (hash << 2) + str[i] * beta + 117;
    }
    return hash % m_max_size;
}

auto Dictionary::hash_3(const std::string &str) -> int {
    int hash{0}; 
    for (int i = 0; i < str.size();i++) {
        hash += str[i] << i;
    }
    return hash % m_max_size;
}

auto Dictionary::CountTotalPercussion() -> int {
    int sum{0};
    for (int i = 0; i < m_max_size; i++) {
        if (m_table[i].size() > 10) {sum += m_table[i].size() - 1;
        }
    }
    return sum;
} 

auto Dictionary::SetHash(HashFunc func) -> void {
    m_hash_func = func;
}