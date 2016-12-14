%module kmer_set

%include typemaps.i
%include <std_vector.i>
%include <std_set.i>
%include <std_string.i>
%include <stl.i>
#include <sys/types.h>

//%{
//#   define SWIG_PYTHON_EXTRA_NATIVE_CONTAINERS 
//%}

//%template(vectord)      std::vector< double >;
%template(StringVector) std::vector< std::string  >;
%template(ULongVector)  std::vector< unsigned long >;
//%template(ULongSet   )  std::set< unsigned long >;

%{
#include "kmer_set.hpp"
%}

%include "kmer_set.hpp"
