#ifndef __H_KMET_SET__
#define __H_KMET_SET__

#include <set>
#include <valarray>     // std::valarray, std::slice
#include <vector>
#include <string>
#include <sys/types.h>

typedef unsigned long ulong;
//typedef unsigned double    udouble;

typedef std::set<ulong, std::less<ulong> > setuLongLess;
//http://en.cppreference.com/w/cpp/numeric/valarray/apply
//http://en.cppreference.com/w/cpp/algorithm/for_each

/*
template<class T> using max_set  = std::set<T, std::greater<T> >;
template<class T> using min_set  = std::set<T, std::less<T> >;
*/

//using namespace std;

int  fact (int n);
void version ();

typedef std::valarray<char>                charValArr;
typedef std::valarray<ulong>               uLongValArr;
typedef std::valarray<int>                 intValArr;
typedef std::valarray<int>                 boolValArr;

typedef std::vector<std::string>           strVec;
typedef std::vector<ulong>                 ulongVec;
//typedef std::vector<double>                doubleVec;

class extract_kmers {
    private:
        int         kmer_size;
        ulong       lineNum;
        ulong       ll;

        ulong       resF;
        ulong       resR;
        ulong       resM;

        ulong       kcF;
        ulong       pvF;
        ulong       cvF;

        ulong       kcR;
        ulong       pvR;
        ulong       cvR;

        char        c;
        int         vF;

        int         dictF[256];
        ulong       pows[32] = {};

#ifndef _USE_SLICE_
        charValArr  kchaF;
        uLongValArr kintF;
#endif

        charValArr  charF;
        uLongValArr intsF;
        boolValArr  valsF;

        setuLongLess q;
    public:
        extract_kmers(    const int ks);
        ~extract_kmers();
        void         read_file_one_liner( const std::string &infile  );
        void         parse_line(          const std::string &line    );
        void         save_kmer_db(        const std::string &outfile );
        void         read_kmer_db(        const std::string &infile , ulongVec &newVector );
        ulongVec     read_kmer_db(        const std::string &infile  );
        void         merge_kmers(         const std::string &outfile, const strVec &infiles, ulongVec &mat );
        ulongVec     merge_kmers(         const std::string &outfile, const strVec &infiles   );
        ulong        get_db_size(         const std::string &infile  );
        ulong        get_total();
        void         print_all();
};

#endif //__H_KMET_SET__
