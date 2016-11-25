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

    seqs_f.resize(kmer_size);
    seqs_r.resize(kmer_size);

    raws_f.resize(kmer_size);
    raws_r.resize(kmer_size);

    vals_f.resize(kmer_size);
    vals_r.resize(kmer_size);

    part_f.resize(kmer_size);
    part_r.resize(kmer_size);
}

/*
int kmer_gen(int kmer_size, int curr, seqs=None, raws=None, vals=None, part=None, verbose=False):
    #print "kmer_gen", kmer_size, curr, seqs, vals, part

    if curr is None:
        #print "curr is None\n"
        curr = 0

        if verbose:
            seqs = [[None, None] for x in xrange(kmer_size)]
            raws = [[None, None] for x in xrange(kmer_size)]
            vals = [[None, None] for x in xrange(kmer_size)]

        part = [[None, None] for x in xrange(kmer_size)]

    for ac in xrange(len(ALPHA)):
        #print "curr {} c {}".format(curr, c),
        ad = 3 - ac

        if verbose:
            c = ALPHA[ac]
            d = ALPHA[ad]

            seqs[ curr                 ][0] = c
            seqs[ kmer_size - curr - 1 ][1] = d

            raws[ curr                 ][0] = ac
            raws[ kmer_size - curr - 1 ][1] = ad

        prev_sum_f    = 0
        prev_sum_r    = 0

        if curr > 0:
            prev_sum_f = part[ curr - 1 ][0]
            prev_sum_r = part[ curr - 1 ][1]

        curr_val_f    = ((4 ** (kmer_size - curr - 1)) * ac)
        curr_sum_f    = prev_sum_f + curr_val_f

        curr_val_r    = ((4 ** (            curr    )) * ad)
        curr_sum_r    = prev_sum_r + curr_val_r

        if verbose:
            vals[curr] = [ curr_val_f, curr_val_r ]

        part[curr] = [ curr_sum_f, curr_sum_r ]

        if verbose:
            print " prev_sum_f {} curr_val_f {} curr_sum_f {} prev_sum_r {} curr_val_r {} curr_sum_r {}".format(prev_sum_f, curr_val_f, curr_sum_f, prev_sum_r, curr_val_r, curr_sum_r)

        if curr == kmer_size - 1:
            if verbose:
                print " curr", curr
                print " seqs F", " ".join(["{:>12s}".format(e[0]) for e in          seqs ]), "{:>12s}".format("SUM")
                print " raws F", " ".join(["{:12,d}".format(e[0]) for e in          raws ])
                print " vals F", " ".join(["{:12,d}".format(e[0]) for e in          vals ])
                print " part F", " ".join(["{:12,d}".format(e[0]) for e in          part ]), "{:12,d}".format(curr_sum_f)
                print
                print " seqs R", " ".join(["{:>12s}".format(e[1]) for e in          seqs ]), "{:>12s}".format("SUM")
                print " raws R", " ".join(["{:12,d}".format(e[1]) for e in          raws ])
                print " vals R", " ".join(["{:12,d}".format(e[1]) for e in reversed(vals)])
                print " part R", " ".join(["{:12,d}".format(e[1]) for e in reversed(part)]), "{:12,d}".format(curr_sum_r)
                print
            yield (curr_sum_f, curr_sum_r)

        else:
            for k in kmer_gen(kmer_size, curr=curr+1, seqs=seqs, raws=raws, vals=vals, part=part, verbose=verbose):
                yield k
*/



/*
BOOST_PYTHON_MODULE(kmer_gen)
{
    boost::python::class_<kmer_gen>("kmer_gen")
        //.def( "merge_jfs", &kmer_gen::merge_jfs )
        //.def( "merge_dbs", &kmer_gen::merge_dbs )
    ;
}

*/
