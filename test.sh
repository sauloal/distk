ulimit -c unlimited

make clean all && \
./kmer.py

time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); \
kmer_set.extract_kmers('test/test1.fasta', 3); \
kmer_set.extract_kmers('test/test2.fasta', 3); \
kmer_set.extract_kmers('test/test3.fasta', 3); \
kmer_set.extract_kmers('test/test4.fasta', 3); \
kmer_set.extract_kmers('test/test5.fasta', 3);"
