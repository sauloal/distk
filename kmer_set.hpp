#ifndef __KMET_SET__
#define __KMET_SET__

#include <vector>
#include <string>
using namespace std;

typedef unsigned long ulong;

int fact (int n);
void version ();

void extract_kmers(std::string infile, int kmer_size);

#endif //__KMET_SET__
