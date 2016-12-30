BASE=kmer_set

__PROG_VERSION__=$(shell git rev-list --all --count && git describe --tags --always --dirty)
__COMPILE_DATE__=$(shell date)


CPP_INCL=-I/usr/include/python2.7 -Igzstream/gzstream
CPP_OPTS=-fPIC -march=native -std=c++0x -lz
CPP_VARS_F=$(CPP_VARS)
CPP_VARS_F+=-D__PROG_VERSION__="$(__PROG_VERSION__)" -D__COMPILE_DATE__="$(__COMPILE_DATE__)"
LDFLAGS=-lz

ifneq ($(THREADS),)
CPP_OPTS+=-fopenmp
LDFLAGS+=-fopenmp
endif

ifeq ($(DEBUG),)
#no debug
CPP_OPTS+=-Ofast
else
#debug
CPP_OPTS+=-Og -g -D_DEBUG_
endif

CPP:=g++

all:_$(BASE).so

clean:
	rm -v $(BASE)_wrap.* $(BASE).o $(BASE).py $(BASE).pyc _$(BASE).so test/*.kmer test/*.log test/*.matrix  test/*.index core || true

print:
	@echo PROG_VERSION $(__PROG_VERSION__)
	@echo COMPILE_DATE $(__COMPILE_DATE__)

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

gzstream.o: gzstream/gzstream/gzstream.C
	$(CPP) $(CPP_OPTS) $(CPP_INCL) $(CPP_VARS_F) -c $< -o $@

_$(BASE).so: $(BASE).o $(BASE)_wrap.o gzstream.o
	$(CPP) -shared $? -o $@ $(LDFLAGS) 

