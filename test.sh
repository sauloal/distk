make clean all

./genc.py 3

python -c "import kmer_gen; print dir(kmer_gen); kmer_gen.version(); kmer_gen.extract_kmers('gen.py', 3)"
