#ifndef NSTU_LAB2_DICTIONARY
#define NSTU_LAB2_DICTIONARY
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <cmath>

using std::string;

struct IsInserted {
    bool res;
    std::string value;
};

enum HashFunc {
    hash1 = 1,
    hash2 = 2,
    shift = 3
};


const size_t SIZE = 3e+5;

class Dictionary {
  public:
    Dictionary(HashFunc index);
    Dictionary() = delete;
    ~Dictionary();

  public:
    auto set(const string &key, const string &value) -> void;
    auto get(const string &key)                      -> IsInserted;
    auto CountTotalPercussion()                      -> int;
    auto SetHash(HashFunc)                           -> void;

  private:
    auto init() -> void;
    auto hash_1(const string &str) -> int;
    auto hash_2(const string &str) -> int;
    auto hash_3(const string &str) -> int;
    auto hash(const string &str)   -> int;


  private:
    size_t m_max_size{SIZE};
    std::list<std::pair<std::string, std::string>> m_table[SIZE];
    int m_hash_func{1};
    int *m_hash(const std::string &str);

};
#endif
