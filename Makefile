BASE=kmer_set

KMER_GEN_VERSION=$(shell git rev-parse HEAD)
COMP_DATE=$(shell date)

CPP_INCL=-I/usr/include/python2.7 -Itree-3.1/src/
CPP_OPTS=-fPIC -std=c++11
CPP_VARS=-D__KMER_GEN_VERSION__="$(KMER_GEN_VERSION)" -D__DATE__="$(COMP_DATE)"

ifeq ($(DEBUG),)
#no debug
CPP_OPTS+=-Ofast
else
#debug
CPP_OPTS+=-O0 -g -DDEBUG
endif

CPP=g++

all: _$(BASE).so

clean:
	rm -v $(BASE)_wrap.* $(BASE).o $(BASE).py $(BASE).pyc _$(BASE).so || true

.PHONY: test
test:
	./test.sh

$(BASE)_wrap.cpp: $(BASE).i $(BASE).cpp $(BASE).hpp
	swig -c++ -python -outdir $(PWD) -I$(PWD) -o $@ $(BASE).i

%.o: %.cpp
	$(CPP) $(CPP_OPTS) $(CPP_INCL) $(CPP_VARS) -c $< -o $@

_$(BASE).so: $(BASE).o $(BASE)_wrap.o
	$(CPP) -shared $? -o $@

