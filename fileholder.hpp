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
        
    private:
        headerInfo      & header;
        T               & fhd;
        ulong             reg_count;
        S                 val;
        S                 diff;
        S                 prev;
        unsigned int      lenI;
        bool              eof;
        nextResult<S>     res;

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