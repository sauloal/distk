#ifndef __H_KMER_SET__
#define __H_KMER_SET__

#include "defs.hpp"

#include "progressbar.hpp"

#include "kmer_set_compression.hpp"

/*
#include "sorted_vector.hpp"
*/

#include "set_alloc.hpp"

//http://en.cppreference.com/w/cpp/numeric/valarray/apply
//http://en.cppreference.com/w/cpp/algorithm/for_each

#include "header.hpp"

#include "fileholder.hpp"

//using namespace std;



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



int  fact (int n);
void version ();













class extract_kmers {
    private:
        int          dictF[256];

        ulong        pows[32] = {};
        ulong        clean;

        headerInfo   header;
        
        setuLongLess q;
        MutexType    lock;

        void         init1();
        void         init2(const int ks);
        void         init3();

        void         reserve();
        ulong        get_max_size();
        
        progressBar  progressRead;
        progressBar  progressKmer;
        
    public:
        extract_kmers();
        extract_kmers(    const int ks         );
        //~extract_kmers();
        ulong         get_number_key_frames();
        void          set_number_key_frames(const ulong      kf      );
        void          read_one_liner(       const string    &infile  );
        void          read_fasta(           const string    &infile  );
        void          read_fastq(           const string    &infile  );
        void          parse_line(                 string    &line    );
        void          save_kmer_db(         const string    &outfile );
        void          read_kmer_db(         const string    &infile  );
        ulong         get_db_file_size(     const string    &infile  );
        ulong         get_db_num_registers( const string    &infile  );
        ulongVec      get_kmer_db();
        ulong         size();
        void          print_all();
    private:
        template<typename T>
        void          read_one_liner(       const string   &infile, T  &infhd   );
        //template<typename T>
        //ulong         get_db_file_size(          T  &infhd   );
        template<typename T>
        ulong         get_db_num_registers(       T        &infhd   );
        template<typename T>
        void          encoder(                    T        &outfhd  );
        template<typename T>
        void          decoder(                    T        &infhd   );
};


#endif //__H_KMET_SET__