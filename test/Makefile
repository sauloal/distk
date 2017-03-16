SHELL:=/bin/bash

PYPY=$(shell command -v pypy 2> /dev/null)
GZIP=$(shell command -v pigz 2> /dev/null)
TIME=$(shell command -v /usr/bin/time 2> /dev/null)

ifdef PYPY
PYTHON=pypy
else
PYTHON=python
endif

ifdef GZIP
GZIP=pigz
GUNZIP=pigz -d
else
GZIP=gzip
GUNZIP=gunzip
endif

ifdef TIME
TIME=/usr/bin/time -v
else
TIME=time
endif

all: run

clean:
	rm -v *.kmer *.matrix *.index || true

.PHONY: wipe
wipe: clean
	rm -v *.fasta.gz *.sha256 || true


.PHONY: get
ifdef SERVER
get: test01.fasta.gz test02.fasta.gz test03.fasta.gz test04.fasta.gz test05.fasta.gz test06.fasta.gz test07.fasta.gz test08.fasta.gz test09.fasta.gz test10.fasta.gz test11.fasta.gz test12.fasta.gz test13.fasta.gz test14.fasta.gz test15.fasta.gz test16.fasta.gz test17.fasta.gz test18.fasta.gz test19.fasta.gz
else
get: test01.fasta.gz test02.fasta.gz test03.fasta.gz test04.fasta.gz test05.fasta.gz test06.fasta.gz test07.fasta.gz                                                                 test12.fasta.gz test13.fasta.gz test14.fasta.gz test15.fasta.gz test16.fasta.gz test17.fasta.gz test18.fasta.gz test19.fasta.gz
endif

.PHONY: run
ifdef SERVER
run: get test01 test02 test03 test04 test05 test06 test07 test08 test09 test10 test11 test12 test13 test14 test15 test16 test17 test18 test19 testMatrix
else
run: get test01 test02 test03 test04 test05 test06 test07                             test12 test13 test14 test15 test16 test17 test18 test19 testMatrix
endif

.PHONY: gen_check check_fasta.sha256 check_kmer.sha256 check_index.sha256 check_matrix.sha256
gen_check: check_fasta.sha256 check_kmer.sha256 check_index.sha256 check_matrix.sha256

.PHONY: check check_fasta check_kmer check_index text_matrix
check: check_fasta check_kmer check_index check_matrix




test01.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py  1 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test02.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py  3 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test03.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py  5 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test04.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py  7 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test05.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py  9 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test06.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py 11 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test07.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py 13 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test08.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py 15 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

ifdef SERVER
test09.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py 17 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test10.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py 19 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test11.fasta.gz:
	$(TIME) $(PYTHON) ./debruijn.py 21 | $(GZIP) -1c > $@.tmp && mv $@.tmp $@
endif

test12.fasta.gz:
	echo -e 'AAA\nAAC\nAAG\nAAT\n\nACA\nACC\nACG\nACT\n\nAGA\nAGC\nAGG\nAGT\n\nATA\nATC\nATG\nATT\n\n\n\n\nCAA\nCAC\nCAG\nCAT\n\nCCA\nCCC\nCCG\nCCT\n\nCGA\nCGC\nCGG\nCGT\n\nCTA\nCTC\nCTG\nCTT\n\n\n\n\nGAA\nGAC\nGAG\nGAT\n\nGCA\nGCC\nGCG\nGCT\n\nGGA\nGGC\nGGG\nGGT\n\nGTA\nGTC\nGTG\nGTT\n\n\n\n\nTAA\nTAC\nTAG\nTAT\n\nTCA\nTCC\nTCG\nTCT\n\nTGA\nTGC\nTGG\nTGT\n\nTTA\nTTC\nTTG\nTTT\n\n' | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test13.fasta.gz:
	echo "CGTACGTACGTACGTACGT"                       | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test14.fasta.gz:
	echo "AAACAAGAATACACGACTAGCAGGAGTATCATGATT"      | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test15.fasta.gz:
	echo "ACGTACGTACGTACGTACGTNACGTACGTACGTACGTACGT" | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test16.fasta.gz:
	echo "AAACAAGAATACACGACNNTAGCAGGAGTATCATGATT"    | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test17.fasta.gz:
	curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch00.fa | grep -v '>' | tr -d '\n' | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test18.fasta.gz: test19.fasta.gz
	zcat test19.fasta.gz | tr -d '\n' | $(GZIP) -1c > $@.tmp && mv $@.tmp $@

