SHELL:=/bin/bash
PYPY := $(shell command -v pypy 2> /dev/null)

ifdef PYPY
PYHTON=pypy
else
PYHTON=python
endif

all: run



.PHONY: get
get: test01.fasta.gz test02.fasta.gz test03.fasta.gz test04.fasta.gz test05.fasta.gz test06.fasta.gz test07.fasta.gz test08.fasta.gz test11.fasta.gz test12.fasta.gz test13.fasta.gz test14.fasta.gz test15.fasta.gz test16.fasta.gz test17.fasta.gz test18.fasta.gz
#test09.fasta.gz test10.fasta.gz 

test01.fasta.gz:
	$(PYTHON) ./debruijn.py 1 | gzip -1 > $@

test02.fasta.gz:
	$(PYTHON) ./debruijn.py 3 | gzip -1 > $@

test03.fasta.gz:
	$(PYTHON) ./debruijn.py 5 | gzip -1 > $@

test04.fasta.gz:
	$(PYTHON) ./debruijn.py 7 | gzip -1 > $@

test05.fasta.gz:
	$(PYTHON) ./debruijn.py 9 | gzip -1 > $@

test06.fasta.gz:
	$(PYTHON) ./debruijn.py 11 | gzip -1 > $@

test07.fasta.gz:
	$(PYTHON) ./debruijn.py 13 | gzip -1 > $@

test08.fasta.gz:
	$(PYTHON) ./debruijn.py 15 | gzip -1 > $@

#test09.fasta.gz:
#	$(PYTHON) ./debruijn.py 19 | gzip -1 > $@
#
#test10.fasta.gz:
#	$(PYTHON) ./debruijn.py 21 | gzip -1 > $@

test11.fasta.gz:
	echo -e 'AAA\nAAC\nAAG\nAAT\n\nACA\nACC\nACG\nACT\n\nAGA\nAGC\nAGG\nAGT\n\nATA\nATC\nATG\nATT\n\n\n\n\nCAA\nCAC\nCAG\nCAT\n\nCCA\nCCC\nCCG\nCCT\n\nCGA\nCGC\nCGG\nCGT\n\nCTA\nCTC\nCTG\nCTT\n\n\n\n\nGAA\nGAC\nGAG\nGAT\n\nGCA\nGCC\nGCG\nGCT\n\nGGA\nGGC\nGGG\nGGT\n\nGTA\nGTC\nGTG\nGTT\n\n\n\n\nTAA\nTAC\nTAG\nTAT\n\nTCA\nTCC\nTCG\nTCT\n\nTGA\nTGC\nTGG\nTGT\n\nTTA\nTTC\nTTG\nTTT\n\n' | gzip -1 > $@

test12.fasta.gz:
	echo "CGTACGTACGTACGTACGT" | gzip -1 > $@

test13.fasta.gz:
	echo "ACGTACGTACGTACGTACGTNACGTACGTACGTACGTACGT" | gzip -1 > $@

test14.fasta.gz:
	echo "AAACAAGAATACACGACTAGCAGGAGTATCATGATT" | gzip -1 > $@

test15.fasta.gz:
	echo "AAACAAGAATACACGACNNTAGCAGGAGTATCATGATT" | gzip -1 > $@

test16.fasta.gz:
	curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch00.fa                                       | grep -v '>' | tr -d '\n' | gzip -1 > $@

test17.fasta.gz:
	curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch{00,01,02,03,04,05,06,07,08,09,10,11,12}.fa | grep -v '>' | tr -d '\n' | gzip -1 > $@

test18.fasta.gz:
	for i in 00 01 02 03 04 05 06 07 08 09 10 11 12; do \
		curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch${i}.fa | grep -v '>' | tr -d '\n' >> test8.fasta; \
		echo >> test8.fasta; \
	done
	gzip -1 test18.fasta





.PHONY: run
run: get test01 test02 test03 test04 test05 test06 test07 test08 test11 test12 test13 test14 test15 test16 test17 test18 testMatrix
# test09 test10

test01:
	./run_test.py "3" "1"

test02:
	./run_test.py "3 5" "2"

test03:
	./run_test.py "3 5 7" "3"

test04:
	./run_test.py "3 5 7 9" "4"

test05:
	./run_test.py "3 5 7 9 11" "5"

test06:
	./run_test.py "3 5 7 9 11 13" "6"

test07:
	./run_test.py "3 5 7 9 11 13 15" "7"

test08:
	./run_test.py "3 5 7 9 11 13 15 17" "8"

test09:
	./run_test.py "3 5 7 9 11 13 15 17 19" "9"

test10:
	./run_test.py "3 5 7 9 11 13 15 17 19 21" "10"

test11:
	@#all triplets
	./run_test.py "3" "10"

test12:
	@#shot sequence
	./run_test.py "3 5 7 9 11 13 15 17 19 21" "12"

test13:
	@#1 N
	./run_test.py "3 5 7 9 11 13 15 17 19 21" "13"

test14:
	@#sequence
	./run_test.py "3 5 7 9 11 13 15 17 19 21" "14"

test15:
	@#2 Ns
	./run_test.py "3 5 7 9 11 13 15 17 19 21" "15"

test16:
	@#tomato chromosome 00
	./run_test.py "3 5 7 9 11 13 15 17 19 21" "16"

test17:
	@#tomato chromosomes as one
	./run_test.py "3 5 7 9 11 13 15 17 19 21" "17"

test18:
	@#tomato chromosomes each line
	./run_test.py "3 5 7 9 11 13 15 17 19 21" "18"

testMatrix:




.PHONY: gen_check check_fasta.sha256 check_kmer.sha256 check_index.sha256 check_matrix.sha256
gen_check: check_fasta.sha256 check_kmer.sha256 check_index.sha256 check_matrix.sha256

check_fasta.sha256: get
	sha256sum *.fasta.gz > $@

check_kmer.sha256:
	sha256sum *.kmer     > $@

check_index.sha256:
	sha256sum *.index    > $@

check_matrix.sha256:
	sha256sum *.matrix   > $@



.PHONY: check check_fasta check_kmer check_index text_matrix
check: run check_fasta check_kmer check_index check_matrix

check_fasta: check_fasta.sha256
	sha256sum -c check_fasta.sha256

check_kmer: run check_kmer.sha256
	sha256sum -c check_kmer.sha256

check_index: run check_index.sha256
	sha256sum -c check_index.sha256

check_matrix: run check_matrix.sha256
	sha256sum -c check_matrix.sha256
