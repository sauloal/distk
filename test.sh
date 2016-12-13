set -xeu

ulimit -c unlimited

rm core || true

#make clean all

./kmer.py

for ti in 7; do
for kl in 7; do

#for ti in 7; do
#for kl in 3; do

#for ti in 1 2 3 4 5 6 7; do
#for kl in 3 5 7 9 11 13 15 17 19 21 23 25; do

kln=$kl

if [[ "$kl" < 10 ]]; then
kln="0"$kl
fi

fa=test/test${ti}.fasta
km=test/test${ti}.${kln}.kmer
lo=${km}.log
rm -v ${lo} ${km} || true
( time python -c "import kmer_set; print dir(kmer_set); kmer_set.version(); ek = kmer_set.extract_kmers("$kl"); ek.read_file('"$fa"'); ek.save_kmer('"$km"');" 2>&1 ) 2>&1 | tee -a ${lo}
( time python -c "import kmer_set;                                          ek = kmer_set.extract_kmers("$kl");                        ek.read_kmer('"$km"');" 2>&1 ) 2>&1 | tee -a ${lo}
done
done
