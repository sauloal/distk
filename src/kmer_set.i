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
//%template(ULongSet   )  std::set< unsigned long >;

%inline %{
  struct foo {};
  foo bar() { return foo(); }
  std::vector<foo> bar2() { 
    return std::vector<foo>(); 
  } 
%}

%template(strVec  )  std::vector< std::string   >;
%template(ulongVec)  std::vector< unsigned long >;


%{
#include "kmer_set.hpp"
%}

%include "kmer_set.hpp"
