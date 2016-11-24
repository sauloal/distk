#!/usr/bin/python

import os
import sys
import struct
import time
import mmap

ALPHA = 'ACGT'

def seconds_to_time(seconds):
    m, s = divmod(seconds, 60)
    h, m = divmod(m      , 60)
    t    = "%3d:%02d:%02d" % (h, m, s)
    return t

def kmer_gen(kmer_size, curr=None, seqs=None, raws=None, vals=None, part=None, verbose=False):
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

def gen_kmer(kmer_size, verbose=False, block_size=5000000):
    fn         = 'key_{:02d}.key'.format(kmer_size)

    print "filename", fn

    if os.path.exists(fn):
        os.remove(fn)

    if os.path.exists(fn + '.tmp'):
        os.remove(fn + '.tmp')

    max_i      = (4 ** (kmer_size))

    if max_i < (block_size * 100):
        block_size = max_i / 100
        if block_size == 0:
            block_size = 1

    file_size  = max_i * 8

    fmt       = "{}Q".format(block_size)

    print "file size {:18,d}".format(file_size)

    with open(fn + '.tmp', 'w+b') as fhd:
        print "creating buffer"
        sys.stdout.flush()

        #fhd.write((file_size)*b'\0')
        fhd.seek(file_size-1)
        fhd.write("\0")
        fhd.seek(0)
        nums         = mmap.mmap(fhd.fileno(), 0, access=mmap.ACCESS_WRITE)
        vals         = [None] * block_size

        print "processing"
        sys.stdout.flush()

        j           = 0
        t_prev      = time.time()
        i_prev      = 0

        for i, (f,r) in enumerate(kmer_gen(kmer_size, verbose=verbose)):
            m = f

            if r < f:
                m = r

            i_perc = (i * 1.0) / max_i * 100.0

            if i != 0 and i % block_size == 0:
                t_curr = time.time()
                t_ela  = t_curr - t_prev
                speed  = (i * 1.0) / t_ela

                if speed != 0:
                    t_eta  = (max_i - i) / speed
            
                    print " {:18,d} / {:18,d} ({:6.2f}% ela {} speed {:12,.0f} k/s eta {}) J {:12,d} M {:12,d} - F {:12,d} R {:12,d}".format(i+1, max_i, i_perc, seconds_to_time(t_ela), speed, seconds_to_time(t_eta), j, m, f, r)

                j = ( i_prev * 8 )
                k = ( i_prev * 8 ) + ( block_size * 8 )
                #print "j {} k {} l {} b {} f {}".format( j, k, len(nums), block_size, fmt )
                nums[ j: k ] = struct.pack(fmt, *vals)
                i_prev = i

            if verbose:
                print " {:18,d} / {:18,d} ({:6.2f}% J {:12,d} M {:12,d} - F {:12,d} R {:12,d}".format(i+1, max_i, i_perc, j, m, f, r)

            vals[ i % block_size ] = m

            if f < r:
                j += 1

        flen = (i % block_size) + 1
        fmt  = '{:d}Q'.format(flen)
        seg  = vals[:flen]

        if verbose:
            print "block_size", block_size
            print "remaining ", flen
            print "fmt       ", fmt
            print "seg begin ", seg[   :10]
            print "sef end   ", seg[-10:  ]

        j = ( i_prev * 8 )
        k = ( i_prev * 8 ) + ( flen * 8 )
        #print "j {} k {} l {} b {} f {}".format( j, k, len(nums), flen, fmt ), "seg", seg
        nums[ j: k ] = struct.pack(fmt, *seg)

        nums.flush()

    os.rename(fn+'.tmp', fn)

def read_bin(fhd):
    val = fhd.read(8)

    if val == '':
        return None, None

    else:
        num = struct.unpack("Q", val)[0]
        return val, num

def read_kmer(kmer_size):
    fn         = 'key_{:02d}.key'.format(kmer_size)

    with open(fn, 'rb') as fhd:
        val, num = read_bin(fhd)
        i        = 1

        if val is not None:
            print "{:18,d} {:35s} {:12,d}".format(i, repr(val), num)

        while val is not None:
            i += 1
            val, num = read_bin(fhd)
            if val is not None:
                print "{:18,d} {:35s} {:12,d}".format(i, repr(val), num)

def main():
    verbose   = False

    kmer_size = int(sys.argv[1])

    gen_kmer(kmer_size, verbose=verbose)
    
    #read_kmer(kmer_size)


if __name__ == '__main__':
    main()
