#ifndef __H_KMER_GEN__
#define __H_KMER_GEN__

#include <iostream>
#include <algorithm>    // std::reverse
#include <sstream>
#include <iterator>
#include <stdint.h>
#include <math.h>
#include <vector>

using namespace std;

int fact (int n);
void version ();

const char ALPHA[]   = "ACGT";
const int  ALPHA_LEN = 4;

typedef unsigned long ulong;
typedef vector<ulong> vint;
typedef vector<char>  vcha;

class kmer_gen {
private:
    int  kmer_size;
    int  curr;
    bool verbose;
    bool finished;

    vint acs;

    vcha seqs_f;
    vcha seqs_r;

    vint raws_f;
    vint raws_r;

    vint vals_f;
    vint vals_r;

    vint part_f;
    vint part_r;
public:
    kmer_gen(int ks);
    void set_verbosity(bool v);
    long next();
};

#endif //__H_KMER_GEN__
