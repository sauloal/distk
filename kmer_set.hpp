#ifndef __H_KMET_SET__
#define __H_KMET_SET__

#include <set>
#include <valarray>     // std::valarray, std::slice
#include <vector>
#include <string>
#include <sys/types.h>

//http://bisqwit.iki.fi/story/howto/openmp/
#ifdef _OPENMP
# include <omp.h>
struct MutexType {
    MutexType()   { omp_init_lock(   &lock); }
    ~MutexType()  { omp_destroy_lock(&lock); }
    void Lock()   { omp_set_lock(    &lock); }
    void Unlock() { omp_unset_lock(  &lock); }

    MutexType(const MutexType& ) { omp_init_lock(&lock); }
    MutexType& operator= (const MutexType& ) { return *this; }
public:
        omp_lock_t lock;
};
#else
/* A dummy mutex that doesn't actually exclude anything,
* but as there is no parallelism either, no worries. */
struct MutexType {
    void Lock() {}
    void Unlock() {}
};
#endif

/* An exception-safe scoped lock-keeper. */
struct ScopedLock {
    explicit ScopedLock(MutexType& m) : mut(m), locked(true) { mut.Lock(); }
    ~ScopedLock() { Unlock(); }
    void Unlock() { if(!locked) return; locked=false; mut.Unlock(); }
    void LockAgain() { if(locked) return; mut.Lock(); locked=true; }
private:
    MutexType& mut;
    bool locked;
private: // prevent copying the scoped lock.
    void operator=(const ScopedLock&);
    ScopedLock(const ScopedLock&);
};





//http://en.cppreference.com/w/cpp/numeric/valarray/apply
//http://en.cppreference.com/w/cpp/algorithm/for_each

typedef unsigned long ulong;
typedef std::set< unsigned long > setuLongLess;

/*
template<class T> using max_set  = std::set<T, std::greater<T> >;
template<class T> using min_set  = std::set<T, std::less<T> >;
typedef std::set<ulong, std::less<ulong> > setuLongLess;
*/

//using namespace std;

int  fact (int n);
void version ();

typedef std::valarray<char>                charValArr;
typedef std::valarray<ulong>               uLongValArr;
typedef std::valarray<unsigned int>        uIntValArr;
typedef std::valarray<int>                 boolValArr;

typedef std::vector<std::string>           strVec;
typedef std::vector<ulong>                 ulongVec;
//typedef std::vector<double>                doubleVec;

class extract_kmers {
    private:
        int          kmer_size;
        int          dictF[256];
        ulong        pows[32] = {};

        ulong        lineNum;
        ulong        clean;

        setuLongLess q;
        MutexType    lock;

    public:
        extract_kmers(    const int ks);
        ~extract_kmers();
        void          read_file_one_liner( const std::string   &infile  );
        void          read_fasta(          const std::string   &infile  );
        void          read_fastq(          const std::string   &infile  );
        void          parse_line(                std::string   &line    );
        void          save_kmer_db(        const std::string   &outfile );
        void          read_kmer_db(        const std::string   &infile  );
        void          merge_kmers(         const std::string   &outfile, const strVec &infiles, ulongVec &mat );
        ulongVec      merge_kmers(         const std::string   &outfile, const strVec &infiles   );
        void          save_matrix(         const std::string   &outfile, const strVec &infiles, const ulongVec &mat );
        void          diff_encoder(              std::ofstream &outfhd  );
        void          diff_decoder(              std::ifstream &infhd   );
        ulongVec      get_kmer_db();
        ulong         get_db_file_size(    const std::string   &infile  );
        ulong         get_db_file_size(          std::ifstream &infhd   );
        ulong         get_db_num_registers(const std::string   &infile  );
        ulong         get_db_num_registers(      std::ifstream &infhd   );
        ulong         size();
        void          print_all();
};

#endif //__H_KMET_SET__
