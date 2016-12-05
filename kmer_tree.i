%module kmer_tree
%include "std_vector.i"
%include <std_string.i>
namespace std {
   //%template(vectors) vector<string>;
   //%template(vectord) vector<double>;
   %template(vectori) vector<long unsigned int>;
};
%{
#include "kmer_tree.hpp"
%}
%include "kmer_tree.hpp"
//int fact(int n);
