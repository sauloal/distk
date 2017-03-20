#ifndef __H_TOOLS__
#define __H_TOOLS__

#include "defs.hpp"






std::ostream& operator<< (std::ostream& out, const std::vector<string>& v);


#ifdef _DEBUG_
#define _PRINT_LINE_LENGTHS_

//http://stackoverflow.com/questions/10750057/how-to-print-out-the-contents-of-a-vector
template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v);


//template <typename T>
std::ostream& operator<< (std::ostream& out, const std::valarray<char>& v);

std::ostream& operator<< (std::ostream& out, const std::valarray<int>& v);

std::ostream& operator<< (std::ostream& out, const std::valarray<uint>& v);

std::ostream& operator<< (std::ostream& out, const std::valarray<ulong>& v);

std::ostream& operator<< (std::ostream& out, const std::valarray<bool>& v);

template <typename T>
std::vector<T> reversed(std::vector<T> v);
#endif


//https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
bool file_exists (const string& name);

void remove_if_exists( const string& name );

void rename_and_check( const string& src, const string& dst );

//https://stackoverflow.com/questions/32640327/how-to-compute-the-size-of-an-intersection-of-two-stl-sets-in-c
struct Counter
{
    struct value_type { template<typename T> value_type(const T&) { } };
    void   push_back(const value_type&) { ++count; }
    size_t count = 0;
};

template<typename T1, typename T2>
size_t intersection_size(const T1& s1, const T2& s2);



//https://stackoverflow.com/questions/874134/find-if-string-ends-with-another-string-in-c
bool hasEnding (string const &fullString, string const &ending);

#endif //#ifndef __H_KMER_SET_COMPRESSION__ 