#include "fileholder.hpp"

#include "tools.hpp"

#include "kmer_set.hpp"

template<typename S, typename T, typename U>
fileHolder<S,T,U>::fileHolder(
                headerInfo & headerl,
                T          & fhdl
           ):
            header(    headerl ),
            fhd(       fhdl    ),
            reg_count( 0       ),
            eof(       false   ) {}


template<typename S, typename T, typename U>
ulong        fileHolder<S,T,U>::get_reg_count() {
    return reg_count;
}


template<typename S, typename T, typename U>
bool         fileHolder<S,T,U>::good() {
    return ! eof;
}


template<typename S, typename T, typename U>
S          & fileHolder<S,T,U>::curr() {
    return currValue.prev;
}


template<typename S, typename T, typename U>
fileHolder<S,T,U>::nextResult<S> & fileHolder<S,T,U>::next() {
    if ( ! eof ) {
        currValue.read( fhd );

        if ( ! currValue.res.valid ) {
            eof  = true;
            return currValue.res;
        } else {
            return currValue.res;
            ++reg_count;
        }
        
    } else {
        throw std::runtime_error("called next on a eof file");
    }
}


template<typename S, typename T, typename U>
void         fileHolder<S,T,U>::load_header() {
    decodeHeader();
}


template<typename S, typename T, typename U>
ulong        fileHolder<S,T,U>::get_num_keyframes_every() {
    //header.key_frames_every = 0;
    ulong key_frames_every = 0;
    
    if ( header.number_key_frames > 0 ) {
        if ( header.num_uniq_kmers > 0 ) {
            if ( header.num_uniq_kmers > header.number_key_frames ) {
                key_frames_every = (ulong)( header.num_uniq_kmers / header.number_key_frames );
            } else {
                key_frames_every = 0;
            }
        }
        if ( key_frames_every == 0 ) {
             key_frames_every = 0;
        }
        if ( key_frames_every == 1 ) {
            key_frames_every = 0;
        }
    }
    
    return key_frames_every;
}


template<typename S, typename T, typename U>
void         fileHolder<S,T,U>::decodeHeader() {
    
    fhd.read((char *)&header          , sizeof(header));

    std::cout << "   READING KMER SIZE       : " << header.kmer_size         << std::endl;
    std::cout << "   READING LINE NUM        : " << header.number_lines      << std::endl;
    std::cout << "   READING VALID COUNT     : " << header.num_valid_kmers   << std::endl;
    std::cout << "   READING NUM REGISTERS   : " << header.num_uniq_kmers    << std::endl;
    std::cout << "   READING NUM KEYFRAMES   : " << header.number_key_frames << std::endl;
    std::cout << "   READING KEY FRAMES EVERY: " << header.key_frames_every  << std::endl;

    ulong  key_frames_every_check = get_num_keyframes_every();
    
    if ( key_frames_every_check != header.key_frames_every ) {
        printf ("key_frames_every_check %lu key_frames_every %lu differ\n", key_frames_every_check, header.key_frames_every);
        assert(key_frames_every_check == header.key_frames_every);
    }
}


template<typename S, typename T, typename U>
void          fileHolder<S,T,U>::encodeHeader() {

    header.key_frames_every = get_num_keyframes_every();
    
    std::cout << "   SAVING KMER SIZE       : " << header.kmer_size         << std::endl;
    std::cout << "   SAVING LINE NUM        : " << header.number_lines      << std::endl;
    std::cout << "   SAVING VALID KMERS     : " << header.num_valid_kmers   << std::endl;
    std::cout << "   SAVING NUM UNIQ KMERS  : " << header.num_uniq_kmers    << std::endl;
    std::cout << "   SAVING NUM KEYFRAMES   : " << header.number_key_frames << std::endl;
    std::cout << "   SAVING KEY FRAMES EVERY: " << header.key_frames_every  << std::endl;

    fhd.write(reinterpret_cast<const char*>( &header ), sizeof(header));
}


template<typename S, typename T, typename U>
void          fileHolder<S,T,U>::read( U & q ) {
    load_header();
    
    std::cout << "    reserving " << header.num_uniq_kmers << std::endl;
    q.reserve(header.num_uniq_kmers);
    std::cout << "    loading" << std::endl;
    
    nextResult<S> result;
    while ( good() ) {
        result = next();
        
        if ( result.valid ) {
            q.insert( result.val );
        }
    }

    reg_count = currValue.reg_count_r;
}

template<typename S, typename T, typename U>
void          fileHolder<S,T,U>::write( U & q ) {
    header.num_uniq_kmers = q.size();
    
    encodeHeader();
    
    for (auto it=q.begin(); it!=q.end(); ++it) {

        currValue.set(*it);
        
#ifdef _DEBUG_
        std::cout << "num " << reg_count << " val " << *it << " prev " << prev << " diff " << cv.diff << " lenI " << cv.lenI << std::endl;
#endif
        currValue.write( fhd );
    }
    
    reg_count = currValue.reg_count_w;
    
    std::cout << "SAVED REGISTERS : " << reg_count << std::endl;

    if ( header.num_uniq_kmers != reg_count ) {
        printf ("expected %lu registers. got %lu\n", header.num_uniq_kmers, reg_count);
        assert(header.num_uniq_kmers == reg_count);
    }
}


template class fileHolder<ulong, filestream, setuLongLess>;
