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
	./run_test.py "3" "2"
	./run_test.py "5" "2"

test03:
	./run_test.py "3" "3"
	./run_test.py "5" "3"
	./run_test.py "7" "3"

test04:
	./run_test.py "3" "4"
	./run_test.py "5" "4"
	./run_test.py "7" "4"
	./run_test.py "9" "4"

test05:
	./run_test.py "3" "5"
	./run_test.py "5" "5"
	./run_test.py "7" "5"
	./run_test.py "9" "5"
	./run_test.py "11" "5"

test06:
	./run_test.py "3" "6"
	./run_test.py "5" "6"
	./run_test.py "7" "6"
	./run_test.py "9" "6"
	./run_test.py "11" "6"
	./run_test.py "13" "6"
    
test07:
	./run_test.py "3" "7"
	./run_test.py "5" "7"
	./run_test.py "7" "7"
	./run_test.py "9" "7"
	./run_test.py "11" "7"
	./run_test.py "13" "7"
	#./run_test.py "15" "7"

test08:
	./run_test.py "3" "8"
	./run_test.py "5" "8"
	./run_test.py "7" "8"
	./run_test.py "9" "8"
	./run_test.py "11" "8"
	./run_test.py "13" "8"
	#./run_test.py "15" "8"
	#./run_test.py "17" "8"

#test09:
#	./run_test.py "3" "9"
#	./run_test.py "5" "9"
#	./run_test.py "7" "9"
#	./run_test.py "9" "9"
#	./run_test.py "11" "9"
#	./run_test.py "13" "9"
#	./run_test.py "15" "9"
#	./run_test.py "17" "9"
#	./run_test.py "19" "9"
#
#test10:
#	./run_test.py "3 5 7 9 11 13 15 17 19 21" "10"

test11:
	@#all triplets
	./run_test.py "3" "10"

test12:
	@#short sequence
	./run_test.py "3" "12"
	./run_test.py "5" "12"
	./run_test.py "7" "12"
	./run_test.py "9" "12"
	./run_test.py "11" "12"
	./run_test.py "13" "12"
	#./run_test.py "15" "12"
	#./run_test.py "17" "12"
	#./run_test.py "19" "12"
	#./run_test.py "21" "12"

test13:
	@#1 N
	./run_test.py "3" "13"
	./run_test.py "5" "13"
	./run_test.py "7" "13"
	./run_test.py "9" "13"
	./run_test.py "11" "13"
	./run_test.py "13" "13"
	#./run_test.py "15" "13"
	#./run_test.py "17" "13"
	#./run_test.py "19" "13"
	#./run_test.py "21" "13"

test14:
	@#sequence
	./run_test.py "3" "14"
	./run_test.py "5" "14"
	./run_test.py "7" "14"
	./run_test.py "9" "14"
	./run_test.py "11" "14"
	./run_test.py "13" "14"
	#./run_test.py "15" "14"
	#./run_test.py "17" "14"
	#./run_test.py "19" "14"
	#./run_test.py "21" "14"

test15:
	@#2 Ns
	./run_test.py "3" "15"
	./run_test.py "5" "15"
	./run_test.py "7" "15"
	./run_test.py "9" "15"
	./run_test.py "11" "15"
	./run_test.py "13" "15"
	#./run_test.py "15" "15"
	#./run_test.py "17" "15"
	#./run_test.py "19" "15"
	#./run_test.py "21" "15"

test16:
	@#tomato chromosome 00
	./run_test.py "3" "16"
	./run_test.py "5" "16"
	./run_test.py "7" "16"
	./run_test.py "9" "16"
	./run_test.py "11" "16"
	./run_test.py "13" "16"
	#./run_test.py "15" "16"
	#./run_test.py "17" "16"
	#./run_test.py "19" "16"
	#./run_test.py "21" "16"

test17:
	@#tomato chromosomes as one
	./run_test.py "3" "17"
	./run_test.py "5" "17"
	./run_test.py "7" "17"
	./run_test.py "9" "17"
	./run_test.py "11" "17"
	./run_test.py "13" "17"
	#./run_test.py "15" "17"
	#./run_test.py "17" "17"
	#./run_test.py "19" "17"
	#./run_test.py "21" "17"

test18:
	@#tomato chromosomes each line
	./run_test.py "3" "18"
	./run_test.py "5" "18"
	./run_test.py "7" "18"
	./run_test.py "9" "18"
	./run_test.py "11" "18"
	./run_test.py "13" "18"
	#./run_test.py "15" "18"
	#./run_test.py "17" "18"
	#./run_test.py "19" "18"
	#./run_test.py "21" "18"

testMatrix:




.PHONY: gen_check check_fasta.sha256 check_kmer.sha256 check_index.sha256 check_matrix.sha256
gen_check: check_fasta.sha256 check_kmer.sha256 check_index.sha256 check_matrix.sha256

check_fasta.sha256:
	sha256sum *.fasta.gz > $@ || true

check_kmer.sha256:
	sha256sum *.kmer     > $@ || true

check_index.sha256:
	sha256sum *.index    > $@ || true

check_matrix.sha256:
	sha256sum *.matrix   > $@ || true



.PHONY: check check_fasta check_kmer check_index text_matrix
check: check_fasta check_kmer check_index check_matrix

check_fasta:
	sha256sum -c check_fasta.sha256

check_kmer:
	sha256sum -c check_kmer.sha256

check_index:
	sha256sum -c check_index.sha256

check_matrix:
	sha256sum -c check_matrix.sha256
