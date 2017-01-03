#ifndef __H_KMET_SET__
#define __H_KMET_SET__

#include <set>
#include <valarray>     // std::valarray, std::slice
#include <vector>
#include <string>
//#include <sys/types.h>

#ifndef _DO_NOT_USE_ZLIB_
#include <gzstream.h>
#endif

//http://bisqwit.iki.fi/story/howto/openmp/
#ifdef _OPENMP
#include <omp.h>
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

typedef std::string                        string;
typedef std::valarray<char>                charValArr;
typedef std::valarray<ulong>               uLongValArr;
typedef std::valarray<unsigned int>        uIntValArr;
typedef std::valarray<int>                 boolValArr;

typedef std::vector<string>                strVec;
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
        void          read_one_liner(      const string    &infile  );
        void          read_fasta(          const string    &infile  );
        void          read_fastq(          const string    &infile  );
        void          parse_line(                string    &line    );
        void          save_kmer_db(        const string    &outfile );
        void          read_kmer_db(        const string    &infile  );
        void          merge_kmers(         const string    &outfile, const strVec &infiles, ulongVec &mat );
        ulongVec      merge_kmers(         const string    &outfile, const strVec &infiles                );
        void          save_matrix(         const string    &outfile, const strVec &infiles, const ulongVec &mat );
        ulong         get_db_file_size(    const string    &infile  );
        ulong         get_db_num_registers(const string    &infile  );
        ulongVec      get_kmer_db();
        ulong         size();
        void          print_all();
    private:
        template<typename T>
        void          read_one_liner(            const string   &infile, T  &infhd   );
        template<typename T>
        ulong         get_db_file_size(          T  &infhd   );
        template<typename T>
        ulong         get_db_num_registers(      T  &infhd   );
        template<typename T>
        void          diff_encoder(              T  &outfhd  );
        template<typename T>
        void          diff_decoder(              T  &infhd   );
};

#endif //__H_KMET_SET__
