#include "kmer_set.hpp"

#include "tools.hpp"

//http://www.linuxquestions.org/questions/programming-9/mmap-tutorial-c-c-511265/

#include <sys/stat.h>



int fact (int n) {
    if (n < 0){
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    else {
        return n * fact(n-1);
    }
}


//http://stackoverflow.com/questions/1204202/is-it-possible-to-print-a-preprocessor-variable-in-c
#define STRING2(x) #x
#define STRING(x) STRING2(x)
void version () {
    std::cout << "version     : " << STRING(__PROG_VERSION__) << "\n"
              << "build date  : " << STRING(__COMPILE_DATE__) << std::endl;

#ifdef _DEBUG_
    std::cout << "COMPILE FLAG: _DEBUG_" << std::endl;
#endif

#ifdef _PRINT_LINE_LENGTHS_
    std::cout << "COMPILE FLAG: _PRINT_LINE_LENGTHS_" << std::endl;
#endif

#ifdef _NO_DIFF_ENCODING_
    std::cout << "COMPILE FLAG: _NO_DIFF_ENCODING_" << std::endl;
#endif

#ifdef _ALTERNATIVE_ALLOC_
    std::cout << "COMPILE FLAG: _ALTERNATIVE_ALLOC_" << std::endl;
#endif
}




extract_kmers::extract_kmers(): clean(0) {
    init1();
}

extract_kmers::extract_kmers( const int ks ): clean(0) {
    std::cout << " KMER SIZE: " << ks << std::endl;
    init1();
    init2(ks);
}

void extract_kmers::init1() {
    //kmer_size(0), number_lines(0), header.number_key_frames(100), clean(0), header.num_valid_kmers(0)
    
    for ( int i = 0; i < 256; i++ ) {
        dictF[i] = 78;
    }

    dictF['a'] = 0;
    dictF['A'] = 0;
    dictF['c'] = 1;
    dictF['C'] = 1;
    dictF['g'] = 2;
    dictF['G'] = 2;
    dictF['t'] = 3;
    dictF['T'] = 3;
}

void extract_kmers::init2(const int ks) {
    //kmer_size(ks), number_lines(0), header.number_key_frames(100), clean(0), header.num_valid_kmers(0)
    
    header.kmer_size = ks;
    
    init3();
}

void extract_kmers::init3() {
    for ( int pos = 0; pos < header.kmer_size; pos++ ) {
        ulong ind = (header.kmer_size-pos-1);
        pows[pos] = std::pow(4, ind);
    }

    //cleans first two bits
    clean        = ((ulong)(pow(2, ((header.kmer_size-1)*2)))-1);

    std::cout << "clean " << clean << std::endl;
    
    progressRead = progressBar("reading");
    progressRead.setProgress( false );
    
    progressKmer = progressBar("adding ", 0, get_max_size()/2);
    //progressKmer.setProgress( false );
    progressKmer.setTwoLines( false );
    progressKmer.setShowSecs( false );
}

/*
extract_kmers::~extract_kmers() {
    //q.clear();
}
*/

ulong         extract_kmers::get_max_size() {
    return pow(4, header.kmer_size);
}

void          extract_kmers::reserve() {
    q.reserve(get_max_size() / 4);
}

ulong         extract_kmers::size() {
    return q.size();
}

void          extract_kmers::print_all() {
    for (auto it=q.begin(); it!=q.end(); ++it) {
        std::cout << ' ' << *it;
        std::cout << '\n';
    }
}

void          extract_kmers::read_one_liner(          const string    &infile  ) {
    filestream infhd(infile, 'r');
    read_one_liner( infile, infhd );
    infhd.close();
}

template<typename T>
void          extract_kmers::read_one_liner(          const string   & infile, T & infhd  ) {
    if (!infhd) {
        perror((string("Error opening input file: ") + infile).c_str());
#ifdef __CHEERP__
        assert(false);
#else
        throw std::runtime_error("error opening input file: " + infile);
#endif
        //return;
    }

    if(!infhd.good()) {
        perror((string("Error reading input file: ") + infile).c_str());
#ifdef __CHEERP__
        assert(false);
#else
        throw std::runtime_error("error opening input file: " + infile);
#endif
        //return;

    } else {
        reserve();

        string line;

        while (infhd.get_line(line)) {
            //std::cout << "Got line" << std::endl;
#pragma omp task firstprivate(line)
            parse_line(line);
#pragma omp taskwait
        }//while (getline(infhd,line)) {

        std::cout << "TOTAL: " <<  size() << std::endl;

#ifdef _DEBUG_
        print_all();
#endif
    }
}

void          extract_kmers::read_fasta(              const string   & infile  ) {
    /*
     * TODO: IMPLEMENT + GZ VERSION
     */
    reserve();
    std::ifstream infhd(infile);
    infhd.close();
}

void          extract_kmers::read_fastq(              const string   & infile  ) {
    /*
     * TODO: IMPLEMENT + GZ VERSION
     */
    reserve();
    std::ifstream infhd(infile);
    infhd.close();
}

void          extract_kmers::parse_line(                    string   & line    ) {
    ulong ll         = line.length();

#ifdef _DEBUG_
    if ( ll <= 100 ) {
        std::cout << "Line: " << line << std::endl;
    }
#endif

    ulong resF       = 0;
    ulong resR       = 0;
    ulong resM       = 0;

    ulong kcF        = 0;
    ulong pvF        = 0;
    ulong cvF        = 0;

    ulong kcR        = 0;
    ulong pvR        = 0;
    ulong cvR        = 0;

    ulong tainted    = 0;
    bool  valid      = false;

    char  c;
    int   vF;

    if ( ll >= header.kmer_size ) {
        /*
         * TODO: Add mutex
         */
        header.number_lines          += 1;

#ifdef _PRINT_LINE_LENGTHS_
        std::cout << " Line :: Length: " << ll << " Num: " << header.number_lines;
#endif


#ifdef _PRINT_LINE_LENGTHS_
        std::cout << " Line Loaded" << std::endl;
#endif

        for ( long i = 0; i < ll; i++ ) {
            c        = line[i];
            vF       = dictF[c];
            line[i]  = vF;

#ifdef _DEBUG_
            std::cout << "i " << i << " c " << c << " (" << (int)c << ") "<< " vF " << vF << std::endl;
#endif

            if ( vF == 78 ) {
                valid = false;

#ifdef _DEBUG_
                if ( line.length() <= 100 ) {
                    std::cout << " BAD"                          << std::endl;
                    //std::cout << "  VALS  :           " << valsF << std::endl;
                }
#endif
                long js = i - header.kmer_size + 1;
                long je = i + header.kmer_size;

                if ( js <  0  ) { js =  0; }
                if ( js >= ll ) { js =  0; }
                if ( je >= ll ) { je = ll; }

#ifdef _DEBUG_
                std::cout << "   js " << js << " je " << je << std::endl;
#endif

                tainted = je;
            }//if ( vF == 78 ) {


            if ( i < ( header.kmer_size-1 ) ) {
                valid = false;
#ifdef _DEBUG_
                std::cout << " seq too small  : " << i << " <  " << (header.kmer_size-1) << std::endl;
#endif
            } else {
#ifdef _DEBUG_
                std::cout << " seq long enough: " << i << " >= " << (header.kmer_size-1) << std::endl;
#endif
                bool valF = (i < tainted);

                if ( valF ) {
                    valid = false;
#ifdef _DEBUG_
                    std::cout << "  position not valid. i: " << i << " tainted: " << tainted << std::endl;
#endif

                } else {
#ifdef _DEBUG_
                    std::cout << "  position valid" << std::endl;
#endif

                    if ( valid ) {
#ifdef _DEBUG_
                        std::cout << " VALID :: B :: resF: " << resF << " resR: " << resR << std::endl;
#endif //_DEBUG_

                        resF &= clean;
                            //resR &= clean;

#ifdef _DEBUG_
                        std::cout << " VALID :: & :: resF: " << resF << " resR: " << resR << std::endl;
#endif //_DEBUG_

                        resF = ( resF << 2 );
                        resR = ( resR >> 2 );

#ifdef _DEBUG_
                        std::cout << " VALID :: S :: resF: " << resF << " resR: " << resR << std::endl;
#endif //_DEBUG_

                        resF += (    vF                       );
                        resR += ( (3-vF) << ((header.kmer_size-1)*2) );

#ifdef _DEBUG_
                        std::cout << " VALID :: R :: resF: " << resF << " resR: " << resR << std::endl;
#endif //_DEBUG_

                    } else {
                        valid = true;

                        auto p_begin = line.begin() + (i - header.kmer_size + 1);

                        resF = 0;
                        resR = 0;
                        resM = 0;

                        kcF  = 0;
                        pvF  = 0;
                        cvF  = 0;

                        kcR  = 0;
                        pvR  = 0;
                        cvR  = 0;

                        for ( unsigned long pos = 0; pos < header.kmer_size; pos++ ) {
                            auto a_pos = p_begin + pos;

                            kcF   = *a_pos;
                            kcR   = 3 - kcF;

                            cvF   = (kcF << ((header.kmer_size - pos - 1)*2));
                            cvR   = (kcR << (                    pos     *2));

#ifdef _DEBUG_
                            std::cout << "  I: "     << i    << " POS : "   << (pos+1)
                                      << " VALID: "  << valF
                                      << " SUM BF: " << resF << " SUM BR: " << resR
                                      << " KCF: "    << kcF  << " KCR: "    << kcR
                                      << " VALF: "   << cvF  << " VALR: "   << cvR
                                      << " PVF: "    << pvF  << " PVR: "    << pvR;
#endif

                            resF += cvF;
                            resR += cvR;

#ifdef _DEBUG_
                            std::cout << " SUM AF: " << resF << " SUM AR: " << resR << std::endl;
#endif
                        } //for ( unsigned int pos = 0; pos < header.kmer_size; pos++ ) {
                    } // else if ( valid ) {

                    resM = ( resF <= resR ) ? resF : resR;
          
                    //std::cout << " INSERTING" << std::endl;
                    ScopedLock lck(lock);
#pragma omp critical(dbupdate)
                    q.insert(resM);
                    lck.Unlock();
                    //std::cout << " INSERTED" << std::endl;

                    
                    ++header.num_valid_kmers;
                    if (get_max_size() > 100) {
                        if ( ( header.num_valid_kmers % 100000 ) == 0 ) {
                            //std::cout << "  ADDED: " << header.num_valid_kmers << " FROM WHICH " << q.size() << " WERE UNIQUE FROM THE MAXIMUM HYPOTETICAL " << get_max_size() << std::endl;
                            progressRead.print( header.num_valid_kmers );
                            progressKmer.print( q.size()   );
                            std::cout << std::endl;
                        }
                    }
                    
#ifdef _DEBUG_
                    std::cout << "  RESF: " << resF  << " RESR  : " << resR << " RESM : " << resM << "\n" << std::endl;
#endif
                }// if ( valF == 0 ) {
            }//if ( i >= header.kmer_size ) {
        }//for (ulong i = 0; i < ll; i++) {
    }//if ( line.length() >= header.kmer_size ) {
}

void          extract_kmers::save_kmer_db(            const string   & outfile ) {
    if ( size() == 0 ) {
        std::cout << "NO KMER TO SAVE" << std::endl;

    } else {
        std::cout << "SAVING TO: " << outfile << " REGISTERS: " << size() << " FILE SIZE: " << (size()*sizeof(ulong)) << std::endl;

        //https://stackoverflow.com/questions/12372531/reading-and-writing-a-stdvector-into-a-file-correctly

        string  outfileT = outfile + ".tmp";

        remove_if_exists(outfile );
        remove_if_exists(outfileT);

        filestream outfhd(outfileT, 'w', 'z');
        
        if (!outfhd) {
            perror((string("error saving kmer file: ") + outfile).c_str());
#ifdef __CHEERP__
            assert(false);
#else
            throw std::runtime_error("error saving kmer file: " + outfile);
#endif
            //return;
        }

        //std::copy(q.begin(), q.end(), std::ostreambuf_iterator<ulong>(outfhd));
        //outfhd.write(reinterpret_cast<const char*>(&q.begin()), q.size()*sizeof(ulong));
        header.num_uniq_kmers = 0;

        encoder(outfhd);

        outfhd.close();

        rename_and_check( outfileT, outfile );

        std::cout << "SAVED" << std::endl;

#ifdef _DEBUG_
        //read_kmer_db(outfile);
#endif
    }
}

ulong         extract_kmers::get_db_file_size(        const string   & infile  ) {
    //https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c
    struct stat stat_buf;
    int rc = stat(infile.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
    
}

void          extract_kmers::read_kmer_db(            const string   & infile  ) {
    /*
     * TODO: load into q
     *       read delta format
     */

    std::cout << "  READING BACK FROM: " << infile << std::endl;

    filestream infhd(infile, 'r', 'z');
    
    std::cout << "   OPEN" << std::endl;

    ulong fileSize = get_db_file_size(infile);

    std::cout << "    SIZE: " << fileSize << std::endl;

    std::cout << "   CLEARING" << std::endl;

    q.clear();

    std::cout << "   READING" << std::endl;

    decoder(infhd);

    std::cout << "   CLOSING" << std::endl;

    infhd.close();

    std::cout << "   READ" << std::endl;

    std::cout << "    NUM REGISTERS: " << size() << std::endl;

    std::cout << "   DONE" << std::endl;
}

template<typename T>
void          extract_kmers::encoder(                       T        & outfhd  ) {
    /*
     * Implement roling difference encoding
     *       <int8>[<char>,n]
     *       '     '--> Diff from prev to current using the minimum number of chars
     *       '--------> Number of chars
     * 1    1    1 <1,1>
     * 2    1    1 <1,1>
     * 3    1    1 <1,1>
     * 5    1    2 <1,1>
     * 10   1    5 <1,1>
     * 200  2  190 <2,12,7>  [ 190 as 2 chars]
     * 2000 3 1800 <3,7,0,8> [1800 as 3 chars]
     *
     * check minimum number of bits as n
     * save n
     * cast ulong to n chars
     * save chars
     *
     * read 1 char
     * read n chars
     * cast n chars to ulong
     *
     * Keyframes are added so that no prior information is needed,
     * this way allowing for parallelization. the position of the
     * keyframes is deterministic but their physical location is not *yet*
     *
     * TODO: create deterministic position for keyframes. meybe by storing
     * the values in the header.
     */
#ifdef _NO_DIFF_ENCODING_
    for (auto it=q.begin(); it!=q.end(); ++it) {
        outfhd.write(reinterpret_cast<const char*>(&(*it)), sizeof(ulong));
        header.num_uniq_kmers += 1;
    }
#else //#ifdef _NO_DIFF_ENCODING_
    std::cout << "  SAVING" << std::endl;

    fileHolder<ulong, T, setuLongLess> lh(header, outfhd);

    lh.write(q);
    
#endif //#ifdef _NO_DIFF_ENCODING_
}

template<typename T>
void          extract_kmers::decoder(                       T        & infhd   ) {
#ifdef _NO_DIFF_ENCODING_
    ulong header.num_uniq_kmers = 0;
    ulong buffer;

    while(infhd.read((char *)&buffer,sizeof(buffer)))
    {
        q.insert(buffer);
        header.num_uniq_kmers++;
    }

    if ( header.num_uniq_kmers != size() ) {
        printf ("expected %lu registers. got %lu\n", header.num_uniq_kmers, size());
        assert(num_uniq_kmers == size());
    }
#else // #ifdef _NO_DIFF_ENCODING_    
    //https://stackoverflow.com/questions/15138353/reading-the-binary-file-into-the-vector-of-unsigned-chars
    fileHolder<ulong, T, setuLongLess> lh(header, infhd);

    lh.read(q);
    
    /*
    lh.load_header();
    
    init2(kmer_size);    
    
    std::cout << "    resizing" << std::endl;
    q.resize(header.num_uniq_kmers);
    std::cout << "    loading" << std::endl;

    
    while ( lh.good() ) {
        q.insert( lh.next() );

        //q.insert(val);
        //q[reg_count] = val;
    }
    */

    init3();    
        
    std::cout << "READ " << lh.get_reg_count() << " REGISTERS" << std::endl;

    if ( header.num_uniq_kmers != lh.get_reg_count() ) {
        printf ("expected %lu registers. got %lu\n", header.num_uniq_kmers, lh.get_reg_count());
        assert( header.num_uniq_kmers == lh.get_reg_count() );
    }

    if ( header.num_uniq_kmers != size() ) {
        printf ("expected %lu registers. inserted %lu\n", header.num_uniq_kmers, size());
        assert( header.num_uniq_kmers == size() );
    }
#endif //#ifdef _NO_DIFF_ENCODING_
}

ulongVec      extract_kmers::get_kmer_db() {
    /*
     * TODO: return q
     */
    //return ulongVec(q.begin(), q.end());
    return q.get_container();
}

ulong         extract_kmers::get_number_key_frames()                             { return header.number_key_frames; }

void          extract_kmers::set_number_key_frames(   const ulong kf           ) { header.number_key_frames = kf;   }






/*
ulong         extract_kmers::get_db_num_registers(    const string   & infile  ) {
    header.num_uniq_kmers = 0;

#ifdef _NO_DIFF_ENCODING_

    ulong fileSize = get_db_file_size(infile);
    header.num_uniq_kmers        = fileSize / sizeof(ulong);

#else

    filestream infhd(infile, 'r', 'z');

    if (!infhd.good()) {
        perror((string("error reading input file: ") + infile).c_str());
#ifdef __CHEERP__
        assert(false);
#else
        throw std::runtime_error("error reading input file: " + infile);
#endif
        //return;
    }

    header.num_uniq_kmers = get_db_num_registers(infhd);

    infhd.close();

#endif

    return header.num_uniq_kmers;
}

/*
template<typename T>
ulong         extract_kmers::get_db_num_registers(          T        & infhd   ) {
    header.num_uniq_kmers  = 0;

#ifdef _NO_DIFF_ENCODING_

    ulong fileSize = get_db_file_size(infhd);
    header.num_uniq_kmers        = fileSize / sizeof(ulong);

#else

    ulong startPos = infhd.tell();

    infhd.read((char *)&header.num_uniq_kmers,sizeof(header.num_uniq_kmers));

    infhd.seek(startPos, std::ios::beg);

#endif

    return header.num_uniq_kmers;
}
*/



