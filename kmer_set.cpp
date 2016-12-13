#include "kmer_set.hpp"

//http://www.linuxquestions.org/questions/programming-9/mmap-tutorial-c-c-511265/
#include <iostream>
#include <fstream>
#include <iterator>


//#include <numeric>
//#include <sstream>
//#include <unistd.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <vector>
//#include <functional>
//#include <math.h>       /* pow */
//#include <cstddef>      // std::size_t

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
   std::cout   << "version      : " << STRING(__PROG_VERSION__) << "\n"
               << "build date   : " << STRING(__COMPILE_DATE__) << std::endl;
#ifdef _DEBUG_
    std::cout   << "COMPILE FLAG: _DEBUG_" << std::endl;
#endif
#ifdef _PRINT_LINE_LENGTHS_
    std::cout   << "COMPILE FLAG: _PRINT_LINE_LENGTHS_" << std::endl;
#endif
#ifdef _USE_SLICE_
    std::cout   << "COMPILE FLAG: _USE_SLICE_" << std::endl;
/*
 *7 7           2m52.768s
 *7 7 use slice 4m32.193s
*/
#endif
}



#ifdef _DEBUG_
#define _PRINT_LINE_LENGTHS_

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
std::ostream& operator<< (std::ostream& out, const std::valarray<bool>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    //std::copy (std::begin(v), std::end(v), std::ostream_iterator<bool>(out, ", "));
    for (auto it=std::begin(v); it!=std::end(v); ++it) {
        out << (( it == std::begin(v) )? "" : ", ") << *it;
    }
    out << "]";
  }
  return out;
}
template <typename T>
std::vector<T> reversed(std::vector<T> v) {
    std::vector<T> w(v.begin(), v.end());
    std::reverse(w.begin(),w.end());
    return w;
}
#endif






extract_kmers::extract_kmers(const int ks): kmer_size(ks), lineNum(0), ll(0), resF(0), resR(0), resM(0), kcF(0), pvF(0), cvF(0), kcR(0), pvR(0), cvR(0) {
    std::cout << " KMER SIZE: " << kmer_size << std::endl;

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

    for ( int pos = 0; pos < kmer_size; pos++ ) {
        ulong ind = (kmer_size-pos-1);
        pows[pos] = std::pow(4, ind);
    }

#ifndef _USE_SLICE_
    kchaF.resize(kmer_size);
    kintF.resize(kmer_size);
#endif
}


extract_kmers::~extract_kmers(){
#ifndef _USE_SLICE_
        kchaF.resize(0);
        kintF.resize(0);
#endif
        charF.resize(0);
        intsF.resize(0);
        valsF.resize(0);

        q.clear();
}

ulong extract_kmers::get_total() {
    return q.size();
}

void extract_kmers::print_all() {
    for (std::set<ulong>::iterator it=q.begin(); it!=q.end(); ++it) {
        std::cout << ' ' << *it;
        std::cout << '\n';
    }
}

void extract_kmers::read_file(  const std::string &infile  ) {
    std::ifstream infhd(infile);

    if(infhd.is_open()) {
        std::string line;
        //std::valarray<const char *> l;

        while (getline(infhd,line)) {
            parse_line(line);
        }//while (getline(infhd,line)) {

        std::cout << "TOTAL: " <<  get_total() << std::endl;
    
#ifdef _DEBUG_
        print_all();
#endif

        infhd.close();
    
    } else {//if(infhd.is_open()) {
        perror("Error reading file");
    }
}

