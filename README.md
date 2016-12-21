(cd test && ./gen_test.sh)

make DEBUG=1 clean al

make test

make THREADS=1 clean all

