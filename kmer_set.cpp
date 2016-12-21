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
    std::cout << "version     : " << STRING(__PROG_VERSION__) << "\n"
              << "build date  : " << STRING(__COMPILE_DATE__) << std::endl;

#ifdef _DEBUG_
    std::cout << "COMPILE FLAG: _DEBUG_" << std::endl;
#endif

#ifdef _PRINT_LINE_LENGTHS_
    std::cout << "COMPILE FLAG: _PRINT_LINE_LENGTHS_" << std::endl;
#endif

#ifdef _NO_DIFF_ENCODING_
    std::cout << "COMPILE FLAG: _NO_DIFF_ENCODING_" << std::endl;
#endif

/*
 *7 7           2m52.768s
 *7 7 use slice 4m32.193s
*/

/*
KMER SIZE: 11
clean 1048575
TOTAL: 2096814
SAVING TO: test/test7.11.kmer SIZE 16774512
SAVED
FINISHED

real    9m53.257s
user    9m46.047s
sys     0m6.375s


version      : 9072332-dirty
build date   : Mon 19 Dec 18:41:34 STD 2016
COMPILE FLAG: _USE_BITSHIFT_
 KMER SIZE: 11
clean 1048575
TOTAL: 2096814
SAVING TO: test/test7.11.kmer SIZE 16774512
SAVED
FINISHED

real    8m36.025s
user    8m30.031s
sys     0m5.719s


//NO COPY
version     : 46466e7-dirty
build date  : Tue 20 Dec 01:58:06 STD 2016
 KMER SIZE: 11
clean 1048575
TOTAL: 2096814
SAVING TO: test/test7.11.kmer SIZE 16774512
SAVED
FINISHED

real    9m25.364s
user    9m21.766s
sys     0m2.984s





version      : 9072332-dirty
build date   : Mon 19 Dec 18:41:34 STD 2016
COMPILE FLAG: _USE_BITSHIFT_
 KMER SIZE: 15
clean 268435455
TOTAL: 185771860
SAVING TO: test/test7.15.kmer SIZE 1486174880
SAVED

FINISHED

real    24m17.492s
user    23m14.953s
sys     0m58.906s

version     : 9072332-dirty
build date  : Mon 19 Dec 22:24:12 STD 2016
 KMER SIZE: 15
clean 268435455
TOTAL: 185771860
SAVING TO: test/test7.15.kmer SIZE 1486174880
SAVED
FINISHED

real    25m13.121s
user    24m23.984s
sys     0m45.391s

test6.07.kmer kmer           gz
normal        65536          12320 (18.79%) 
diff          40968 (62.51%)   419 ( 0.63% - gz 3.35%)
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







extract_kmers::extract_kmers(const int ks): kmer_size(ks), lineNum(0) {
    std::cout << " KMER SIZE: " << kmer_size << std::endl;

    for ( int i = 0; i < 256; i++ ) {
        dictF[i] = 78;
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

    //cleans first two bits
    clean = ((ulong)(pow(2, ((kmer_size-1)*2)))-1);

    std::cout << "clean " << clean << std::endl;
}

/*
extract_kmers::~extract_kmers(){
        //q.clear();
}
*/

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
            //std::cout << "Got line" << std::endl;
            parse_line(line);
        }//while (getline(infhd,line)) {

        std::cout << "TOTAL: " <<  size() << std::endl;

#ifdef _DEBUG_
        print_all();
#endif

        infhd.close();
    }
}

void          extract_kmers::read_fasta(          const std::string &infile  ) {
    /*
     * TODO: IMPLEMENT + GZ VERSION
     */
    std::ifstream infhd(infile);
    infhd.close();
}

void          extract_kmers::read_fastq(          const std::string &infile  ) {
    /*
     * TODO: IMPLEMENT + GZ VERSION
     */
    std::ifstream infhd(infile);
    infhd.close();
}