void extract_kmers::parse_line( const std::string &line    ) {
#ifdef _DEBUG_
    if ( line.length() <= 100 ) {
        std::cout << "Line: " << line << std::endl;
    }
#endif

#ifdef _USE_SLICE_
    std::slice sl;
#endif
    //charValArr kchaF(kmer_size);
    //uIntValArr kintF(kmer_size);

    if ( line.length() >= kmer_size ) {
        lineNum          += 1;
        ll                = line.length();
        
#ifdef _PRINT_LINE_LENGTHS_
        std::cout << " Line :: Length: " << ll << " Num: " << lineNum;
#endif

#ifdef _DEBUG_
        charF = charValArr(line.c_str(), ll);
        intsF = uIntValArr(              ll);
#else
        charF = charValArr(line.c_str(), ll);
#endif

        valsF = boolValArr(              ll);

        std::cout << " Line Loaded" << std::endl;

        for ( long i = 0; i < ll; i++ ) {
            c        = charF[i];
            vF       = dictF[c];

#ifdef _DEBUG_
            intsF[i] = vF;
            std::cout << "i " << i << " c " << c << " vF " << vF << std::endl;
#else
            charF[i] = vF;
#endif

            if ( vF == 127 ) {
#ifdef _DEBUG_
                if ( line.length() <= 100 ) {
                    std::cout << " BAD"                          << std::endl;
                    std::cout << "  SEQ   :           " << charF << std::endl;
                    std::cout << "  INTS  :           " << intsF << std::endl;
                    std::cout << "  VALS  :           " << valsF << std::endl;
                }
#endif
                long js = i - kmer_size + 1;
                long je = i + kmer_size;

                if ( js <  0  ) { js =  0; }
                if ( js >= ll ) { js =  0; }
                if ( je >= ll ) { je = ll; }
#ifdef _DEBUG_
                std::cout << "   js " << js << " je " << je << std::endl;
#endif

                for ( ulong j = js; j < je; j++ ) {
                    valsF[j] = 1;
#ifdef _DEBUG_
                    std::cout << "   js " << js << " je " << je << " j " << j;
                    
                    if ( line.length() <= 100 ) {
                        std::cout << " " << valsF;
                    }
                    
                    std::cout << " " << valsF.size() << std::endl;
#endif
                }
            }//if ( vF == 127 ) {

/*
#ifdef _DEBUG_
        std::cout << " SEQ   : " << charF << std::endl;
        std::cout << " INTS  : " << intsF << std::endl;
        std::cout << " VALIDS: " << valsF << std::endl;
#endif
*/

            if ( i < (kmer_size-1) ) {
#ifdef _DEBUG_
                std::cout << " seq too small  : " << i << " <  " << (kmer_size-1) << std::endl;
#endif
            } else {
#ifdef _DEBUG_
                std::cout << " seq long enough: " << i << " >= " << (kmer_size-1) << std::endl;
#endif
                bool valF = valsF[ i  ];

                if ( valF ) {
#ifdef _DEBUG_
                    std::cout << "  position not valid" << std::endl;
#endif

                } else {
#ifdef _DEBUG_
                    std::cout << "  position valid" << std::endl;
#endif


#ifdef _USE_SLICE_
                    sl               = std::slice(i - kmer_size + 1, kmer_size, 1);
                    charValArr kchaF = charF[ sl ];
#else
                    std::copy(std::begin(charF) + i - kmer_size + 1, std::begin(charF) + i + kmer_size, std::begin(kchaF));
#endif



#ifdef _DEBUG_
#ifdef _USE_SLICE_
                    uIntValArr kintF = intsF[ sl ];
#else
                    std::copy(std::begin(intsF) + i - kmer_size + 1, std::begin(intsF) + i + kmer_size, std::begin(kintF));
#endif

                    std::cout << " I   : " << i;
                    std::cout << " KMER: " << kchaF;
                    std::cout << " VALS: " << kintF;
                    std::cout << "\n";
#endif

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
#ifdef _DEBUG_
                        kcF   = kintF[             pos     ];
#else
                        kcF   = kchaF[             pos     ];
#endif
                        kcR   = 3 - kcF;
                        pvF   = pows[              pos     ];
                        pvR   = pows[  kmer_size - pos - 1 ];

#ifdef _DEBUG_
                        std::cout << "  I: "     << i    << " POS : "   << (pos+1)
                                  << " VALID: "  << valF
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
                                  << " SUM AF: " << resF << " SUM AR: " << resR << std::endl;
#endif
                    } //for ( unsigned int pos = 0; pos < kmer_size; pos++ ) {

                    resM = ( resF <= resR ) ? resF : resR;

                    q.insert(resM);

#ifdef _DEBUG_
                    std::cout << "  RESF: " << resF  << " RESR  : " << resR << " RESM : " << resM << "\n" << std::endl;
#endif
                }// if ( valF == 0 ) {
            }//if ( i >= kmer_size ) {
        }//for (ulong i = 0; i < ll; i++) {
    }//if ( line.length() >= kmer_size ) {
}

void extract_kmers::save_kmer(  const std::string &outfile ) {
    if ( get_total() > 0 ) {
        std::cout << "SAVING TO: " << outfile << " SIZE " << (get_total()*sizeof(ulong)) << std::endl;

        //https://stackoverflow.com/questions/12372531/reading-and-writing-a-stdvector-into-a-file-correctly
        std::ofstream outfhd(outfile, std::ios::out | std::ofstream::binary);
        if (!outfhd) throw std::runtime_error("error opening file");
        //std::copy(q.begin(), q.end(), std::ostreambuf_iterator<ulong>(outfhd));
        //outfhd.write(reinterpret_cast<const char*>(&q.begin()), q.size()*sizeof(ulong));
        for (std::set<ulong>::iterator it=q.begin(); it!=q.end(); ++it) {
            outfhd.write(reinterpret_cast<const char*>(&(*it)), sizeof(ulong));
        }
        outfhd.close();

#ifdef _DEBUG_
        read_kmer(outfile);
#endif
    } else {
        std::cout << "NO KMER TO SAVE" << std::endl;
    }
}

void extract_kmers::read_kmer(  const std::string &infile  ) {
        std::cout << "READING BACK FROM: " << infile << std::endl;

        //https://stackoverflow.com/questions/15138353/reading-the-binary-file-into-the-vector-of-unsigned-chars
        std::streampos fileSize;
        std::streampos regs;

        std::ifstream infhd(infile, std::ios::in | std::ifstream::binary);
        if (!infhd) throw std::runtime_error("error opening file");
        infhd.seekg(0, std::ios::end);
        fileSize = infhd.tellg();
        regs = fileSize / sizeof(ulong);
        infhd.seekg(0, std::ios::beg);

        std::cout << " SIZE: " << fileSize << " REGISTERS " << regs << std::endl;
        std::vector<ulong> newVector(regs);

        //std::copy(iter, std::istreambuf_iterator<char>{}, std::back_inserter(newVector));
        infhd.read((char*) &newVector[0], fileSize);
        infhd.close();
        std::cout << " LENGHT: " << newVector.size() << std::endl;

#ifdef _DEBUG_
        std::cout << newVector << std::endl;
#endif
}


/*
http://en.cppreference.com/w/cpp/algorithm/set_symmetric_difference
http://en.cppreference.com/w/cpp/algorithm/set_difference
http://en.cppreference.com/w/cpp/algorithm/set_intersection
http://en.cppreference.com/w/cpp/algorithm/set_union
*/
