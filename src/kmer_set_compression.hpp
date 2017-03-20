#ifndef __H_KMER_SET_COMPRESSION__
#define __H_KMER_SET_COMPRESSION__

//https://github.com/hoxnox/csio

#include <string>
#include <iostream>
#include <fstream>

// USE GZSTREAM
#include <gzstream.h>

typedef std::string    string;
typedef std::ofstream  ofstream;
typedef std::ifstream  ifstream;


class filestream {
    string         filename;
    char           mode;
    char           type;

    igzstream      infhdz ;
    ogzstream      outfhdz;
    
    ifstream       infhdt ;
    ofstream       outfhdt;
            
    public:
        filestream(const std::string& lfilename, char lmode, char ltype='a');
        void   close();
        void   write(const char* c, size_t s);
        bool   read(char* c, size_t s);
        bool   operator!();
        bool   get_line(std::string& line);
        size_t tell();
        bool   good();
        void   seek(const size_t p, const std::ios_base::seekdir dir);
};



#endif //#ifndef __H_KMER_SET_COMPRESSION__