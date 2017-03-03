#include "fileholder.hpp"

#include "tools.hpp"

template<typename S, typename T, typename U>
fileHolder<S,T,U>::fileHolder(
                headerInfo & headerl,
                T          & fhdl
           ):
            header(    headerl ),
            fhd(       fhdl    ),
            reg_count( 0       ),
            val(       0       ),
            diff(      0       ),
            prev(      0       ),
            lenI(      0       ),
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
    return prev;
}

template<typename S, typename T, typename U>
S          & fileHolder<S,T,U>::next() {
    if ( ! eof ) {
        if ( ! fhd.read((char *)&lenI, sizeof(lenI)) ) {
            eof = true;
        } else {
            diff = 0;
            fhd.read((char *)&diff,       lenI );

            if (( reg_count != 0 ) && (diff == 0 )) {
                printf ("zero difference. reg #%lu diff %lu\n", reg_count, diff);
                assert(diff != 0);
            }
            
            if (
                 ( header.number_key_frames > 0 ) &&
                 ( header.key_frames_every  > 0 ) &&
                 ((reg_count % header.key_frames_every) == 0)
               ){
                val  = diff;
            } else {
                val  = prev + diff;
            }
        
#ifdef _DEBUG_
            std::cout << "reg_count " << (reg_count+1) << " lenI " << lenI << " diff " << diff << " prev " << prev << " val " << val << std::endl;
#endif
            
            prev = val;
            lenI = 0;
            diff = 0;
            ++reg_count;
    
            return prev;
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
    ulong key_frames_every;
    
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
    /*
    ulong        key_frames_every       = 0;
    ulong        key_frames_everyCheck  = 0;
    
                 header.kmer_size       = 0;
                 number_lines           = 0;
                 header.number_key_frames      = 0;
    ulong        clean_check            = 0;
                 header.num_valid_kmers = 0;
    ulong        header.num_uniq_kmers         = 0;
    */
    
    /*
    infhd.read((char *)&kmer_size             , sizeof(kmer_size             ));
    infhd.read((char *)&number_lines          , sizeof(number_lines          ));
    infhd.read((char *)&clean_check           , sizeof(clean_check           ));
    infhd.read((char *)&header.num_valid_kmers, sizeof(header.num_valid_kmers));
    infhd.read((char *)&num_uniq_kmers        , sizeof(num_uniq_kmers        ));
    infhd.read((char *)&number_key_frames     , sizeof(number_key_frames     ));
    infhd.read((char *)&key_frames_everyCheck , sizeof(key_frames_everyCheck ));
    */
    
    fhd.read((char *)&header          , sizeof(header));

    ulong  key_frames_every_check = get_num_keyframes_every();
    
    assert(key_frames_every_check == header.key_frames_every);
    
    std::cout << "   READING KMER SIZE       : " << header.kmer_size         << std::endl;
    std::cout << "   READING LINE NUM        : " << header.number_lines      << std::endl;
    std::cout << "   READING VALID COUNT     : " << header.num_valid_kmers   << std::endl;
    std::cout << "   READING NUM REGISTERS   : " << header.num_uniq_kmers    << std::endl;
    std::cout << "   READING NUM KEYFRAMES   : " << header.number_key_frames << std::endl;
    std::cout << "   READING KEY FRAMES EVERY: " << header.key_frames_every  << std::endl;
}




template<typename S, typename T, typename U>
void          fileHolder<S,T,U>::encodeHeader() {
    ulong        diff           = 0;
    ulong        prev           = 0;
    unsigned int lenI           = 0;
    ulongVec     poses;

    header.key_frames_every = get_num_keyframes_every();
    
    std::cout << "   SAVING KMER SIZE       : " << header.kmer_size         << std::endl;
    std::cout << "   SAVING LINE NUM        : " << header.number_lines      << std::endl;
    std::cout << "   SAVING VALID KMERS     : " << header.num_valid_kmers   << std::endl;
    std::cout << "   SAVING NUM UNIQ KMERS  : " << header.num_uniq_kmers    << std::endl;
    std::cout << "   SAVING NUM KEYFRAMES   : " << header.number_key_frames << std::endl;
    std::cout << "   SAVING KEY FRAMES EVERY: " << header.key_frames_every  << std::endl;

    fhd.write(reinterpret_cast<const char*>( &header ), sizeof(header));

    /*
    outfhd.write(reinterpret_cast<const char*>( &kmer_size       ), sizeof(kmer_size      ));
    outfhd.write(reinterpret_cast<const char*>( &number_lines         ), sizeof(number_lines        ));
    outfhd.write(reinterpret_cast<const char*>( &clean           ), sizeof(clean          ));
    outfhd.write(reinterpret_cast<const char*>( &header.num_valid_kmers      ), sizeof(header.num_valid_kmers     ));
    outfhd.write(reinterpret_cast<const char*>( &num_uniq_kmers         ), sizeof(num_uniq_kmers        ));
    outfhd.write(reinterpret_cast<const char*>( &number_key_frames ), sizeof(number_key_frames));
    outfhd.write(reinterpret_cast<const char*>( &key_frames_every  ), sizeof(key_frames_every ));
    */
    
    /*
    for ( int i = 0; i < ((number_key_frames + 3)*sizeof(num_uniq_kmers        )); i++) {
        outfhd.write(reinterpret_cast<const char*>( &diff         ), sizeof(diff        ));    
    }
    */

    /*
    for (auto it=q.begin(); it!=q.end(); ++it) {
        printf (" v %lu\n", *it);
    }
    */
}


template<typename S, typename T, typename U>
void          fileHolder<S,T,U>::read( U q ) {
    load_header();
    
    std::cout << "    resizing" << std::endl;
    q.resize(header.num_uniq_kmers);
    std::cout << "    loading" << std::endl;
    
    while ( good() ) {
        q.insert( next() );

        //q.insert(val);
        //q[reg_count] = val;
    }
}

template<typename S, typename T, typename U>
void          fileHolder<S,T,U>::write( U q ) {
    header.num_uniq_kmers = q.size();
    
    encodeHeader();
    
    for (auto it=q.begin(); it!=q.end(); ++it) {
        if ( it == q.begin() ) {
            prev = 0;
        } else {
            if ( prev == *it ) {
                printf ("previous %lu and next %lu are the same\n", prev, *it);
                assert(prev != *it);
            }
        }

        if (
             ( header.number_key_frames > 0             ) &&
             ( header.key_frames_every  > 0             ) &&
             ((reg_count % header.key_frames_every) == 0)
           ) {
            diff = *it;
            lenI = sizeof(diff);
            //poses.push_back( fhd.tell() );
        } else {
            diff = *it - prev;
            lenI = diff == 0 ? 1 : lrint(ceil(log2(diff+1)/8.0));
            lenI = lenI == 0 ? 1 : lenI;
        }
        

#ifdef _DEBUG_
        std::cout << "num " << reg_count << " val " << *it << " prev " << prev << " diff " << diff << " lenI " << lenI << std::endl;
#endif

        fhd.write(reinterpret_cast<const char*>( &lenI ), sizeof(lenI));
        fhd.write(reinterpret_cast<const char*>(&(diff)),        lenI );
        prev = *it;
        reg_count++;
    }
    
    std::cout << "SAVED REGISTERS : " << reg_count << std::endl;

    if ( header.num_uniq_kmers != reg_count ) {
        printf ("expected %lu registers. got %lu\n", header.num_uniq_kmers, reg_count);
        assert(header.num_uniq_kmers == reg_count);
    }
}
