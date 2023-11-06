#pragma once

#include <vector>
#include <fstream>
#include <initializer_list>

class CyclePolynom {
    private:
    std::vector<bool> _powers;
    int rang{0};

    public:

    public:
    CyclePolynom();
    CyclePolynom(std::string filename);
    CyclePolynom(const CyclePolynom &other);
    CyclePolynom(const std::initializer_list<int>&);
    CyclePolynom(const int power);
    CyclePolynom operator / (const CyclePolynom &other);
    CyclePolynom operator + (const CyclePolynom &other);
    CyclePolynom operator *(const int power);
    CyclePolynom& operator=(const CyclePolynom& other);
    std::string GetStringRepresentation();

    int GetRank() {return rang - 1;};
    std::vector<bool> GetPowers() {return _powers;};
};