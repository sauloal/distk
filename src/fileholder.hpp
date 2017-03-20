#ifndef __H_FILEHOLDER__
#define __H_FILEHOLDER__

#include <stdexcept>
#include <assert.h>
#include <iostream>

#include "defs.hpp"

#include "header.hpp"



template<typename S, typename T, typename U>
class fileHolder {
    public:
        template<typename V>
        struct nextResult {
            bool valid;
            V    val;
        };
        
        typedef nextResult<S> nextResult_t;
        
    private:
        struct currVal{
            S                 diff;
            S                 prev;
            unsigned int      lenI;
            size_t            reg_count_r;
            size_t            reg_count_w;
            nextResult<S>     res;
            
            currVal(): diff(0), prev(0), lenI(0), reg_count_r(0), reg_count_w(0), res({false, 0}) {}
            currVal(const S &val) {
                set(val);
            }
            void set(const S &val) {
                if ( reg_count_w == 0 ) {
                    diff = val;
                    lenI = sizeof(diff);
                } else {
                    if ( prev == val ) {
                        printf ("previous %lu and next %lu are the same\n", prev, val);
                        assert(prev != val);
                    } else {
                        diff = val - prev;
                        lenI = diff == 0 ? 1 : lrint(ceil(log2(diff+1)/8.0));
                        lenI = lenI == 0 ? 1 : lenI;
                    }
                }
                ++reg_count_w;
            }
            void write( T & fhd ) {
                fhd.write(reinterpret_cast<const char*>(& lenI ), sizeof(lenI));
                fhd.write(reinterpret_cast<const char*>(&(diff)),        lenI );
            }
            void read( T & fhd ) {
                if ( ! fhd.read((char *)&lenI, sizeof(lenI)) ) {
                    res  = {false, 0};
                
                } else {
                    diff = 0;
                    fhd.read((char *)&diff,       lenI );
                    prev += diff;
                    lenI = 0;
                    diff = 0;
                    ++reg_count_r;
            
                    res = {true, prev};
                }
            }
        };

        headerInfo      & header;
        T               & fhd;
        ulong             reg_count;
        bool              eof;
        currVal           currValue;

        ulong             get_num_keyframes_every();
        void              decodeHeader();
        void              encodeHeader();

    public:
        fileHolder(headerInfo & headerl, T & fhdl);
        bool            good();
        S             & curr();
        nextResult<S> & next();
        void            load_header();
        void            write( U & q );
        void            read(  U & q );
        ulong           get_reg_count();
};


#endif