all: run



.PHONY: get
get: test01.fasta test02.fasta test03.fasta test04.fasta test05.fasta test06.fasta test07.fasta test08.fasta

.PHONY: run
run: get test01 test02 test03 test04 test05 test06 test07 test08 testMatrix



test01:
	./run_test.py "3" "1"

test02:
	./run_test.py "3 5 7 9 11 13 15 17" "2"

test03:
	./run_test.py "3 5 7 9 11 13 15 17" "3"

test04:
	./run_test.py "3 5 7 9 11 13 15 17" "4"

test05:
	./run_test.py "3 5 7 9 11 13 15 17" "5"

test06:
	./run_test.py "3 5 7 9 11 13 15 17 19" "6"

test07:
	./run_test.py "3 5 7 9 11 13 15 17 19" "7"

test08:
	./run_test.py "3 5 7 9 11 13 15 17 19" "8"

testMatrix:




.PHONY: gen_check check check_fasta check_kmer check_index text_matrix
gen_check:
	sha256sum *.fasta  > check_fasta.sha256
	sha256sum *.kmer   > check_kmer.sha256
	sha256sum *.index  > check_index.sha256
	sha256sum *.matrix > check_matrix.sha256

check: run check_fasta check_kmer check_index check_matrix

check_fasta: get
	sha256sum -c check_fasta.sha256

check_kmer: run
	sha256sum -c check_kmer.sha256

check_index: run
	sha256sum -c check_index.sha256

check_matrix: run
	sha256sum -c check_matrix.sha256




test01.fasta:
	./debruijn.py 1 > $@

test02.fasta:
	./debruijn.py 3 > $@

test03.fasta:
	./debruijn.py 5 > $@

test04.fasta:
	./debruijn.py 7 > $@

test05.fasta:
	./debruijn.py 9 > $@

test06.fasta:
	./debruijn.py 11 > $@

test07.fasta:
	./debruijn.py 13 > $@

test08.fasta:
	./debruijn.py 15 > $@

test09.fasta:
	./debruijn.py 19 > $@

test10.fasta:
	./debruijn.py 21 > $@

test11.fasta:
	echo -e 'AAA\nAAC\nAAG\nAAT\n\nACA\nACC\nACG\nACT\n\nAGA\nAGC\nAGG\nAGT\n\nATA\nATC\nATG\nATT\n\n\n\n\nCAA\nCAC\nCAG\nCAT\n\nCCA\nCCC\nCCG\nCCT\n\nCGA\nCGC\nCGG\nCGT\n\nCTA\nCTC\nCTG\nCTT\n\n\n\n\nGAA\nGAC\nGAG\nGAT\n\nGCA\nGCC\nGCG\nGCT\n\nGGA\nGGC\nGGG\nGGT\n\nGTA\nGTC\nGTG\nGTT\n\n\n\n\nTAA\nTAC\nTAG\nTAT\n\nTCA\nTCC\nTCG\nTCT\n\nTGA\nTGC\nTGG\nTGT\n\nTTA\nTTC\nTTG\nTTT\n\n' > $@

test12.fasta:
	echo "CGTACGTACGTACGTACGT" > $@

test13.fasta:
	echo "ACGTACGTACGTACGTACGTNACGTACGTACGTACGTACGT" > $@

test14.fasta:
	echo "AAACAAGAATACACGACTAGCAGGAGTATCATGATT" > $@

test15.fasta:
	echo "AAACAAGAATACACGACNNTAGCAGGAGTATCATGATT" > $@

test16.fasta:
	curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch00.fa                                       | grep -v '>' | tr -d '\n' > test6.fasta

test17.fasta:
	curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch{00,01,02,03,04,05,06,07,08,09,10,11,12}.fa | grep -v '>' | tr -d '\n' > test7.fasta

test18.fasta:
	for i in 00 01 02 03 04 05 06 07 08 09 10 11 12; do \
		curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch${i}.fa | grep -v '>' | tr -d '\n' >> test8.fasta; \
		echo >> test8.fasta; \
	done

