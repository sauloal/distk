ifdef simple
    CXXFLAGS := -D__TREE_SIMPLE__=1
else
    CXXFLAGS :=
endif

all: test1 test2 tree_example

%.o: %.cc 
	g++ -g -c -Wall -O2 -std=c++11 $(CXXFLAGS) -I. -o $@ $^

test1: test1.o
	g++ -o test1 test1.o

test2: test2.o 
	g++ -o test2 test2.o

tree_example: tree_example.o
	g++ -o $@ $^

.PHONY: run_example run_tests run

run_tests: test1 test1.req
	./test1 > test1.res
	@diff test1.res test1.req
	@echo "*** All tests OK ***"

run_example: tree_example
	./tree_example

run: run_tests run_example

clean:
	rm -f *.o *~ *.res
