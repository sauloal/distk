/*
#include <boost/python.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/raw_function.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/args.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/class.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/return_internal_reference.hpp>
*/

#include "kmer_gen.hpp"

#include <iostream>
#include <algorithm>    // std::reverse
#include <sstream>
#include <iterator>
#include <stdint.h>
#include <math.h>

//using namespace std;

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
   std::cout   << "kmer_gen version: " << STRING(__KMER_GEN_VERSION__) << "\n"
               << "build date      : " << STRING(__DATE__            ) << std::endl;
}




//http://stackoverflow.com/questions/10750057/how-to-print-out-the-contents-of-a-vector
template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}


template <typename T>
std::vector<T> reversed(std::vector<T> v) {
    std::vector<T> w(v.begin(), v.end());
    std::reverse(w.begin(),w.end());
    return w;
}





kmer_gen::kmer_gen(int ks) {
    std::cout   << "initializing kmer generator with k " << ks << std::endl;

    kmer_size = ks;
    curr      = 0;
    verbose   = false;
    finished  = false;

    acs.resize(kmer_size);

    seqs_f.resize(kmer_size);
    seqs_r.resize(kmer_size);

    raws_f.resize(kmer_size);
    raws_r.resize(kmer_size);

    vals_f.resize(kmer_size);
    vals_r.resize(kmer_size);

    part_f.resize(kmer_size);
    part_r.resize(kmer_size);
}

void kmer_gen::set_verbosity(bool v) {
    verbose = v;
}


doubleVal kmer_gen::next() {
#ifdef DEBUG
        std::cout << "curr " << curr << std::endl;
#endif

        doubleVal err = { false, 0, 0 };

        if ( finished ) {
#ifdef DEBUG
            std::cout << "finished" << std::endl;
#endif
            return err;
        }

        int ac = acs[curr];
        int ad = ALPHA_LEN - ac - 1;

        if ( ac == ALPHA_LEN ) { //if last char
#ifdef DEBUG
            std::cout << "ac == ALPHA_LEN = reset curr pos and goes up" << std::endl;
#endif
            acs[curr] = 0;       // reset current position char
            curr--;              // goes to previous

            if ( curr == -1 ) {  // if previous is invalid position, quit
#ifdef DEBUG
                std::cout << "ac == ALPHA_LEN | curr == -1 = previous is invalid. quitting" << std::endl;
#endif
                finished = true;
                return err;
            } else {             // if previous is valid position
#ifdef DEBUG
                std::cout << "ac == ALPHA_LEN | curr != -1 = previous is valid. incrementing and iterating" << std::endl;
#endif
                acs[curr]++;     //  increment previous
                return next();   //  run again
            }
        }

        if ( verbose ) {
            char c = ALPHA[ac];
            char d = ALPHA[ad];

            seqs_f[ curr                 ] = c;
            seqs_r[ kmer_size - curr - 1 ] = d;

            raws_f[ curr                 ] = ac;
            raws_r[ kmer_size - curr - 1 ] = ad;
        }

        outint prev_sum_f    = 0;
        outint prev_sum_r    = 0;

        if ( curr > 0 ) {
            prev_sum_f = part_f[ curr - 1 ];
            prev_sum_r = part_r[ curr - 1 ];
        }

        outint curr_val_f    = (pow(4, (kmer_size - curr - 1)) * ac);
        outint curr_sum_f    = prev_sum_f + curr_val_f;

        outint curr_val_r    = (pow(4, (            curr    )) * ad);
        outint curr_sum_r    = prev_sum_r + curr_val_r;

        if ( verbose ) {
            vals_f[curr] = curr_val_f;
            vals_r[curr] = curr_val_r;
        }

        part_f[curr] = curr_sum_f;
        part_r[curr] = curr_sum_r;

        if ( verbose ) {
            std::cout << " prev_sum_f " << prev_sum_f << " curr_val_f " << curr_val_f << " curr_sum_f " << curr_sum_f << " prev_sum_r " << prev_sum_r << " curr_val_r " << curr_val_r << " curr_sum_r " << curr_sum_r << std::endl;

            if ( curr == (kmer_size - 1) ) {
                std::cout << " curr  " << curr                           << std::endl;
                std::cout << " seqs F" <<          seqs_f  << "SUM"      << std::endl;
                std::cout << " raws F" <<          raws_f                << std::endl;
                std::cout << " vals F" <<          vals_f                << std::endl;
                std::cout << " part F" <<          part_f  << curr_sum_f << std::endl;
                std::cout                                                << std::endl;
                std::cout << " seqs R" <<          seqs_r  << "SUM"      << std::endl;
                std::cout << " raws R" <<          raws_r                << std::endl;
                std::cout << " vals R" << reversed(vals_r)               << std::endl;
                std::cout << " part R" << reversed(part_r) << curr_sum_r << std::endl;
                std::cout << std::endl;
            }
        }

        if ( curr == (kmer_size - 1) ) { //last position
#ifdef DEBUG
            std::cout << "curr == (kmer_size - 1) = incrementing and returning" << std::endl;
#endif
            acs[curr]++;     //  increment current

            if ( curr_sum_f <= curr_sum_r ) {
#ifdef DEBUG
                std::cout << "curr == (kmer_size - 1) | curr_sum_f <= curr_sum_r = returning" << std::endl;
#endif
                return {true, curr_sum_f, curr_sum_r};
            } else {
#ifdef DEBUG
                std::cout << "curr == (kmer_size - 1) | curr_sum_r <  curr_sum_f = returning" << std::endl;
#endif
                return {true, curr_sum_f, curr_sum_r};
            }

        } else {           //not last position
#ifdef DEBUG
            std::cout << "curr != (kmer_size - 1) = advancing and iterating" << std::endl;
#endif
            curr++;        //advance cursor
            return next(); //iterate
        }
}






