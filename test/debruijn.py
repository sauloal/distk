#!/usr/bin/env python

#https://en.wikipedia.org/wiki/De_Bruijn_sequence

import os
import sys

def main():
	kmer = int(sys.argv[1])
	de_bruijn("ACGT", kmer)
	print
	#print(de_bruijn(2, 3))
	#print(de_bruijn("abcd", 2))

def de_bruijn(k, n, ret=False):
    """
    De Bruijn sequence for alphabet k
    and subsequences of length n.
    """

    try:
        # let's see if k can be cast to an integer;
        # if so, make our alphabet a list
        _ = int(k)
        alphabet = list(map(str, range(k)))

    except (ValueError, TypeError):
        alphabet = k
        k = len(k)

    a = [0] * k * n
    sequence = []

    def db(t, p, save=False):
        if t > n:
            if n % p == 0:
                piece = a[1:p + 1]
                if save:
                    sequence.extend(a[1:p + 1])
                else:
                    sys.stdout.write( "".join(alphabet[i] for i in piece if alphabet[i]) )
        else:
            a[t] = a[t - p]
            db(t + 1, p, save=save)
            for j in range(a[t - p] + 1, k):
                a[t] = j
                db(t + 1, t, save=save)

    db(1, 1, save=ret)
    if ret:
        return "".join(alphabet[i] for i in sequence)

if __name__ == '__main__':
	main()
