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
    int dictF[256];

    for ( int i = 0; i < 256; i++ ) {
        dictF[i] = 127;
    }

    dictF['a'] = 0;
    dictF['A'] = 0;
    dictF['c'] = 1;
    dictF['C'] = 1;
    dictF['g'] = 2;
    dictF['G'] = 2;
    dictF['t'] = 3;
    dictF['T'] = 3;

    std::ifstream infhd(infile);
    std::valarray<char> kmer;
    min_set<ulong>  q;

    ulong pows[32] = {};

    for ( int pos = 0; pos < kmer_size; pos++ ) {
        ulong ind = (kmer_size-pos-1);
        pows[pos] = std::pow(4, ind);
    }


    if(infhd.is_open()) {
        std::string line;
        //std::valarray<const char *> l;
        while (getline(infhd,line)) {

#ifdef _DEBUG_
            std::cout << "Line: " << line << endl;
#endif

            if ( line.length() >= kmer_size ) {
                ulong      ll    = line.length();

                charValArr charF = charValArr(line.c_str(), ll);
                oIntValArr intsF = oIntValArr(              ll);
                intValArr  valsF = intValArr(               ll);

                char c;
                int  vF;
                for (ulong i = 0; i < ll; i++) {
                    c        = charF[i];
                    vF       = dictF[c];
                    intsF[i] = vF;

#ifdef _DEBUG_
                    std::cout << "i " << i << " c " << c << " vF " << vF << "(" << vF << ")" << std::endl;
#endif

                    ulong js;
                    ulong je;
                    if ( vF == 127 ) {
#ifdef _DEBUG_
                        std::cout << "BAD" << std::endl;
#endif
                        js = i - kmer_size + 1;
                        je = i             + 1;

                        if ( js < 0  ) { js =  0; }
                        if ( je > ll ) { js = ll; }
#ifdef _DEBUG_
                        std::cout << "js " << js << " je " << je << std::endl;
#endif

                        for ( ulong j = js; j < je; j++ ) {
                            valsF[j] = 1;
#ifdef _DEBUG_
                            std::cout << "js " << js << " je " << je << " j " << j << valsF << std::endl;
#endif
                        }
                    }
                }

/*
#ifdef _DEBUG_
                std::cout << " SEQ   : " << charF << endl;
                std::cout << " INTS  : " << intsF << endl;
                std::cout << " VALIDS: " << valsF << endl;
#endif
*/

                ulong resF = 0;
                ulong resR = 0;
                ulong resM = 0;

                ulong kcF  = 0;
                ulong pvF  = 0;
                ulong cvF  = 0;

                ulong kcR  = 0;
                ulong pvR  = 0;
                ulong cvR  = 0;

                for ( ulong i = 0; i < (line.length() - kmer_size + 1); i++ ) {
                    std::slice sl    = std::slice(i, kmer_size, 1);
                    charValArr kmerF = charF[ sl ];
                    oIntValArr kvalF = intsF[ sl ];
                    bool       valF  = valsF[ i  ];

                    if ( valF == 0 ) {
#ifdef _DEBUG_
                        std::cout << " I   : " << i;
                        std::cout << " KMER: " << kmerF;
                        std::cout << " VALS: " << kvalF;
                        std::cout << "\n";
#endif

                        /*
                        //auto res = kval.apply( KmerSum(kval) );
                        KmerSum s   = std::for_each(std::begin(kval), std::end(kval), KmerSum(kmer_size));
                        auto    res = s.sum;
                        //auto res = KmerSummer(kval);
                        */

                        resF = 0;
                        resR = 0;
                        resM = 0;

                        kcF  = 0;
                        pvF  = 0;
                        cvF  = 0;

                        kcR  = 0;
                        pvR  = 0;
                        cvR  = 0;

                        for ( unsigned int pos = 0; pos < kmer_size; pos++ ) {
                            kcF   = kvalF[             pos     ];
                            kcR   = 3 - kcF;
                            pvF   = pows[              pos     ];
                            pvR   = pows[  kmer_size - pos - 1 ];

#ifdef _DEBUG_
                            std::cout << "POS : "    << (pos+1)
                                      << " SUM BF: " << resF << " SUM BR: " << resR
                                      << " KCF: "    << kcF  << " KCR: "    << kcR
                                      << " PVF: "    << pvF  << " PVR: "    << pvR;
#endif
                            cvF   = kcF * pvF;
                            cvR   = kcR * pvR;

                            resF += cvF;
                            resR += cvR;

#ifdef _DEBUG_
                            std::cout << " VALF: "   << cvF  << " VALR: "   << cvR
                                      << " SUM AF: " << resF << " SUM AR: " << resR << endl;
#endif
                        }

                        resM = resF <= resR ? resF : resR;

                        q.insert(resM);

#ifdef _DEBUG_
                        std::cout << "RESF: " << resF  << " RESR: " << resR << " RESM: " << resM << "\n" << endl;
#endif
                    }
                }
            }
        }

        std::cout << "TOTAL: " << q.size() << endl;
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
