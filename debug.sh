set -xeu

t=2
k=13
gdb --args python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); ek = kmer_set.extract_kmers("$k"); ek.read_file_one_liner('test/test"$t".fasta'); ek.save_kmer_db('test/test"$t"."$k".kmer'); print 'FINISHED';"
