#!/usr/bin/env python

import os
import sys
import time

sys.path.insert(0, '..')

import kmer_set

print dir(kmer_set)

kmer_set.version()

def main():
	exec_type    =                   sys.argv[1]
	kmer_lens    = [ int(k) for k in sys.argv[2].split() ]
	test_indexes = [ int(i) for i in sys.argv[3].split() ]

	assert exec_type in 'read,write,compare'.split(',')

	outs = []
	for kmer_len in kmer_lens:
		for test_index in test_indexes:
			print kmer_len, test_index

			fa = "test{:02d}.fasta.gz".format( test_index )
			km = "test{:02d}.{:02d}.kmer".format( test_index, kmer_len )

			print fa, km
			outs.append(km)

			def e_write():
				if os.path.exists(km):
					os.remove(km)
	
				time1 = time.time()
				ek    = kmer_set.extract_kmers(kmer_len)
				print dir(ek)
				ek.read_one_liner(fa)
				ek.save_kmer_db(km)
				time2 = time.time()
				
				print 'FINISHED SAVING TEST %d KMER LEN %d IN %0.3f s' % (test_index, kmer_len, (time2-time1))
				
				return ek

			def e_read():
				if os.path.exists(km):
					time1 = time.time()
					ek2   = kmer_set.extract_kmers()
					ek2.read_kmer_db(km)
					re    = ek2.get_kmer_db()
					time2 = time.time()
	
					print 'RE:', (re if (kmer_len <= 7) else '')
	
					print 'FINISHED READING TEST %d KMER LEN %d IN %0.3f s' % (test_index, kmer_len, (time2-time1))
					
					return ek2

			if   exec_type == 'write':
				e_write()

			elif exec_type == 'read':
				e_read()

			elif exec_type == 'compare':
				k1 = e_write()
				k2 = e_read()
				r  = k1.is_clone(k2)
				print r.reason, r.res
				print dir(r)
				

if __name__ == "__main__":
	main()