//http://www.linuxquestions.org/questions/programming-9/mmap-tutorial-c-c-511265/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include <byteswap.h>

/*
//http://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
#include <chrono>
*/

//http://man7.org/linux/man-pages/man2/mmap.2.html
//#define MAP_HUGE_1GB    (30 << MAP_HUGE_SHIFT)

#include "progressbar.hpp"

int kmer_gen_m(int ks) {
    kmer_gen kg(ks);

    int    i;
    int    fd;
    outint  result;
    outint *map;  /* mmapped array of int's */

    outint  max_i     = pow(4, ks);
    outint  filesize  = max_i * sizeof(outint);

    std::string filepath = "key_";
    filepath += std::to_string(ks);
    filepath += ".key";

    std::cout << "filename " << filepath << " size " << filesize << " max_i " << max_i << std::endl;

    progressBar progress("filepath", 0, max_i);

    /* Open a file for writing.
     *  - Creating the file if it doesn't exist.
     *  - Truncating it to 0 size if it already exists. (not really needed)
     *
     * Note: "O_WRONLY" mode is not sufficient when mmaping.
     */
    fd = open(filepath.c_str(), O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1) {
    perror("Error opening file for writing");
    exit(EXIT_FAILURE);
    }

    /* Stretch the file size to the size of the (mmapped) array of ints
     */
    result = lseek(fd, filesize-1, SEEK_SET);
    if (result == -1) {
    close(fd);
    perror("Error calling lseek() to 'stretch' the file");
    exit(EXIT_FAILURE);
    }

    /* Something needs to be written at the end of the file to
     * have the file actually have the new size.
     * Just writing an empty string at the current file position will do.
     *
     * Note:
     *  - The current position in the file is at the end of the stretched
     *    file due to the call to lseek().
     *  - An empty string is actually a single '\0' character, so a zero-byte
     *    will be written at the last byte of the file.
     */
    result = write(fd, "", 1);
    if (result != 1) {
    close(fd);
    perror("Error writing last byte of the file");
    exit(EXIT_FAILURE);
    }

    /* Now the file is ready to be mmapped.
     */
    //map = (outint*)mmap(0, filesize, PROT_READ | PROT_WRITE | MAP_HUGETLB | MAP_HUGE_1GB, MAP_SHARED, fd, 0);
    map = (outint*)mmap(0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
    close(fd);
    perror("Error mmapping the W file");
    exit(EXIT_FAILURE);
    }

    /* Now write int's to the file as if it were memory (an array of ints).
     */
    /*
    for (i = 1; i <=NUMINTS; ++i) {
    map[i] = 2 * i;
    }
    */
    /*
    auto  begin = std::chrono::steady_clock::now();
    auto  curr  = std::chrono::steady_clock::now();
    outint ela   = 1;
    outint eta   = 0;
    outint speed = 0;
    */
    ulong     I = 0;
    ulong     J = 0;
    ulong     K = 0;
    outint    m = 0;
    doubleVal v = kg.next();
    while (v.valid) {
        //std::cout << "I " << I << " J " << J << " FWD " << v.fwd << " REV " << v.rev << std::endl;

        if ( v.fwd <= v.rev ) {
            //mapW[I] = bswap_64(J); //little endian
            map[I] = J; //little endian
            J++;
        } else {
            K = map[v.rev];
            map[I] = K;
        }

        if ( (I != 0) && (I % 5000000 == 0) ) {
            progress.print( I );
            /*
            curr  = std::chrono::steady_clock::now();
            ela   = std::chrono::duration_cast<std::chrono::seconds>(curr - begin).count();
            speed = I / ela;
            eta   = (max_i - I) / speed;
            std::cout << "I " << I << " ela " << ela << " speed " << speed << " eta " << eta << std::endl;
            */
            //std::cout << "I " << I << " ela " << ela << " speed " << speed << std::endl;
            //std::cout << "I " << I << " ela " << ela << std::endl;
        }

        I++;
        v = kg.next();
    }

    std::cout << "MAX I " << I << " MAX J " << J << " LAST VAL " << map[I-1] << std::endl;

    /* Don't forget to free the mmapped memory
     */
    if (munmap(map, filesize) == -1) {
    perror("Error un-mmapping the W file");
    /* Decide here whether to close(fd) and exit() or not. Depends... */
    }

    /* Un-mmaping doesn't close the file, so we still need to do that.
     */
    std::cout << "CLOSING" << std::endl;
    close(fd);
    return 0;
}

