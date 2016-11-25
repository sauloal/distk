CPP_INCL=-I/usr/include/python2.7
CPP_OPTS=-fPIC -O3
CPP_VARS=


KMER_GEN_VERSION=$(shell git rev-parse HEAD)
COMP_DATE=$(shell date)

BASE=kmer_gen
CPP=g++

all: _$(BASE).so

clean:
	rm -v $(BASE)_wrap.* $(BASE).o $(BASE).py $(BASE).pyc _$(BASE).so || true

$(BASE)_wrap.cpp: $(BASE).i $(BASE).cpp
	swig -c++ -python -outdir $(PWD) -I$(PWD) -o $@ $(BASE).i

%.o: %.cpp
	$(CPP) -D__KMER_GEN_VERSION__="$(KMER_GEN_VERSION)" -D__DATE__="$(COMP_DATE)" $(CPP_OPTS) $(CPP_INCL) $(CPP_VARS) -c $< -o $@

_$(BASE).so: $(BASE).o $(BASE)_wrap.o
	$(CPP) -shared $? -o $@

