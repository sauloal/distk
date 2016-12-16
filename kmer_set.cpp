#include "kmer_set.hpp"

//http://www.linuxquestions.org/questions/programming-9/mmap-tutorial-c-c-511265/
#include <iostream>
#include <fstream>
#include <iterator>

#include <stdio.h>
#include <string.h>

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

/*
 *7 7           2m52.768s
 *7 7 use slice 4m32.193s
*/
}


std::ostream& operator<< (std::ostream& out, const std::vector<std::string>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    std::copy (std::begin(v), std::end(v), std::ostream_iterator<std::string>(out, ", "));
    out << "\b\b]";
  }
  return out;
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





//https://stackoverflow.com/questions/32640327/how-to-compute-the-size-of-an-intersection-of-two-stl-sets-in-c
struct Counter
{
    struct value_type { template<typename T> value_type(const T&) { } };
    void   push_back(const value_type&) { ++count; }
    size_t count = 0;
};

template<typename T1, typename T2>
size_t intersection_size(const T1& s1, const T2& s2)
{
    Counter c;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(c));
    return c.count;
}




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
}

extract_kmers::~extract_kmers(){
        charF.resize(0);
        valsF.resize(0);

#ifdef _DEBUG_
        intsF.resize(0);
#endif

        //q.clear();
}

ulong         extract_kmers::size() {
    return q.size();
}

void          extract_kmers::print_all() {
    for (std::set<ulong>::iterator it=q.begin(); it!=q.end(); ++it) {
        std::cout << ' ' << *it;
        std::cout << '\n';
    }
}

void          extract_kmers::read_file_one_liner( const std::string &infile  ) {
    std::ifstream infhd(infile);

    if (!infhd) {
        perror((std::string("Error opening input file: ") + infile).c_str());
        throw std::runtime_error("error opening input file: " + infile);
        //return;
    }

    if(!infhd.is_open()) {
        perror((std::string("Error reading input file: ") + infile).c_str());
        throw std::runtime_error("error opening input file: " + infile);
        //return;

    } else {
        std::string line;
        //std::valarray<const char *> l;

        while (getline(infhd,line)) {
            parse_line(line);
        }//while (getline(infhd,line)) {

        std::cout << "TOTAL: " <<  size() << std::endl;

#ifdef _DEBUG_
        print_all();
#endif

        infhd.close();
    }
}

