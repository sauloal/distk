#!/usr/bin/python

import os
import sys
import struct

import kmer_gen as kgc

print dir(kgc)
print kgc.fact(3)
kgc.version()

DEBUG    = True
#DEBUG    = False
BIN_SIZE = 8

def gen_kmer(kmer_size, verbose=False):
    fn         = 'key_{:02d}.key'.format(kmer_size)

    print "filename", fn

    #if os.path.exists(fn):
    #    os.remove(fn)

    #if os.path.exists(fn + '.tmp'):
    #    os.remove(fn + '.tmp')

    max_i      = (4 ** (kmer_size))
    file_size  = max_i * BIN_SIZE

    print "file size {:18,d}".format(file_size)

    kg = kgc.kmer_gen_m(kmer_size)

    #os.rename(fn+'.tmp', fn)

def read_bin(fhd):
    val = fhd.read(BIN_SIZE)

    if val == '':
        return None, None

    else:
        num = struct.unpack("Q", val)[0]
        return val, num

def s_to_h(s):
    return ":".join("{:03d}".format(ord(c)) for c in s)

def read_kmer(kmer_size):
    fn         = 'key_{:d}.key'.format(kmer_size)

    with open(fn, 'rb') as fhd:
        val, num = read_bin(fhd)
        i        = 1

        if val is not None:
            print "{:18,d} {:31s} {:30,d}".format(i, s_to_h(val), num)

        while val is not None:
            i        += 1
            val, num  = read_bin(fhd)

            if val is not None:
                print "{:18,d} {:31s} {:30,d}".format(i, s_to_h(val), num)

def main():
    verbose   = False

    if DEBUG:
        verbose   = True

    kmer_size = int(sys.argv[1])

    gen_kmer(kmer_size, verbose=verbose)
    
    if DEBUG and kmer_size <= 5:
        read_kmer(kmer_size)


if __name__ == '__main__':
    main()
