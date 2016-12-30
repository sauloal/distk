SHELL:=/bin/bash
PYPY := $(shell command -v pypy 2> /dev/null)

ifdef PYPY
PYHTON=pypy
else
PYHTON=python
endif

all: run

clean:
	rm -v *.kmer *.matrix || true

.PHONY: wipe
wipe: clean
	rm -v *.fasta.gz *.sha256 || true


.PHONY: get
ifdef SERVER
get: test01.fasta.gz test02.fasta.gz test03.fasta.gz test04.fasta.gz test05.fasta.gz test06.fasta.gz test07.fasta.gz test08.fasta.gz test09.fasta.gz test10.fasta.gz test11.fasta.gz test12.fasta.gz test13.fasta.gz test14.fasta.gz test15.fasta.gz test16.fasta.gz test17.fasta.gz test18.fasta.gz test19.fasta.gz
else
get: test01.fasta.gz test02.fasta.gz test03.fasta.gz test04.fasta.gz test05.fasta.gz test06.fasta.gz test07.fasta.gz test08.fasta.gz                                                 test12.fasta.gz test13.fasta.gz test14.fasta.gz test15.fasta.gz test16.fasta.gz test17.fasta.gz test18.fasta.gz test19.fasta.gz
endif

.PHONY: run
ifdef SERVER
run: get test01 test02 test03 test04 test05 test06 test07 test08 test09 test10 test11 test12 test13 test14 test15 test16 test17 test18 test19 testMatrix
else
run: get test01 test02 test03 test04 test05 test06 test07 test08                      test12 test13 test14 test15 test16 test17 test18 test19 testMatrix
endif

.PHONY: gen_check check_fasta.sha256 check_kmer.sha256 check_index.sha256 check_matrix.sha256
gen_check: check_fasta.sha256 check_kmer.sha256 check_index.sha256 check_matrix.sha256

.PHONY: check check_fasta check_kmer check_index text_matrix
check: check_fasta check_kmer check_index check_matrix




test01.fasta.gz:
	$(PYTHON) ./debruijn.py 1 | gzip -1 > $@.tmp && mv $@.tmp $@

test02.fasta.gz:
	$(PYTHON) ./debruijn.py 3 | gzip -1 > $@.tmp && mv $@.tmp $@

test03.fasta.gz:
	$(PYTHON) ./debruijn.py 5 | gzip -1 > $@.tmp && mv $@.tmp $@

test04.fasta.gz:
	$(PYTHON) ./debruijn.py 7 | gzip -1 > $@.tmp && mv $@.tmp $@

test05.fasta.gz:
	$(PYTHON) ./debruijn.py 9 | gzip -1 > $@.tmp && mv $@.tmp $@

test06.fasta.gz:
	$(PYTHON) ./debruijn.py 11 | gzip -1 > $@.tmp && mv $@.tmp $@

test07.fasta.gz:
	$(PYTHON) ./debruijn.py 13 | gzip -1 > $@.tmp && mv $@.tmp $@

test08.fasta.gz:
	$(PYTHON) ./debruijn.py 15 | gzip -1 > $@.tmp && mv $@.tmp $@

ifdef SERVER
test09.fasta.gz:
	$(PYTHON) ./debruijn.py 17 | gzip -1 > $@.tmp && mv $@.tmp $@

test10.fasta.gz:
	$(PYTHON) ./debruijn.py 19 | gzip -1 > $@.tmp && mv $@.tmp $@

test11.fasta.gz:
	$(PYTHON) ./debruijn.py 21 | gzip -1 > $@.tmp && mv $@.tmp $@
endif

test12.fasta.gz:
	echo -e 'AAA\nAAC\nAAG\nAAT\n\nACA\nACC\nACG\nACT\n\nAGA\nAGC\nAGG\nAGT\n\nATA\nATC\nATG\nATT\n\n\n\n\nCAA\nCAC\nCAG\nCAT\n\nCCA\nCCC\nCCG\nCCT\n\nCGA\nCGC\nCGG\nCGT\n\nCTA\nCTC\nCTG\nCTT\n\n\n\n\nGAA\nGAC\nGAG\nGAT\n\nGCA\nGCC\nGCG\nGCT\n\nGGA\nGGC\nGGG\nGGT\n\nGTA\nGTC\nGTG\nGTT\n\n\n\n\nTAA\nTAC\nTAG\nTAT\n\nTCA\nTCC\nTCG\nTCT\n\nTGA\nTGC\nTGG\nTGT\n\nTTA\nTTC\nTTG\nTTT\n\n' | gzip -1 > $@.tmp && mv $@.tmp $@

test13.fasta.gz:
	echo "CGTACGTACGTACGTACGT" | gzip -1 > $@.tmp && mv $@.tmp $@

test14.fasta.gz:
	echo "AAACAAGAATACACGACTAGCAGGAGTATCATGATT" | gzip -1 > $@.tmp && mv $@.tmp $@

