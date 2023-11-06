    #pragma once
    #include "matrix/matrix_oop.h"
    #include "cycle_polynom.h"
    #include <fstream>
    #include <set>
    #include <string>
    #include <cmath>
    #include <map>
    #include <experimental/filesystem>
    typedef std::string code_str;

    void noNoiseCypher(std::fstream &file_in, std::fstream &file_out, const std::map<std::string, code_str>& coded_alphabet);

    void checkErrorsDecypher(std::fstream &input, std::fstream &output, std::map<std::string, code_str> alph);


    class HammingCoding {
        private:
        Matrix _generative;
        Matrix _H;
        Matrix _Checking;
        std::map<std::string, code_str> _alph;
        std::map<int, int> errors_table;

        int _n{-1}, _k{-1};
        private:
        void EvalCheckMatrix();

        public:
        HammingCoding() {};
        HammingCoding(Matrix& P, int n, int k);
        HammingCoding(const std::string& fileWithMatrix, int n, int k);
        HammingCoding(CyclePolynom &poly, int n, int k);


        HammingCoding& operator =(const  HammingCoding& other);

        std::string GenerateCode(const std::string& number);
        void GenerateAlhpabet();
        void ViewAlph();
        void Coding(std::fstream &file_in, std::fstream &file_out);
        void Decoding(std::fstream &file_in, std::fstream &file_out);
        void ViewMatrices();
        void ViewMetrics();
        int hammingDistance();
        int LesserDistance{1000000};
    };