#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>


typedef std::string digram;
typedef std::string code;

class Coder {
    // key is code, value is letter 
    std::map<digram, code> _alphabet;
    std::map<char, int> _letters;
    int _N = 27;
    int _key;

    public:

    Coder() = delete;
    Coder(int key);
    Coder(std::fstream& keyFile);

    void GenerateAlphabet(int key);
    auto CodeFile(std::fstream &file_in, std::fstream &file_out) -> void;
    auto DecodeFile(std::fstream &file_in, std::fstream &file_out) -> void;



    private:
    digram ConvertIntToDigram(int);
    
};