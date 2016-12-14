%module kmer_set

%include typemaps.i
%include <std_vector.i>
%include <std_set.i>
%include <std_string.i>
%include <stl.i>
#include <sys/types.h>


%template(StringVector) std::vector< std::string >;
%template(ULongSet   )  std::set< unsigned long >;
%template(ULongVector)  std::vector< unsigned long >;
//%template(vectord)      std::vector< double >;

%{
#include "kmer_set.hpp"
%}

%include "kmer_set.hpp"