test15.fasta.gz:
	echo "ACGTACGTACGTACGTACGTNACGTACGTACGTACGTACGT" | gzip -1 > $@.tmp && mv $@.tmp $@

test16.fasta.gz:
	echo "AAACAAGAATACACGACNNTAGCAGGAGTATCATGATT" | gzip -1 > $@.tmp && mv $@.tmp $@

test17.fasta.gz:
	curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch00.fa                                       | grep -v '>' | tr -d '\n' | gzip -1 > $@.tmp && mv $@.tmp $@

test18.fasta.gz: test19.fasta.gz
	zcat test19.fasta.gz | tr -d '\n' | gzip -1 > $@.tmp && mv $@.tmp $@

test19.fasta.gz:
	rm -v test19.fasta.tmp test19.fasta test19.fasta.gz || true
	for i in 00 01 02 03 04 05 06 07 08 09 10 11 12; do \
		curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch$${i}.fa | grep -v '>' | tr -d '\n' >> test19.fasta.tmp; \
		echo >> test19.fasta.tmp; \
	done
	mv test19.fasta.tmp test19.fasta && gzip -1 test19.fasta







test01: test01.fasta.gz
	@#debruijn - all 1 mers
	$(eval TEST_NUM=1)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test02: test02.fasta.gz
	@#debruijn - all 3 mers
	$(eval TEST_NUM=2)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test03: test03.fasta.gz
	@#debruijn - all 5 mers
	$(eval TEST_NUM=3)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test04: test04.fasta.gz
	@#debruijn - all 7 mers
	$(eval TEST_NUM=4)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test05: test05.fasta.gz
	@#debruijn - all 9 mers
	$(eval TEST_NUM=5)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test06: test06.fasta.gz
	@#debruijn - all 11 mers
	$(eval TEST_NUM=6)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test07: test07.fasta.gz
	@#debruijn - all 13 mers
	$(eval TEST_NUM=7)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test08: test08.fasta.gz
	@#debruijn - all 15 mers
	$(eval TEST_NUM=8)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


ifdef SERVER
test09: test09.fasta.gz
	@#debruijn - all 17 mers
	$(eval TEST_NUM=9)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)

test10: test10.fasta.gz
	@#debruijn - all 19 mers
	$(eval TEST_NUM=10)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)

test11: test11.fasta.gz
	@#debruijn - all 21 mers
	$(eval TEST_NUM=11)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
endif


test12: test12.fasta.gz
	@#all triplets - one each line
	$(eval TEST_NUM=12)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)


test13: test13.fasta.gz
	@#short sequence
	$(eval TEST_NUM=13)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test14: test14.fasta.gz
	@#short sequence 2
	$(eval TEST_NUM=14)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test15: test15.fasta.gz
	@#1 N
	$(eval TEST_NUM=15)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test16: test16.fasta.gz
	@#2 Ns
	$(eval TEST_NUM=16)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test17: test17.fasta.gz
	@#tomato chromosome 00
	$(eval TEST_NUM=17)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test18: test18.fasta.gz
	@#all tomato chromosomes as one
	$(eval TEST_NUM=18)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
	./run_test.py write "15" $(TEST_NUM) && ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test19: test19.fasta.gz
	@#all tomato chromosomes - one each line
	$(eval TEST_NUM=19)
	./run_test.py write  "3" $(TEST_NUM) && ./run_test.py read  "3" $(TEST_NUM)
	./run_test.py write  "5" $(TEST_NUM) && ./run_test.py read  "5" $(TEST_NUM)
	./run_test.py write  "7" $(TEST_NUM) && ./run_test.py read  "7" $(TEST_NUM)
	./run_test.py write  "9" $(TEST_NUM) && ./run_test.py read  "9" $(TEST_NUM)
	./run_test.py write "11" $(TEST_NUM) && ./run_test.py read "11" $(TEST_NUM)
	./run_test.py write "13" $(TEST_NUM) && ./run_test.py read "13" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	./run_test.py write "17" $(TEST_NUM) && ./run_test.py read "17" $(TEST_NUM)
	./run_test.py write "19" $(TEST_NUM) && ./run_test.py read "19" $(TEST_NUM)
	./run_test.py write "21" $(TEST_NUM) && ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


testMatrix:






check_fasta.sha256:
	sha256sum *.fasta.gz > $@.tmp && mv $@.tmp $@

check_kmer.sha256:
	sha256sum *.kmer     > $@.tmp && mv $@.tmp $@

check_index.sha256:
	sha256sum *.index    > $@.tmp && mv $@.tmp $@

check_matrix.sha256:
	sha256sum *.matrix   > $@.tmp && mv $@.tmp $@





check_fasta:
	sha256sum -c check_fasta.sha256

check_kmer:
	sha256sum -c check_kmer.sha256

check_index:
	sha256sum -c check_index.sha256

check_matrix:
	sha256sum -c check_matrix.sha256
