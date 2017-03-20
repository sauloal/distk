#include "merger.hpp"
#include "tools.hpp"

#include <iostream>
#include <fstream>
#include <cstring>

              merge_kmers::merge_kmers( const strVec    & infilesl ): infiles(infilesl) { merge(); }

void          merge_kmers::get_matrix(        ulongVec  & matl     ) { matl = mat; };

ulongVec    & merge_kmers::get_matrix()                              { return mat; };

void          merge_kmers::read_matrix( const string    & prefix   ) {
    //TODO: IMPLEMENT
}

void          merge_kmers::merge() {
    /*
     * TODO: read q
     */
/*
    extract_kmers v1(kmer_size);
    extract_kmers v2(kmer_size);

    auto size = infiles.size();

    std::cout << "# files " << size << " " << infiles << std::endl;

    mat.resize(size * size);

#pragma omp parallel for
    for( strVec::size_type i = 0; i < size; i++ ) {
        auto file1  = infiles[i];

        v1.read_kmer_db( file1 );

        std::cout << "I " << i << " (" << file1 << ") [" << v1.size() << "]" << std::endl;

        mat[((i * size) + i)] = v1.size();

        for( strVec::size_type j = i+1; j < size; j++ ) {
            auto pos1 = ( i * size ) + j;
            auto pos2 = ( j * size ) + i;
*/
            /*
             *00 01 02 03
             *04 05 06 07
             *08 09 10 11
             *12 13 14 15
             *
             *   01 02 03
             *      06 07
             *         11
             *
             *
             *04
             *08 09
             *12 13 14
             *
             *00
             *   05
             *      10
             *         15
             */
/*
            auto file2 = infiles[j];

            v2.read_kmer_db( file2 );

            std::cout << "  J " << j << " (" << file2 << ") [" << v2.size() << "] - " << pos1 << ":" << pos2 << " CALCULATING" << std::endl;

            size_t count = intersection_size( v1.get_kmer_db(), v2.get_kmer_db() );

            std::cout << "   COUNT " << count << std::endl;
*/
            /*
            ScopedLock lck(lock);
#pragma omp critical(matrixupdate)
            {
                mat[pos1] = count;
                mat[pos2] = count;
            }
            lck.Unlock();
            */
/*
        }
    }
*/
}


void          merge_kmers::save_matrix( const string    & prefix   ) {
    if ( mat.size() > 0 ) {
        std::cout << "SAVING TO: " << prefix << ".prefix SIZE " << (mat.size()*sizeof(ulong)) << std::endl;

        string matrix  = prefix + string(".matrix");
        string index   = prefix + string(".index" );
        string matrixT = matrix + string(".tmp");
        string indexT  = index  + string(".tmp" );

        remove_if_exists(matrix );
        remove_if_exists(matrixT);
        remove_if_exists(index  );
        remove_if_exists(indexT );

        //https://stackoverflow.com/questions/12372531/reading-and-writing-a-stdvector-into-a-file-correctly
        std::ofstream outfhd(matrixT, std::ios::out | std::ofstream::binary);

        if (!outfhd) {
            perror((string("error saving matrix file: ") + matrix).c_str());
#ifdef __CHEERP__
            assert(false);
#else
            throw std::runtime_error("error saving matrix file: " + matrix);
#endif
            //return;
        }

        //std::copy(q.begin(), q.end(), std::ostreambuf_iterator<ulong>(outfhd));
        //outfhd.write(reinterpret_cast<const char*>(&q.begin()), q.size()*sizeof(ulong));
        for (auto it=mat.begin(); it!=mat.end(); ++it) {
            outfhd.write(reinterpret_cast<const char*>(&(*it)), sizeof(ulong));
        }
        outfhd.close();



        std::ofstream outind(indexT, std::ios::out | std::ofstream::binary);

        if (!outind) {
            perror((string("error saving index file: ") + index).c_str());
#ifdef __CHEERP__
            assert(false);
#else
            throw std::runtime_error("error saving index file: " + index);
#endif
            //return;
        }

        ulong c = 0;
        char* nl = new char[1];
        nl[0] = '\n';
        for (auto it=infiles.begin(); it!=infiles.end(); ++it) {
            auto n = (*it).c_str();
            std::cout << n << " " << strlen(n) << std::endl;
            if ( c > 0 ) {
                outind.write(nl, 1);
            }
            outind.write(reinterpret_cast<const char*>(n), strlen(n));
            c++;
        }

        outind.close();

        rename_and_check( indexT , index  );
        rename_and_check( matrixT, matrix );
    } else {
        std::cout << "NO MATRIX TO SAVE" << std::endl;
    }
}

/*
http://en.cppreference.com/w/cpp/algorithm/set_symmetric_difference
http://en.cppreference.com/w/cpp/algorithm/set_difference
http://en.cppreference.com/w/cpp/algorithm/set_intersection
http://en.cppreference.com/w/cpp/algorithm/set_union
*/
