#ifndef NSTU_RANDOM_STR
#define NSTU_RANDOM_STR
#include <random>
#include <string>
#include <exception>

auto random_string(int min_len, int max_len, std::default_random_engine &engine, const std::string &characters) -> std::string;
#endif