#include <fstream>

int kmer_gen_f(int ks) {
    int    i;
    int    fd;
    outint  result;
    outint *map;  /* mmapped array of int's */

    outint  max_i     = pow(4, ks);
    outint  filesize  = max_i * sizeof(outint);

    std::string filepath = "key_";
    filepath += std::to_string(ks);
    filepath += ".key";

    std::cout << "filename " << filepath << " size " << filesize << " max_i " << max_i << std::endl;

    progressBar progress(filepath, 0, max_i);

    /* Open a file for writing.
     *  - Creating the file if it doesn't exist.
     *  - Truncating it to 0 size if it already exists. (not really needed)
     *
     * Note: "O_WRONLY" mode is not sufficient when mmaping.
     */
    /*
    fd = open(filepath.c_str(), O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1) {
    perror("Error opening file for writing");
    exit(EXIT_FAILURE);
    }
    */
    fstream myFile (filepath, ios::out | ios::binary);

    /* Stretch the file size to the size of the (mmapped) array of ints
     */
    /*
    result = lseek(fd, filesize-1, SEEK_SET);
    if (result == -1) {
    close(fd);
    perror("Error calling lseek() to 'stretch' the file");
    exit(EXIT_FAILURE);
    }
    */
    myFile.seekg(filesize-1);

    /* Something needs to be written at the end of the file to
     * have the file actually have the new size.
     * Just writing an empty string at the current file position will do.
     *
     * Note:
     *  - The current position in the file is at the end of the stretched
     *    file due to the call to lseek().
     *  - An empty string is actually a single '\0' character, so a zero-byte
     *    will be written at the last byte of the file.
     */
    /*
    result = write(fd, "", 1);
    if (result != 1) {
    close(fd);
    perror("Error writing last byte of the file");
    exit(EXIT_FAILURE);
    }
    */
    char x = '\0';
    myFile.write((char*)&x, sizeof(x));
    myFile.seekg (0);


    kmer_gen kg(ks);

    doubleVal m = kg.next();
    outint    o = 0;
    ulong     I = 0;

    while (m.valid) {
        if ( m.fwd <= m.rev ) {
            o = m.fwd;
        } else {
            o = m.rev;
        }

        myFile.write((char*)reinterpret_cast<const char *>(&o), sizeof(o));

        if ( (I != 0) && (I % 5000000 == 0) ) {
            progress.print( I );
        }
        I++;
        m = kg.next();
    }

    /* Un-mmaping doesn't close the file, so we still need to do that.
     */
    std::cout << "CLOSING" << std::endl;
    close(fd);
    return 0;
}
