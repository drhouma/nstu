#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "digram_coder.h"



int main () {
    auto gtime = time(NULL);
    srand(gtime);
    int key = 123;
    Coder coder(5552);
    std::fstream in("files/sequence"),out_c("files/output_coding"), out_d("files/output_decoding"); 
    coder.CodeFile(in, out_c);
    // coder.DecodeFile(out_c, out_d);
}