test19.fasta.gz:
	rm -v test19.fasta.tmp test19.fasta test19.fasta.gz || true
	for i in 00 01 02 03 04 05 06 07 08 09 10 11 12; do \
		curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch$${i}.fa | grep -v '>' | tr -d '\n' >> test19.fasta.tmp; \
		echo >> test19.fasta.tmp; \
	done
	mv test19.fasta.tmp test19.fasta && $(GZIP) -1 test19.fasta







test01: test01.fasta.gz
	@#debruijn - all 1 mers
	$(eval TEST_NUM=1)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test02: test02.fasta.gz
	@#debruijn - all 3 mers
	$(eval TEST_NUM=2)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test03: test03.fasta.gz
	@#debruijn - all 5 mers
	$(eval TEST_NUM=3)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test04: test04.fasta.gz
	@#debruijn - all 7 mers
	$(eval TEST_NUM=4)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test05: test05.fasta.gz
	@#debruijn - all 9 mers
	$(eval TEST_NUM=5)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test06: test06.fasta.gz
	@#debruijn - all 11 mers
	$(eval TEST_NUM=6)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test07: test07.fasta.gz
	@#debruijn - all 13 mers
	$(eval TEST_NUM=7)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


ifdef SERVER
test08: test08.fasta.gz
	@#debruijn - all 15 mers
	$(eval TEST_NUM=8)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)


test09: test09.fasta.gz
	@#debruijn - all 17 mers
	$(eval TEST_NUM=9)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)

test10: test10.fasta.gz
	@#debruijn - all 19 mers
	$(eval TEST_NUM=10)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)

test11: test11.fasta.gz
	@#debruijn - all 21 mers
	$(eval TEST_NUM=11)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
endif


test12: test12.fasta.gz
	@#all triplets - one each line
	$(eval TEST_NUM=12)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)


test13: test13.fasta.gz
	@#short sequence
	$(eval TEST_NUM=13)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test14: test14.fasta.gz
	@#short sequence 2
	$(eval TEST_NUM=14)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test15: test15.fasta.gz
	@#1 N
	$(eval TEST_NUM=15)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test16: test16.fasta.gz
	@#2 Ns
	$(eval TEST_NUM=16)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test17: test17.fasta.gz
	@#tomato chromosome 00
	$(eval TEST_NUM=17)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test18: test18.fasta.gz
	@#all tomato chromosomes as one
	$(eval TEST_NUM=18)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
else
	@echo SERVER DISABLED. SKIPPING KMERS 17-21 FOR TEST $(TEST_NUM)
endif


test19: test19.fasta.gz
	@#all tomato chromosomes - one each line
	$(eval TEST_NUM=19)
	$(TIME) ./run_test.py write  "3" $(TEST_NUM) && $(TIME) ./run_test.py read  "3" $(TEST_NUM)
	$(TIME) ./run_test.py write  "5" $(TEST_NUM) && $(TIME) ./run_test.py read  "5" $(TEST_NUM)
	$(TIME) ./run_test.py write  "7" $(TEST_NUM) && $(TIME) ./run_test.py read  "7" $(TEST_NUM)
	$(TIME) ./run_test.py write  "9" $(TEST_NUM) && $(TIME) ./run_test.py read  "9" $(TEST_NUM)
	$(TIME) ./run_test.py write "11" $(TEST_NUM) && $(TIME) ./run_test.py read "11" $(TEST_NUM)
	$(TIME) ./run_test.py write "13" $(TEST_NUM) && $(TIME) ./run_test.py read "13" $(TEST_NUM)
ifdef SERVER
	@echo SERVER ENABLED. CALCULATING KMERS 17-21 FOR TEST $(TEST_NUM)
	$(TIME) ./run_test.py write "15" $(TEST_NUM) && $(TIME) ./run_test.py read "15" $(TEST_NUM)
	$(TIME) ./run_test.py write "17" $(TEST_NUM) && $(TIME) ./run_test.py read "17" $(TEST_NUM)
	$(TIME) ./run_test.py write "19" $(TEST_NUM) && $(TIME) ./run_test.py read "19" $(TEST_NUM)
	$(TIME) ./run_test.py write "21" $(TEST_NUM) && $(TIME) ./run_test.py read "21" $(TEST_NUM)
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
