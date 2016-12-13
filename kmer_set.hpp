#ifndef __H_KMET_SET__
#define __H_KMET_SET__

#include <set>
#include <valarray>     // std::valarray, std::slice
#include <string>

typedef unsigned long ulong;

typedef std::set<ulong, std::less<ulong> > setLongLess;
//http://en.cppreference.com/w/cpp/numeric/valarray/apply
//http://en.cppreference.com/w/cpp/algorithm/for_each

/*
template<class T> using max_set  = std::set<T, std::greater<T> >;
template<class T> using min_set  = std::set<T, std::less<T> >;
*/

//using namespace std;

int fact (int n);
void version ();

typedef std::valarray<char>                charValArr;
typedef std::valarray<ulong>               uIntValArr;
typedef std::valarray<int>                 intValArr;
typedef std::valarray<int>                 boolValArr;

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
        charValArr kchaF;
        uIntValArr kintF;
#endif

        charValArr charF;
        uIntValArr intsF;
        boolValArr valsF;

        setLongLess q;
    public:
        extract_kmers(    const int ks);
        ~extract_kmers();
        void  read_file(  const std::string &infile  );
        void  parse_line( const std::string &line    );
        void  save_kmer(  const std::string &outfile );
        void  read_kmer(  const std::string &infile  );
        ulong get_total();
        void  print_all();
};

#endif //__H_KMET_SET__
