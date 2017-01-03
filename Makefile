BASE=kmer_set

__PROG_VERSION__=$(shell git rev-list --all --count && git describe --tags --always --dirty)
__COMPILE_DATE__=$(shell date)

ifneq ($(_DEBUG_),)
__PROG_VERSION__+=debug
endif

ifneq ($(_DO_NOT_USE_ZLIB_),)
__PROG_VERSION__+=no_zlib
endif

ifneq ($(THREADS),)
__PROG_VERSION__+=threads
endif


CPP:=g++

CPP_INCL_F=$(CPP_INCL) -I/usr/include/python2.7 -Igzstream/gzstream
CPP_OPTS_F=$(CPP_OPTS) -fPIC -march=native -std=c++0x -lz
CPP_VARS_F=$(CPP_VARS) -D__PROG_VERSION__="$(__PROG_VERSION__)" -D__COMPILE_DATE__="$(__COMPILE_DATE__)"
LDFLAGS_F=$(LDFLAGS) -lz

ifneq ($(THREADS),)
CPP_OPTS_F+=-fopenmp
LDFLAGS_F+=-fopenmp
endif

ifeq ($(_DEBUG_),)
#no debug
CPP_OPTS_F+=-Ofast
else
#debug
CPP_OPTS_F+=-Og -g -D_DEBUG_
endif

LIBS=$(BASE).o $(BASE)_wrap.o
ifeq ($(_DO_NOT_USE_ZLIB_),)
LIBS+=gzstream.o
endif




all:_$(BASE).so

clean:
	rm -v $(BASE)_wrap.* $(BASE).py $(BASE).pyc _$(BASE).so *.o core || true

print:
	@echo "PROG_VERSION      '$(__PROG_VERSION__)'"
	@echo "COMPILE_DATE      '$(__COMPILE_DATE__)'"
	@echo "MAKE              $(MAKE)"
	@echo "BASE              $(BASE)"
	@echo "LIBS              $(LIBS)"
	@echo "_DEBUG_           $(_DEBUG_)"
	@echo "_DO_NOT_USE_ZLIB_ $(_DO_NOT_USE_ZLIB_)"
	@echo "THREADS           $(THREADS)"
	@echo "CPP_OPTS_F        $(CPP_OPTS_F)"
	@echo "CPP_INCL_F        $(CPP_INCL_F)"
	@echo "CPP_VARS_F        $(CPP_VARS_F)"
	@echo "LDFLAGS_F         $(LDFLAGS_F)"

.PHONY: test
test:
	$(MAKE) -C test

.PHONY: debug
debug:
	./debug.sh

$(BASE)_wrap.cpp: $(BASE).i $(BASE).cpp $(BASE).hpp
	swig -c++ -python -outdir $(PWD) -I$(PWD) -o $@ $(BASE).i

%.o: %.cpp
	$(CPP) $(CPP_OPTS_F) $(CPP_INCL_F) $(CPP_VARS_F) -c $< -o $@

gzstream.o: gzstream/gzstream/gzstream.C
	$(CPP) $(CPP_OPTS_F) $(CPP_INCL_F) $(CPP_VARS_F) -c $< -o $@

_$(BASE).so: $(LIBS)
	$(CPP) -shared $? -o $@ $(LDFLAGS_F)
