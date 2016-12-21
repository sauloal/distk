BASE=kmer_set

__PROG_VERSION__=$(shell git describe --tags --always --dirty)
__COMPILE_DATE__=$(shell date)


CPP_INCL=-I/usr/include/python2.7 -Itree-3.1/src/
CPP_OPTS=-fPIC -march=native -std=c++0x
CPP_VARS_F=$(CPP_VARS)
CPP_VARS_F+=-D__PROG_VERSION__="$(__PROG_VERSION__)" -D__COMPILE_DATE__="$(__COMPILE_DATE__)"
LNK_OPTS=

ifneq ($(THREADS),)
CPP_OPTS+=-fopenmp
LNK_OPTS+=-fopenmp
endif

ifeq ($(DEBUG),)
#no debug
CPP_OPTS+=-Ofast
else
#debug
CPP_OPTS+=-Og -g -D_DEBUG_
endif

CPP=g++

all: _$(BASE).so

clean:
	rm -v $(BASE)_wrap.* $(BASE).o $(BASE).py $(BASE).pyc _$(BASE).so test/*.kmer test/*.log test/*.matrix  test/*.index core || true

.PHONY: test
test:
	./test.sh

.PHONY: debug
debug:
	./debug.sh

$(BASE)_wrap.cpp: $(BASE).i $(BASE).cpp $(BASE).hpp
	swig -c++ -python -outdir $(PWD) -I$(PWD) -o $@ $(BASE).i

%.o: %.cpp
	$(CPP) $(CPP_OPTS) $(CPP_INCL) $(CPP_VARS_F) -c $< -o $@

_$(BASE).so: $(BASE).o $(BASE)_wrap.o
	$(CPP) -shared $(LNK_OPTS) $? -o $@

