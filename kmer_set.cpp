#include "kmer_set.hpp"

#include <iostream>

#ifndef _PRINT_PROGRESS_EVERY_
#define _PRINT_PROGRESS_EVERY_ 5000000
#endif

int fact (int n) {
    if (n < 0){
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    else {
        return n * fact(n-1);
    }
}


//http://stackoverflow.com/questions/1204202/is-it-possible-to-print-a-preprocessor-variable-in-c
#define STRING2(x) #x
#define STRING(x) STRING2(x)
void version () {
   std::cout   << "kmer_gen version: " << STRING(__KMER_GEN_VERSION__) << "\n"
               << "build date      : " << STRING(__DATE__            ) << std::endl;
}


//http://www.linuxquestions.org/questions/programming-9/mmap-tutorial-c-c-511265/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include <valarray>     // std::valarray, std::slice

#include <fstream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <math.h>       /* pow */
#include <functional>
#include <set>

//http://stackoverflow.com/questions/10750057/how-to-print-out-the-contents-of-a-vector
template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}


//template <typename T>
std::ostream& operator<< (std::ostream& out, const std::valarray<char>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    std::copy (std::begin(v), std::end(v), std::ostream_iterator<char>(out, ", "));
    out << "\b\b]";
  }
  return out;
}
std::ostream& operator<< (std::ostream& out, const std::valarray<int>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    std::copy (std::begin(v), std::end(v), std::ostream_iterator<int>(out, ", "));
    out << "\b\b]";
  }
  return out;
}
std::ostream& operator<< (std::ostream& out, const std::valarray<uint>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    std::copy (std::begin(v), std::end(v), std::ostream_iterator<uint>(out, ", "));
    out << "\b\b]";
  }
  return out;
}
std::ostream& operator<< (std::ostream& out, const std::valarray<ulong>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    std::copy (std::begin(v), std::end(v), std::ostream_iterator<ulong>(out, ", "));
    out << "\b\b]";
  }
  return out;
}
template <typename T>
std::vector<T> reversed(std::vector<T> v) {
    std::vector<T> w(v.begin(), v.end());
    std::reverse(w.begin(),w.end());
    return w;
}




typedef std::valarray<char>  charValArr;
typedef std::valarray<ulong> oIntValArr;
typedef std::valarray<int>   intValArr;
//http://en.cppreference.com/w/cpp/numeric/valarray/apply
//http://en.cppreference.com/w/cpp/algorithm/for_each

struct KmerSum
{
    int   len;
    ulong sum;
    ulong pos;
    KmerSum(const int l): len(l), sum(0), pos(0) {}
    void operator()(const int n) {
        pos       += 1;
        //std::cout << "\nPOS: " << pos << " N: " << n << " SUM B: " << sum;
        ulong pv   = std::pow( 4, (len-pos));
        ulong val  = pv * n;
        sum       += val;
        //std::cout << " PV: " << pv << " VAL: " << val << " SUM A: " << sum << endl;
    }
};



/*
ulong KmerSummer(oIntValArr &kval) {
    return 0;
}
*/

//http://www.cplusplus.com/reference/valarray/slice/
#include <cstddef>      // std::size_t
#include <valarray>     // std::valarray, std::slice

template<class T> using max_set  = std::set<T, std::greater<T> >;
template<class T> using min_set  = std::set<T, std::less<T> >;

void extract_kmers(const std::string infile, int kmer_size) {
    char dict[256];

    for ( int i = 0; i < 256; i++ ) {
        dict[i] = 127;
    }

    dict['a'] = 0;
    dict['A'] = 0;
    dict['c'] = 1;
    dict['C'] = 1;
    dict['g'] = 2;
    dict['G'] = 2;
    dict['t'] = 3;
    dict['T'] = 3;

    std::ifstream infhd(infile);
    std::valarray<char> kmer;
    min_set<ulong>  q;

    if(infhd.is_open()) {
        std::string line;
        //std::valarray<const char *> l;
        while (getline(infhd,line)) {
#ifdef _DEBUG_
            std::cout << "Line: " << line << endl;
#endif
            if ( line.length() >= kmer_size ) {
                charValArr lc     = charValArr(line.c_str(), line.length());
                oIntValArr vals   = oIntValArr(              line.length());
                intValArr  valids = intValArr(               line.length());
                ulong ll = line.length();

                for (ulong i = 0; i < ll; i++) {
                    const char n = lc[i];
                    char  v      = dict[n];
                    vals[i]      = v;

#ifdef _DEBUG_
                    std::cout << "i " << i << " n " << n << " v " << v << "(" << ((int)v) << ")" << std::endl;
#endif

                    if (((int)v) == 127) {
#ifdef _DEBUG_
                        std::cout << "BAD" << std::endl;
#endif
                        long js = (long)i - kmer_size + 1;
                        long je = (long)i + 1;

                        if ( js < 0  ) { js =  0; }
                        if ( je > ll ) { js = ll; }
#ifdef _DEBUG_
                        std::cout << "js " << js << " je " << je << std::endl;
#endif

                        for ( long j = js; j < je; j++ ) {
                            valids[j] = 1;
#ifdef _DEBUG_
                            std::cout << "js " << js << " je " << je << " j " << j << valids << std::endl;
#endif
                        }
                    }
                }

#ifdef _DEBUG_
                std::cout << " SEQ   : " << lc     << endl;
                std::cout << " VALS  : " << vals   << endl;
                std::cout << " VALIDS: " << valids << endl;
#endif

                for (ulong i = 0; i < (line.length() - kmer_size - 1); i++) {
                    charValArr kmer = lc[     std::slice(i, kmer_size, 1) ];
                    oIntValArr kval = vals[   std::slice(i, kmer_size, 1) ];
                    bool       val  = valids[ i                           ];

                    if ( val == 0 ) {
#ifdef _DEBUG_
                        std::cout << " I   : " << i;
                        std::cout << " KMER: " << kmer;
                        std::cout << " VALS: " << kval;
#endif

                        //auto res = kval.apply( KmerSum(kval) );
                        KmerSum s   = std::for_each(std::begin(kval), std::end(kval), KmerSum(kmer_size));
                        auto    res = s.sum;
                        //auto res = KmerSummer(kval);
                        q.insert(res);

#ifdef _DEBUG_
                        std::cout << "RES : " << res << endl;
#endif
                    }
                }
            }
        }

        for (std::set<ulong>::iterator it=q.begin(); it!=q.end(); ++it) {
//#ifdef _DEBUG_
            std::cout << ' ' << *it;
            std::cout << '\n';
//#endif
        }
    } else {
        perror("Error reading file");
    }
}
