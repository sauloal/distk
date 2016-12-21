#!/bin/bash

set -xeu

if [[ ! -f "test6.fasta" ]]; then
curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch00.fa                                       | grep -v '>' | tr -d '\n' > test6.fasta
fi
if [[ ! -f "test7.fasta" ]]; then
curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch{00,01,02,03,04,05,06,07,08,09,10,11,12}.fa | grep -v '>' | tr -d '\n' > test7.fasta
fi
if [[ ! -f "test8.fasta" ]]; then
echo -n '' > test8.fasta
for i in 00 01 02 03 04 05 06 07 08 09 10 11 12; do
curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch${i}.fa | grep -v '>' | tr -d '\n' >> test8.fasta
echo >> test8.fasta
done
fi
