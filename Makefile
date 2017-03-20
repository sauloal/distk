BASE=kmer_set

__PROG_VERSION__=$(shell git rev-list --all --count && git describe --tags --always --dirty)
__COMPILE_DATE__=$(shell date)

CPP:=g++
OBJ_FOLDER:=obj
SRC_FOLDER:=src


CPP_VARS_F=$(CPP_VARS) -D__COMPILE_DATE__="$(__COMPILE_DATE__)"



ifneq ($(_DEBUG_),)
__PROG_VERSION__+=debug
CPP_VARS_F=-D_DEBUG_=1
endif

ifneq ($(_PRINT_LINE_LENGTHS_),)
__PROG_VERSION__+=print_line_lengths
CPP_VARS_F=-D_PRINT_LINE_LENGTHS_=1
endif

ifneq ($(_NO_DIFF_ENCODING_),)
__PROG_VERSION__+=no_diff_encoding
CPP_VARS_F=-D_NO_DIFF_ENCODING_=1
endif

ifneq ($(_ALTERNATIVE_ALLOC_),)
__PROG_VERSION__+=alternative_alloc
CPP_VARS_F=-D_ALTERNATIVE_ALLOC_=1
endif

ifneq ($(THREADS),)
__PROG_VERSION__+=threads
endif



CPP_VARS_F+=-D__PROG_VERSION__="$(__PROG_VERSION__)"
CPP_INCL_F=$(CPP_INCL) -I/usr/include/python2.7 -Ibgzf -Igzstream/gzstream -Icontainers
CPP_OPTS_F=$(CPP_OPTS) -fPIC -march=native -mtune=native -std=c++1y -lz -pipe
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

LIBS=$(OBJ_FOLDER)/$(BASE).o
LIBS+=$(OBJ_FOLDER)/$(BASE)_wrap.o
LIBS+=$(OBJ_FOLDER)/kmer_set_compression.o
LIBS+=$(OBJ_FOLDER)/fileholder.o
LIBS+=$(OBJ_FOLDER)/merger.o
LIBS+=$(OBJ_FOLDER)/tools.o
LIBS+=$(OBJ_FOLDER)/gzstream.o




all:_$(BASE).so

clean:
	rm -v $(SRC_FOLDER)/$(BASE)_wrap.* $(BASE).py $(BASE).pyc _$(BASE).so $(OBJ_FOLDER)/*.o core || true

print:
	@echo "PROG_VERSION        '$(__PROG_VERSION__)'"
	@echo "COMPILE_DATE        '$(__COMPILE_DATE__)'"
	@echo "MAKE                $(MAKE)"
	@echo "BASE                $(BASE)"
	@echo "LIBS                $(LIBS)"
	@echo "_DEBUG_             $(_DEBUG_)"
	@echo "_ALTERNATIVE_ALLOC_ $(_ALTERNATIVE_ALLOC_)"
	@echo "THREADS             $(THREADS)"
	@echo "CPP_OPTS_F          $(CPP_OPTS_F)"
	@echo "CPP_INCL_F          $(CPP_INCL_F)"
	@echo "CPP_VARS_F          $(CPP_VARS_F)"
	@echo "LDFLAGS_F           $(LDFLAGS_F)"

.PHONY: test
test:
	$(MAKE) -C test

.PHONY: debug
debug:
	./debug.sh

$(SRC_FOLDER)/$(BASE)_wrap.cpp: $(SRC_FOLDER)/$(BASE).i $(SRC_FOLDER)/$(BASE).cpp $(SRC_FOLDER)/$(BASE).hpp
	swig -c++ -python -outdir $(PWD) -I$(PWD) -I$(SRC_FOLDER) -o $@ $(SRC_FOLDER)/$(BASE).i

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	$(CPP) $(CPP_OPTS_F) $(CPP_INCL_F) $(CPP_VARS_F) -c $< -o $@

$(OBJ_FOLDER)/gzstream.o: gzstream/gzstream/gzstream.C
	$(CPP) $(CPP_OPTS_F) $(CPP_INCL_F) $(CPP_VARS_F) -c $< -o $@

_$(BASE).so: $(LIBS)
	$(CPP) -shared $? -o $@ $(LDFLAGS_F)
