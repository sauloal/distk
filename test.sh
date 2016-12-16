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

for test_index in 1; do

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

( time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); ek = kmer_set.extract_kmers("$kmer_len"); ek.read_file_one_liner('"$fa"'); ek.save_kmer_db('"$km"'); print 'FINISHED';" 2>&1 ) 2>&1 | tee -a ${lo}
if [[ -f "core" ]]; then exit 1; fi
( time python -c "import kmer_set;                                          ek = kmer_set.extract_kmers("$kmer_len");                                  ek.read_kmer_db('"$km"'); re = ek.get_kmer_db(); print 'RE:',re if ("$kmer_len" <= 9) else ''" 2>&1 ) 2>&1 | tee -a ${lo}
if [[ -f "core" ]]; then exit 1; fi

done

out_matrix="test/test_m${kmer_len_num}"
rm ${out_matrix} || true
( time python -c "import kmer_set; import os;                               ek = kmer_set.extract_kmers("$kmer_len"); m = ek.merge_kmers('"${out_matrix}"', [x for x in '"${fls}"'.split(',') if os.path.exists(x)]); print m;" 2>&1 ) 2>&1 | tee -a ${lo}
if [[ -f "core" ]]; then exit 1; fi

done

