#!/bin/bash

set -xeu

ulimit -c unlimited

rm core || true

#make clean all

./kmer.py

for kmer_len in 3; do
fls=""

kmer_len_num=$kmer_len

if [[ "$kmer_len" -lt "10" ]]; then
kmer_len_num="0"$kmer_len
fi

for test_index in 1 2 3 4; do

#for kmer_len in 3; do
#for test_index in 7; do

#for kmer_len in 3 5 7 9 11 13 15 17 19 21 23 25; do
#for test_index in 1 2 3 4 5 6 7; do

fa=test/test${test_index}.fasta
km=test/test${test_index}.${kmer_len_num}.kmer
lo=${km}.log

if [[ "${fls}" != "" ]]; then
fls="${fls},"
fi

fls="${fls}${km}"

rm -v ${lo} ${km} || true

( time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); ek = kmer_set.extract_kmers("$kmer_len"); ek.read_file_one_liner('"$fa"');      ek.save_kmer_db('"$km"');" 2>&1 ) 2>&1 | tee -a ${lo}
( time python -c "import kmer_set;                                          ek = kmer_set.extract_kmers("$kmer_len");                                  re = ek.read_kmer_db( '"$km"'); print re if ("$kmer_len" <= 5) else ''" 2>&1 ) 2>&1 | tee -a ${lo}

done

out_matrix="test/test_m${kmer_len_num}.matrix"
rm ${out_matrix} || true
( time python -c "import kmer_set;                                          ek = kmer_set.extract_kmers("$kmer_len"); m = ek.merge_kmers('"${out_matrix}"', '"${fls}"'.split(',')); print m;" 2>&1 ) 2>&1 | tee -a ${lo}

done

