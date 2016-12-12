set -xeu

ulimit -c unlimited

#make clean all

./kmer.py

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test1.fasta', 'test/test1.03.kmer', 3);" 2>&1
#time python -c "import kmer_set;                                          kmer_set.read_kmers(                       'test/test1.03.kmer');" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test2.fasta', 'test/test2.03.kmer', 3);" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test3.fasta', 'test/test3.03.kmer', 3);" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test4.fasta', 'test/test4.03.kmer', 3);" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test5.fasta', 'test/test5.03.kmer', 3);" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test6.fasta', 'test/test6.03.kmer', 3);" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test6.fasta', 'test/test6.05.kmer', 5);" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test6.fasta', 'test/test6.07.kmer', 7);" 2>&1
#time python -c "import kmer_set;                                          kmer_set.read_kmers(                       'test/test6.07.kmer');" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test6.fasta', 'test/test6.09.kmer', 9);" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test6.fasta', 'test/test6.11.kmer', 11);" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test6.fasta', 'test/test6.13.kmer', 13);" 2>&1
#time python -c "import kmer_set;                                          kmer_set.read_kmers(                       'test/test6.13.kmer');" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test6.fasta', 'test/test6.15.kmer', 15);" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test6.fasta', 'test/test6.17.kmer', 17);" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test6.fasta', 'test/test6.19.kmer', 19);" 2>&1

time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test6.fasta', 'test/test6.21.kmer', 21);" 2>&1
time python -c "import kmer_set;                                          kmer_set.read_kmers(                       'test/test6.21.kmer');" 2>&1

#time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); kmer_set.extract_kmers('test/test7.fasta', 'test/test7.03.kmer', 3);" 2>&1

