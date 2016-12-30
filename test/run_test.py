#!/usr/bin/env python

import os
import sys
sys.path.insert(0, '..')

import kmer_set

print dir(kmer_set)

kmer_set.version()

def main():
	exec_type    =                   sys.argv[1]
	kmer_lens    = [ int(k) for k in sys.argv[2].split() ]
	test_indexes = [ int(i) for i in sys.argv[3].split() ]

	outs = []
	for kmer_len in kmer_lens:
		for test_index in test_indexes:
			print kmer_len, test_index

			fa = "test{:02d}.fasta.gz".format( test_index )
			km = "test{:02d}.{:02d}.kmer".format( test_index, kmer_len )

			print fa, km
			outs.append(km)

			if exec_type == 'write':
				if os.path.exists(km):
					os.remove(km)
	
				ek = kmer_set.extract_kmers(kmer_len)
				ek.read_one_liner(fa)
				ek.save_kmer_db(km)
				print 'FINISHED SAVING'

			elif exec_type == 'read':
				if os.path.exists(km):
					ek2 = kmer_set.extract_kmers(kmer_len)
					ek2.read_kmer_db(km)
					re = ek2.get_kmer_db()
	
					print 'RE:', (re if (kmer_len <= 9) else '')
	
					print 'FINISHED READING'

if __name__ == "__main__":
	main()