void          extract_kmers::parse_line(                std::string &line    ) {
    ulong       ll = line.length();

#ifdef _DEBUG_
    if ( ll <= 100 ) {
        std::cout << "Line: " << line << std::endl;
    }
#endif

    ulong resF = 0;
    ulong resR = 0;
    ulong resM = 0;

    ulong kcF  = 0;
    ulong pvF  = 0;
    ulong cvF  = 0;

    ulong kcR  = 0;
    ulong pvR  = 0;
    ulong cvR  = 0;

    char  c;
    int   vF;

    ulong tainted = 0;
    bool  valid   = false;

    if ( ll >= kmer_size ) {
        /*
         * TODO: Add mutex
         */
        lineNum          += 1;

#ifdef _PRINT_LINE_LENGTHS_
        std::cout << " Line :: Length: " << ll << " Num: " << lineNum;
#endif


#ifdef _PRINT_LINE_LENGTHS_
        std::cout << " Line Loaded" << std::endl;
#endif

        for ( long i = 0; i < ll; i++ ) {
            c        = line[i];
            vF       = dictF[c];
            line[i]  = vF;

#ifdef _DEBUG_
            std::cout << "i " << i << " c " << c << " (" << (int)c << ") "<< " vF " << vF << std::endl;
#endif

            if ( vF == 78 ) {
                valid = false;

#ifdef _DEBUG_
                if ( line.length() <= 100 ) {
                    std::cout << " BAD"                          << std::endl;
                    //std::cout << "  VALS  :           " << valsF << std::endl;
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

                tainted = je;
            }//if ( vF == 78 ) {


            if ( i < (kmer_size-1) ) {
                valid = false;
#ifdef _DEBUG_
                std::cout << " seq too small  : " << i << " <  " << (kmer_size-1) << std::endl;
#endif
            } else {
#ifdef _DEBUG_
                std::cout << " seq long enough: " << i << " >= " << (kmer_size-1) << std::endl;
#endif
                bool valF = (i < tainted);

                if ( valF ) {
                    valid = false;
#ifdef _DEBUG_
                    std::cout << "  position not valid. i: " << i << " tainted: " << tainted << std::endl;
#endif

                } else {
#ifdef _DEBUG_
                    std::cout << "  position valid" << std::endl;
#endif

                    if ( valid ) {
#ifdef _DEBUG_
                        std::cout << " VALID :: B :: resF: " << resF << " resR: " << resR << std::endl;
#endif //_DEBUG_

                        resF &= clean;
                            //resR &= clean;

#ifdef _DEBUG_
                        std::cout << " VALID :: & :: resF: " << resF << " resR: " << resR << std::endl;
#endif //_DEBUG_

                        resF = ( resF << 2 );
                        resR = ( resR >> 2 );

#ifdef _DEBUG_
                        std::cout << " VALID :: S :: resF: " << resF << " resR: " << resR << std::endl;
#endif //_DEBUG_

                        resF += (    vF                       );
                        resR += ( (3-vF) << ((kmer_size-1)*2) );

#ifdef _DEBUG_
                        std::cout << " VALID :: R :: resF: " << resF << " resR: " << resR << std::endl;
#endif //_DEBUG_

                    } else {
                        valid = true;

                        auto p_begin = line.begin() + (i - kmer_size + 1);
                        
                        resF = 0;
                        resR = 0;
                        resM = 0;

                        kcF  = 0;
                        pvF  = 0;
                        cvF  = 0;

                        kcR  = 0;
                        pvR  = 0;
                        cvR  = 0;

                        for ( unsigned long pos = 0; pos < kmer_size; pos++ ) {
                            auto a_pos = p_begin + pos;

                            kcF   = *a_pos;
                            kcR   = 3 - kcF;

                            cvF   = (kcF << ((kmer_size - pos - 1)*2));
                            cvR   = (kcR << (             pos     *2));

#ifdef _DEBUG_
                            std::cout << "  I: "     << i    << " POS : "   << (pos+1)
                                      << " VALID: "  << valF
                                      << " SUM BF: " << resF << " SUM BR: " << resR
                                      << " KCF: "    << kcF  << " KCR: "    << kcR
                                      << " VALF: "   << cvF  << " VALR: "   << cvR
                                      << " PVF: "    << pvF  << " PVR: "    << pvR;
#endif

                            resF += cvF;
                            resR += cvR;

#ifdef _DEBUG_
                            std::cout << " SUM AF: " << resF << " SUM AR: " << resR << std::endl;
#endif
                        } //for ( unsigned int pos = 0; pos < kmer_size; pos++ ) {
                    } // else if ( valid ) {
                    
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

#ifdef _NO_DIFF_ENCODING_
        for (std::set<ulong>::iterator it=q.begin(); it!=q.end(); ++it) {
            outfhd.write(reinterpret_cast<const char*>(&(*it)), sizeof(ulong));
        }
#else
        diff_encoder(outfhd);
#endif
        outfhd.close();

        std::cout << "SAVED" << std::endl;

#ifdef _DEBUG_
        //read_kmer_db(outfile);
#endif
    }
}

ulong         extract_kmers::get_db_file_size(    const std::string &infile  ) {
    /*
     * TODO: read delta format
     */
    std::ifstream infhd(infile, std::ios::in | std::ifstream::binary);

    if (!infhd) {
        perror((std::string("error reading input file: ") + infile).c_str());
        throw std::runtime_error("error reading input file: " + infile);
        //return;
    }
    
    return get_db_file_size(infhd);
}

ulong         extract_kmers::get_db_file_size(    std::ifstream &infhd  ) {
    ulong startPos = infhd.tellg();

    infhd.seekg(0, std::ios::end);

    ulong fileSize = infhd.tellg();

    infhd.seekg(startPos, std::ios::beg);

    return fileSize;
}

ulong         extract_kmers::get_db_num_registers(const std::string &infile  ) {
    ulong numRegs = 0;

#ifdef _NO_DIFF_ENCODING_
    ulong fileSize = get_db_file_size(infile);
    numRegs        = fileSize / sizeof(ulong);
#else

    std::ifstream infhd(infile, std::ios::in | std::ifstream::binary);

    if (!infhd) {
        perror((std::string("error reading input file: ") + infile).c_str());
        throw std::runtime_error("error reading input file: " + infile);
        //return;
    }

    numRegs = get_db_num_registers(infhd);
    
    infhd.close();
#endif
    return numRegs;
}

ulong         extract_kmers::get_db_num_registers(std::ifstream &infhd) {
    ulong numRegs = 0;
#ifdef _NO_DIFF_ENCODING_
    ulong fileSize = get_db_file_size(infhd);
    numRegs = fileSize / sizeof(ulong);
#else
    ulong startPos = infhd.tellg();
    
    infhd.read((char *)&numRegs,sizeof(numRegs));

    infhd.seekg(startPos, std::ios::beg);
#endif
    return numRegs;
}

void          extract_kmers::read_kmer_db(        const std::string &infile  ) {
    /*
     * TODO: load into q
     *       read delta format
     */

    std::cout << "  READING BACK FROM: " << infile << std::endl;
    
    std::ifstream infhd(infile, std::ios::in | std::ifstream::binary);

    std::cout << "    OPEN" << std::endl;

    ulong fileSize = get_db_file_size(infile);
    ulong regs     = get_db_num_registers(infile);

    std::cout << "    SIZE: " << fileSize << " REGISTERS " << regs << std::endl;

    std::cout << "   CLEARING" << std::endl;

    q.clear();
    
    std::cout << "   ALLOCATING " << regs << " REGS" << std::endl;

    q.get_allocator().allocate(regs);
    
    //std::copy(iter, std::istreambuf_iterator<char>{}, std::back_inserter(newVector));
    //infhd.read((char*)&(*q.cbegin()), fileSize);

#ifdef _NO_DIFF_ENCODING_
    ulong buffer;
    while(infhd.read((char *)&buffer,sizeof(buffer)))
    {
        q.insert(buffer);
    }
#else
    diff_decoder(infhd);
#endif

    std::cout << "    CLOSE" << std::endl;
    infhd.close();

    std::cout << "   READ" << std::endl;

    std::cout << "    LENGHT: " << q.size() << std::endl;

    std::cout << "   DONE" << std::endl;
}

void  extract_kmers::diff_encoder(std::ofstream &outfhd) {
    /*
     * TODO: Implement roling difference encoding
     *       <int8>[<char>,n]
     *       '     '--> Diff from prev to current using the minimum number of chars
     *       '--------> Number of chars
     * 1    1    1 <1,1>
     * 2    1    1 <1,1>
     * 3    1    1 <1,1>
     * 5    1    2 <1,1>
     * 10   1    5 <1,1>
     * 200  2  190 <2,12,7>  [ 190 as 2 chars]
     * 2000 3 1800 <3,7,0,8> [1800 as 3 chars]
     *
     * check minimum number of bits as n
     * save n
     * cast ulong to n chars
     * save chars
     *
     * read 1 char
     * read n chars
     * cast n chars to ulong
     */
    ulong        diff    = 0;
    ulong        prev    = 0;
    unsigned int lenI    = 0;
    ulong        numRegs = q.size();
    
    std::cout << "NUM REGISTERS: " << numRegs << std::endl;
    
    outfhd.write(reinterpret_cast<const char*>( &numRegs ), sizeof(numRegs));
    
    for (std::set<ulong>::iterator it=q.begin(); it!=q.end(); ++it) {
        if ( it == q.begin() ) {
            prev = 0;
        }

        diff = *it - prev;
        lenI = diff == 0 ? 1 : lrint(ceil(log2(diff)/8.0));
        lenI = lenI == 0 ? 1 : lenI;
//#ifdef _DEBUG_
        std::cout << "val " << *it << " prev " << prev << " diff " << diff << " lenI " << lenI << std::endl;
//#endif
        outfhd.write(reinterpret_cast<const char*>( &lenI ), sizeof(lenI));
        outfhd.write(reinterpret_cast<const char*>(&(diff)),        lenI );
        prev = *it;
    }
}

void  extract_kmers::diff_decoder(std::ifstream &infhd) {
    //https://stackoverflow.com/questions/15138353/reading-the-binary-file-into-the-vector-of-unsigned-chars
    std::cout << "   READING" << std::endl;

    ulong        val  = 0;
    ulong        diff = 0;
    ulong        prev = 0;
    unsigned int lenI = 0;

    ulong        regs = 0;
    infhd.read((char *)&regs,sizeof(ulong));
    std::cout << "   READING " << regs << " registers" << std::endl;
    
    
    while(infhd.read((char *)&lenI,sizeof(lenI))) {
        infhd.read((char *)&diff,       lenI );
        val  = prev + diff;
//#ifdef _DEBUG_
        std::cout << "val " << val << " prev " << prev << " diff " << diff << " lenI " << lenI << std::endl;
//#endif
        q.insert(val);
        prev = val;
        lenI = 0;
        diff = 0;
    }
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
