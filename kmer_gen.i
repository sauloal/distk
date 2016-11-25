%module kmer_gen

%include "std_vector.i"

namespace std {
   //%template(vectors) vector<string>;
   //%template(vectord) vector<double>;
   %template(vectori) vector<long unsigned int>;
};

%{
#include "kmer_gen.hpp"
%}

%include "kmer_gen.hpp"

//int fact(int n);
