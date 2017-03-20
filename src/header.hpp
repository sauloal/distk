#ifndef __H_HEADER__
#define __H_HEADER__

#include <string>
#include <vector>

#include "defs.hpp"

struct headerInfo {
    int          kmer_size;
    ulong        number_lines;
    ulong        number_key_frames;
    ulong        key_frames_every;
    ulong        num_valid_kmers;
    ulong        num_uniq_kmers;
    
    headerInfo():   kmer_size(         0 ),
                    number_lines(      0 ),
                    number_key_frames( 0 ),
                    key_frames_every(  0 ),
                    num_valid_kmers(   0 ),
                    num_uniq_kmers(    0 )
                    {}
};


#endif