void          extract_kmers::parse_line(          const std::string &line    ) {
#ifdef _DEBUG_
    if ( line.length() <= 100 ) {
        std::cout << "Line: " << line << std::endl;
    }
#endif


    std::slice sl;
    //charValArr kchaF(kmer_size);
    //uIntValArr kintF(kmer_size);

    if ( line.length() >= kmer_size ) {
        lineNum          += 1;
        ll                = line.length();

#ifdef _PRINT_LINE_LENGTHS_
        std::cout << " Line :: Length: " << ll << " Num: " << lineNum;
#endif

        charF = charValArr( line.c_str(), ll);
        valsF = boolValArr(               ll);

#ifdef _DEBUG_
        intsF = uLongValArr(              ll);
#endif


#ifdef _PRINT_LINE_LENGTHS_
        std::cout << " Line Loaded" << std::endl;
#endif


        for ( long i = 0; i < ll; i++ ) {
            c        = charF[i];
            vF       = dictF[c];

#ifdef _DEBUG_
            intsF[i] = vF;
            std::cout << "i " << i << " c " << c << " (" << (int)c << ") "<< " vF " << vF << std::endl;
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
                std::cout << "  SEQ1  :           " << charF << std::endl;
                std::cout << "  INTS1 :           " << intsF << std::endl;
#endif
                bool valF = valsF[ i  ];

                if ( valF ) {
#ifdef _DEBUG_
                    std::cout << "  position not valid" << std::endl;
#endif

                } else {
#ifdef _DEBUG_
                    std::cout << "  position valid" << std::endl;
                    std::cout << "  SEQ2  :           " << charF << std::endl;
                    std::cout << "  INTS2 :           " << intsF << std::endl;
#endif


                    sl               = std::slice(i - kmer_size + 1, kmer_size, 1);
                    const charValArr  kchaF = charF[ sl ];
#ifdef _DEBUG_
                    const uLongValArr kintF = intsF[ sl ];
#endif //_DEBUG_


#ifdef _DEBUG_
                    std::cout << "  I: "   << i;
                    std::cout << " KMER: " << kchaF;
                    std::cout << " VALS: " << kintF;
                    std::cout << "\n";
#endif //_DEBUG_


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
                    /*
                     * TODO: rolling kmer
                    */
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

void          extract_kmers::save_kmer_db(        const std::string &outfile ) {
    if ( size() == 0 ) {
        std::cout << "NO KMER TO SAVE" << std::endl;

    } else {
        std::cout << "SAVING TO: " << outfile << " SIZE " << (size()*sizeof(ulong)) << std::endl;

        //https://stackoverflow.com/questions/12372531/reading-and-writing-a-stdvector-into-a-file-correctly
        std::ofstream outfhd(outfile, std::ios::out | std::ofstream::binary);
        
        if (!outfhd) {
            perror((std::string("error saving kmer file: ") + outfile).c_str());
            throw std::runtime_error("error saving kmer file: " + outfile);
            //return;
        }
        
        //std::copy(q.begin(), q.end(), std::ostreambuf_iterator<ulong>(outfhd));
        //outfhd.write(reinterpret_cast<const char*>(&q.begin()), q.size()*sizeof(ulong));
        for (std::set<ulong>::iterator it=q.begin(); it!=q.end(); ++it) {
            outfhd.write(reinterpret_cast<const char*>(&(*it)), sizeof(ulong));
        }

        outfhd.close();

        std::cout << "SAVED" << std::endl;

#ifdef _DEBUG_
        //read_kmer_db(outfile);
#endif
    }
}

ulong         extract_kmers::get_db_size(         const std::string &infile  ) {
    /*
     * TODO: read delta format
     */
    std::ifstream infhd(infile, std::ios::in | std::ifstream::binary);

    if (!infhd) {
        perror((std::string("error reading input file: ") + infile).c_str());
        throw std::runtime_error("error reading input file: " + infile);
        //return;
    }
    
    infhd.seekg(0, std::ios::end);

    ulong fileSize = infhd.tellg();

    return fileSize;
}

void          extract_kmers::read_kmer_db(        const std::string &infile  ) {
    /*
     * TODO: load into q
     *       read delta format
     */
    std::cout << "  READING BACK FROM: " << infile << std::endl;

    //https://stackoverflow.com/questions/15138353/reading-the-binary-file-into-the-vector-of-unsigned-chars
    ulong fileSize = get_db_size(infile);
    ulong regs     = fileSize / sizeof(ulong);

    std::cout << "    SIZE: " << fileSize << " REGISTERS " << regs << std::endl;

    std::cout << "   CLEARING" << std::endl;

    q.clear();
    
    std::cout << "   ALLOCATING " << regs << " REGS" << std::endl;

    q.get_allocator().allocate(regs);

    std::cout << "   READING" << std::endl;
    
    std::ifstream infhd(infile, std::ios::in | std::ifstream::binary);

    std::cout << "    OPEN" << std::endl;

    //std::copy(iter, std::istreambuf_iterator<char>{}, std::back_inserter(newVector));
    //infhd.read((char*)&(*q.cbegin()), fileSize);

    ulong buffer;
    while(infhd.read((char *)&buffer,sizeof(buffer)))
    {
        q.insert(buffer);
    }
    
    
    std::cout << "    CLOSE" << std::endl;
    infhd.close();

    std::cout << "   READ" << std::endl;

    std::cout << "    LENGHT: " << q.size() << std::endl;

    std::cout << "   DONE" << std::endl;
}

ulongVec      extract_kmers::get_kmer_db() {
    /*
     * TODO: return q
     */
    return ulongVec(q.begin(), q.end());
}

void          extract_kmers::merge_kmers(         const std::string &outfile, const strVec &infiles, ulongVec &mat ) {
    /*
     * TODO: read q
     */
    extract_kmers v1(kmer_size);
    extract_kmers v2(kmer_size);

    auto size = infiles.size();

    std::cout << "# files " << size << " " << infiles << std::endl;

    mat.resize(size * size);

    for( strVec::size_type i = 0; i < size; i++ ) {
        auto file1  = infiles[i];

        v1.read_kmer_db( file1 );

        std::cout << "I " << i << " (" << file1 << ") [" << v1.size() << "]" << std::endl;

        mat[((i * size) + i)] = v1.size();

        for( strVec::size_type j = i+1; j < size; j++ ) {
            auto pos1 = ( i * size ) + j;
            auto pos2 = ( j * size ) + i;

            /*
             *00 01 02 03
             *04 05 06 07
             *08 09 10 11
             *12 13 14 15
             *
             *   01 02 03
             *      06 07
             *         11
             *
             *
             *04
             *08 09
             *12 13 14
             *
             *00
             *   05
             *      10
             *         15
             */

            auto file2 = infiles[j];

            v2.read_kmer_db( file2 );

            std::cout << "  J " << j << " (" << file2 << ") [" << v2.size() << "] - " << pos1 << ":" << pos2 << " CALCULATING" << std::endl;

            size_t count = intersection_size( v1.get_kmer_db(), v2.get_kmer_db() );
            
            std::cout << "   COUNT " << count << std::endl;
            
            mat[pos1] = count;
            mat[pos2] = count;
        }
    }
    
    save_matrix(outfile, infiles, mat);
}

ulongVec      extract_kmers::merge_kmers(         const std::string &outfile, const strVec &infiles   ) {
    /*
     * TODO: return q
     */
    ulongVec mat;
    merge_kmers( outfile, infiles, mat );
    return mat;
}

void          extract_kmers::save_matrix(         const std::string &outfile, const strVec &infiles, const ulongVec &mat ) {
    if ( mat.size() > 0 ) {
        std::cout << "SAVING TO: " << outfile << ".matrix SIZE " << (mat.size()*sizeof(ulong)) << std::endl;

        std::string matrix = outfile.c_str() + std::string(".matrix");
        std::string index  = outfile.c_str() + std::string(".index" );
        
        //https://stackoverflow.com/questions/12372531/reading-and-writing-a-stdvector-into-a-file-correctly
        std::ofstream outfhd(matrix, std::ios::out | std::ofstream::binary);

        if (!outfhd) {
            perror((std::string("error saving matrix file: ") + matrix).c_str());
            throw std::runtime_error("error saving matrix file: " + matrix);
            //return;
        }
        
        //std::copy(q.begin(), q.end(), std::ostreambuf_iterator<ulong>(outfhd));
        //outfhd.write(reinterpret_cast<const char*>(&q.begin()), q.size()*sizeof(ulong));
        for (auto it=mat.begin(); it!=mat.end(); ++it) {
            outfhd.write(reinterpret_cast<const char*>(&(*it)), sizeof(ulong));
        }
        outfhd.close();

        
        
        std::ofstream outind(index, std::ios::out | std::ofstream::binary);
        
        if (!outind) {
            perror((std::string("error saving index file: ") + index).c_str());
            throw std::runtime_error("error saving index file: " + index);
            //return;
        }

        ulong c = 0;
        char* nl = new char[1];
        nl[0] = '\n';
        for (auto it=infiles.begin(); it!=infiles.end(); ++it) {
            auto n = (*it).c_str();
            std::cout << n << " " << strlen(n) << std::endl;
            if ( c > 0 ) {
                outind.write(nl, 1);                
            }
            outind.write(reinterpret_cast<const char*>(n), strlen(n));
            c++;
        }

        outind.close();
    } else {
        std::cout << "NO MATRIX TO SAVE" << std::endl;
    }
}

/*
http://en.cppreference.com/w/cpp/algorithm/set_symmetric_difference
http://en.cppreference.com/w/cpp/algorithm/set_difference
http://en.cppreference.com/w/cpp/algorithm/set_intersection
http://en.cppreference.com/w/cpp/algorithm/set_union
*/
