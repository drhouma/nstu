#include "random_string.h"

auto random_string(int min_len, int max_len, std::default_random_engine &engine,
                   const std::string &characters) -> std::string {
  if (max_len <= 0) throw std::exception();
  std::string res;
  std::uniform_int_distribution<int> dist(min_len, max_len - 1);
  std::uniform_int_distribution<int> random_char(0, characters.size() - 1);
  int len = dist(engine);
  res.resize(len);
  for (int i = 0; i < len; i++) {
    res[i] = characters[random_char(engine)];
  }
  return res;
}