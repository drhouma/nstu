#include "hamming_algo.h"
#include "cycle_polynom.h"
#include <fstream>

int main() {
    // HammingCoding coder("files/ham_my.txt", 9, 5);
    // coder.ViewAlph();
    // std::fstream in("files/ham_text.txt"), outc("hc"), outd("hd");
    // coder.Coding(in, outc);
    // std::fstream in2("hc_err");
    // coder.Decoding(in2, outd);
    // in.close();
    // // in2.close();
    // outc.close();
    // outd.close();

    CyclePolynom poly("files/polynoms/poly_var8.txt");
    HammingCoding coder("files/hammingFiles/ham_my.txt", 9, 5);
    // coder.ViewMatrices();
    coder.ViewAlph();
    std::cout << coder.hammingDistance() << '\n';
    // 1010110
    // std::fstream file("files/ham_15_7_p8.txt"), output("out");
    // coder.Decoding(file, output);

    // std::cout << poly.GetStringRepresentation() << '\n';
    
}