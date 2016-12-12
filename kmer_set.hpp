#ifndef __KMET_SET__
#define __KMET_SET__

#include <vector>
#include <string>
using namespace std;

typedef unsigned long ulong;

int fact (int n);
void version ();

void extract_kmers(const std::string infile, const std::string outfile, const int kmer_size);
void read_kmers(const std::string outfile);

#endif //__KMET_SET__
