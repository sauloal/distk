ulimit -c unlimited

make clean all && \
./genc.py 3 && \
python -c "import kmer_gen; print dir(kmer_gen); kmer_gen.version(); kmer_gen.extract_kmers('test/test1.fasta', 3);  kmer_gen.extract_kmers('test/test2.fasta', 3);"
