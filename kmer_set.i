%module kmer_set
%include "std_vector.i"
%include <std_string.i>
namespace std {
   //%template(vectors) vector<string>;
   //%template(vectord) vector<double>;
   %template(vectori) vector<long unsigned int>;
};
%{
#include "kmer_set.hpp"
%}
%include "kmer_set.hpp"
//int fact(int n);
