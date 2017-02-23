#ifndef __H_KMER_SET_COMPRESSION__
#define __H_KMER_SET_COMPRESSION__

//https://github.com/hoxnox/csio

#include <string>
#include <iostream>
#include <fstream>

typedef std::string                        string;

#ifndef _DO_NOT_USE_ZLIB_
 // COMPRESS
    #ifndef _DO_NOT_USE_BGZF_
     // USE BGZIP
    #include "htslib/hts.h"
    #include "htslib/bgzf.h"
    #include "htslib/hfile.h"
    #include "htslib/thread_pool.h"
    #include "cram/pooled_alloc.h"
        
    #define BUFSZ 32768
    
    #else  //#ifdef _DO_NOT_USE_BGZF_
     // USE GZSTREAM
    #include <gzstream.h>
    #endif //#ifdef _DO_NOT_USE_BGZF_
#else  //#ifdef _DO_NOT_USE_ZLIB_
 // USE TEXT
#endif //#ifndef _DO_NOT_USE_ZLIB_




#ifndef _DO_NOT_USE_BGZF_
static void error(const char *format, ...);

typedef struct bgzf_job {
    BGZF *fp;
    unsigned char comp_data[BGZF_MAX_BLOCK_SIZE];
    size_t comp_len;
    unsigned char uncomp_data[BGZF_MAX_BLOCK_SIZE];
    size_t uncomp_len;
    int errcode;
    int64_t block_address;
    int hit_eof;
} bgzf_job;

enum mtaux_cmd {
    NONE = 0,
    SEEK,
    HAS_EOF,
    CLOSE,
};

typedef struct bgzf_mtaux_t {
    // Memory pool for bgzf_job structs, to avoid many malloc/free
    pool_alloc_t *job_pool;
    bgzf_job *curr_job;

    // Thread pool
    int n_threads;
    int own_pool;
    hts_tpool *pool;

    // Output queue holding completed bgzf_jobs
    hts_tpool_process *out_queue;

    // I/O thread.
    pthread_t io_task;
    pthread_mutex_t job_pool_m;
    int jobs_pending; // number of jobs waiting
    int flush_pending;
    void *free_block;
    int hit_eof;  // r/w entirely within main thread

    // Message passing to the reader thread; eg seek requests
    int errcode;
    uint64_t block_address;
    int eof;
    pthread_mutex_t command_m; // Set whenever fp is being updated
    pthread_cond_t command_c;
    enum mtaux_cmd command;
} mtaux_t;

static off_t bgzf_htell(BGZF *fp);

class obgzf {
    private:
        BGZF*  fp;
        int    valid;
        size_t size;

    public:
        obgzf();
        int    open(const char* name);
        void   close();
        void   write(const void *data, size_t length);
        bool   operator!();
        size_t tellp();
        void   seekp(const size_t p, const std::ios_base::seekdir dir);
        bool   good();
};

class ibgzf {
    private:
        BGZF*         fp;
        int           valid;
        std::istream *is;

    public:
        ibgzf();
        
        int    open(const char* name);
        void   close();
        bool   operator!();
        size_t tellg();
        void   seekg(const size_t p, const std::ios_base::seekdir dir);
        bool   good();
        bool   get_line(std::string& line);
        bool   read(char* c, size_t s);
};
#endif // #ifndef _DO_NOT_USE_BGZF_






//https://stackoverflow.com/questions/874134/find-if-string-ends-with-another-string-in-c
bool hasEnding (string const &fullString, string const &ending);

class filestream {
    typedef std::basic_ostream<char> boc;
    typedef const char* cc;
    
    std::string filename;
    char        mode;
    char        type;
    
    #ifndef _DO_NOT_USE_ZLIB_
    #ifndef _DO_NOT_USE_BGZF_
           // USE BGZIP
        obgzf         outfhdz;
        ibgzf         infhdz ;
    #else  // #ifdef  _DO_NOT_USE_BGZF_
           // USE GZIP
        ogzstream     outfhdz;
        igzstream     infhdz ;
    #endif // #ifdef  _DO_NOT_USE_BGZF_
    #endif // #ifndef _DO_NOT_USE_ZLIB_
    // USE TEXT
    std::ofstream  outfhdt;
    std::ifstream  infhdt ;
    std::istream  *is;
            
    public:
        filestream(const std::string& lfilename, char lmode, char ltype='a');
        void close();
        //std::basic_ostream<char>& write(const char* c, size_t s) {
        void write(const char* c, size_t s);
        bool read(char* c, size_t s);
        bool operator!();
        bool get_line(std::string& line);
        size_t tell();
        bool good();
        void seek(const size_t p, const std::ios_base::seekdir dir);
};



#endif //#ifndef __H_KMER_SET_COMPRESSION__