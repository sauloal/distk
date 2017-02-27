//https://github.com/hoxnox/csio

#include "kmer_set_compression.hpp"
#include "tools.hpp"




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
            if ( infhdz.read(c,s) ) {
                return true;
            } else {
                return false;
            }
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
    if ( mode == 'r' ) {
        if ( type == 'z' ) {
            return !infhdz;                
        } else
        if ( type == 't' ) {
            return !infhdt;
        }
    } else
    if ( mode == 'w' ) {
        if ( type == 'z' ) {
            return !outfhdz;                
        } else
        if ( type == 't' ) {
            return !outfhdt;
        }
    }
}

bool filestream::get_line(std::string& line) {
    if ( mode == 'r' ) {
        if ( type == 'z' ) {
            if ( getline(infhdz, line) ) {
                return true;
            } else {
                return false;
            }
        } else
        if ( type == 't' ) {
            if ( getline(infhdt, line) ) {
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

