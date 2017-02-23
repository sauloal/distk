//https://github.com/hoxnox/csio

#include "kmer_set_compression.hpp"

typedef std::string                        string;

#ifndef _DO_NOT_USE_ZLIB_
 // COMPRESS
    #ifndef _DO_NOT_USE_BGZF_
     // USE BGZIP
    const char *bgzf_suffix = ".gz";
    const char *idx_suffix  = ".gzi";
    const char *tmp_suffix  = ".tmp";
    #else  //#ifdef _DO_NOT_USE_BGZF_
     // USE GZSTREAM
    #endif //#ifdef _DO_NOT_USE_BGZF_
#else  //#ifdef _DO_NOT_USE_ZLIB_
 // USE TEXT
#endif //#ifndef _DO_NOT_USE_ZLIB_




#ifndef _DO_NOT_USE_BGZF_
static void error(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    exit(EXIT_FAILURE);
}



static off_t bgzf_htell(BGZF *fp) {
    if (fp->mt) {
        pthread_mutex_lock(&fp->mt->job_pool_m);
        off_t pos = fp->block_address + fp->block_clength;
        pthread_mutex_unlock(&fp->mt->job_pool_m);
        return pos;
    } else {
        return htell(fp->fp);
    }
}

obgzf::obgzf(): valid(0), size(0) {}
int obgzf::open(const char* name) {
    fp = bgzf_open(name, "w");
    if (fp == NULL) {
        fprintf(stderr, "[bgzip] can't create %s: %s\n", name, strerror(errno));
        valid = 1;
    }
    return valid;
}
void obgzf::close() {
    if (bgzf_close(fp) < 0) error("Close failed: Error %d", fp->errcode);
}
void obgzf::write(const void *data, size_t length) {
    size += length;
/*
    static const int WINDOW_SIZE = 64 * 1024;
    void *buffer;
    while ((c = read(f_src, buffer, WINDOW_SIZE)) > 0)
        if (bgzf_write(fp, buffer, c) < 0) error("Could not write %d bytes: Error %d\n", c, fp->errcode);
*/
    if (bgzf_write(fp, data, length) < 0) error("Could not write %d bytes: Error %d\n", length, fp->errcode);
}

bool obgzf::operator!() {
    return !valid;
}

size_t obgzf::tellp() {
    return size;
}

void obgzf::seekp(const size_t p, const std::ios_base::seekdir dir) {
    //std::ios::beg
    //outfhdz.seekp(p, dir);
}

bool obgzf::good() {
    return valid == 0;
}




ibgzf::ibgzf(): valid(0) {}

int ibgzf::open(const char* name) {
    fp = bgzf_open(name, "r");
    if (fp == NULL) {
        fprintf(stderr, "[bgzip] can't create %s: %s\n", name, strerror(errno));
        valid = 1;
    }
    return valid;
}

void ibgzf::close() {
    if (bgzf_close(fp) < 0) error("Close failed: Error %d", fp->errcode);
}

bool ibgzf::operator!() {
    return !valid;
}

size_t ibgzf::tellg() {
    return bgzf_htell(fp);
}

void ibgzf::seekg(const size_t p, const std::ios_base::seekdir dir) {
    //std::ios::beg
    //outfhdz.seekp(p, dir);
}

bool ibgzf::good() {
    return valid == 0;
}

bool ibgzf::get_line(std::string& line) {
    return false;
}

bool ibgzf::read(char* c, size_t s) {
    //buffer = malloc(BGZF_BLOCK_SIZE);
    //bgzf_index_build_init(fp);
    //int ret;
    //while ( (ret=bgzf_read(fp, buffer, BGZF_BLOCK_SIZE))>0 ) ;

    //if ( infhdt.read(c,s) ) {
    //    return true;
    //} else {
    //    return false;
    //}
    
    return false;
}        
#endif // #ifndef _DO_NOT_USE_BGZF_






//https://stackoverflow.com/questions/874134/find-if-string-ends-with-another-string-in-c
bool hasEnding (string const &fullString, string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}






filestream::filestream(const std::string& lfilename, char lmode, char ltype): filename(lfilename), mode(lmode), type(ltype) {
    if ( type == 'a' ) {
        if ( hasEnding(filename, ".gz") ) {
            type = 'z';
        } else {
            type = 't';
        }
    }
    
    if ( mode == 'r' ) {
        if ( type == 'z' ) {
            infhdz .open(filename.c_str());
        } else
        if ( type == 't' ) {
            infhdt .open(filename.c_str());
        }
    } else
    if ( mode == 'w' ) {
        if ( type == 'z' ) {
            outfhdz.open(filename.c_str());
        } else
        if ( mode == 't' ) {
            outfhdt.open(filename.c_str());
        }
    }
}

void filestream::close() {
    if ( mode == 'r' ) {
        if ( type == 'z' ) {
            infhdz .close();
        } else
        if ( type == 't' ) {
            infhdt .close();
        }
    } else
    if ( mode == 'w' ) {
        if ( type == 'z' ) {
            outfhdz.close();
        } else
        if ( mode == 't' ) {
            outfhdt.close();
        }
    }
}

//std::basic_ostream<char>& write(const char* c, size_t s) {
void filestream::write(const char* c, size_t s) {
    if ( mode == 'w' ) {
        if ( type == 'z' ) {
            outfhdz.write(c, s);
        } else
        if ( type == 't' ) {
            //return outfhd.write(c, s);
            outfhdt.write(c, s);
        }
    }
}

bool filestream::read(char* c, size_t s) {
    if ( mode == 'r' ) {
        if ( type == 'z' ) {
            return infhdz.read(c,s);
        } else
        if ( type == 't' ) {
            if ( infhdt.read(c,s) ) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

bool filestream::operator!() {
    if ( type == 'z' ) {
        return !!!outfhdz;                
    } else
    if ( type == 't' ) {
        return !!!outfhdt;
    }
}

bool filestream::get_line(std::string& line) {
    if ( mode == 'r' ) {
        if ( type == 'z' ) {
            return infhdz.get_line(line);
        } else
        if ( type == 't' ) {
            if ( std::getline(infhdt, line) ) {
                return true;
            } else {
                return false;
            }
        }
    } else {
        return false;
    }
}

size_t filestream::tell() {
    if ( mode == 'w' ) {
        if ( type == 'z' ) {
            return outfhdz.tellp();
        } else
        if ( type == 't' ) {
            return outfhdt.tellp();
        }
    } else
    if ( mode == 'r' ) {
        if ( type == 'z' ) {
            return infhdz.tellg();
        } else 
        if ( type == 't' ) {
            return infhdt.tellg();
        }
    }
}

bool filestream::good() {
    if ( mode == 'w' ) {
        if ( type == 'z' ) {
            return outfhdz.good();
        } else
        if ( type == 't' ) {
            return outfhdt.good();
        }
    } else
    if ( mode == 'r' ) {
        if ( type == 'z' ) {
            return infhdz.good();
        } else
        if ( type == 't' ) {
            return infhdt.good();
        }
    }
}

void filestream::seek(const size_t p, const std::ios_base::seekdir dir) {
    //std::ios::beg
    if ( mode == 'w' ) {
        if ( type == 'z' ) {
            outfhdz.seekp(p, dir);
        } else
        if ( type == 't' ) {
            outfhdt.seekp(p, dir);
        }
    } else
    if ( mode == 'r' ) {
        if ( type == 'z' ) {
            infhdz.seekg(p, dir);
        } else
        if ( type == 't' ) {
            infhdt.seekg(p, dir);
        }
    }
}

