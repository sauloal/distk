#ifndef __KMET_SET__
#define __KMET_SET__

#include <string>
#include <set>
#include <valarray>     // std::valarray, std::slice

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
        setLongLess q;

        charValArr charF;
        uIntValArr intsF;
        intValArr  valsF;

    public:
        extract_kmers(    const int ks);
        void  read_file(  const std::string &infile  );
        void  parse_line( const std::string &line    );
        void  save_kmer(  const std::string &outfile );
        void  read_kmer(  const std::string &infile  );
        ulong get_total();
        void  print_all();
};

#endif //__KMET_SET__
