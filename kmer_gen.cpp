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

kmer_gen::kmer_gen(int ks) {
    std::cout   << "initializing kmer generator with k" << ks << std::endl;

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

long kmer_gen::next() {
#ifdef DEBUG
        std::cout << "curr " << curr << std::endl;
#endif

        if ( finished ) {
#ifdef DEBUG
            std::cout << "finished" << std::endl;
#endif
            return -1;
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
                return -1;
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

        ulong prev_sum_f    = 0;
        ulong prev_sum_r    = 0;

        if ( curr > 0 ) {
            prev_sum_f = part_f[ curr - 1 ];
            prev_sum_r = part_r[ curr - 1 ];
        }

        ulong curr_val_f    = (pow(4, (kmer_size - curr - 1)) * ac);
        ulong curr_sum_f    = prev_sum_f + curr_val_f;

        ulong curr_val_r    = (pow(4, (            curr    )) * ad);
        ulong curr_sum_r    = prev_sum_r + curr_val_r;

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
                return curr_sum_f;
            } else {
#ifdef DEBUG
                std::cout << "curr == (kmer_size - 1) | curr_sum_r <  curr_sum_f = returning" << std::endl;
#endif
                return curr_sum_r;
            }

        } else {           //not last position
#ifdef DEBUG
            std::cout << "curr != (kmer_size - 1) = advancing and iterating" << std::endl;
#endif
            curr++;        //advance cursor
            return next(); //iterate
        }
}



/*
BOOST_PYTHON_MODULE(kmer_gen)
{
    boost::python::class_<kmer_gen>("kmer_gen")
        //.def( "merge_jfs", &kmer_gen::merge_jfs )
        //.def( "merge_dbs", &kmer_gen::merge_dbs )
    ;
}

*/
