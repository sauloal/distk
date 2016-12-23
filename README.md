(cd test && ./gen_test.sh)

make DEBUG=1 clean al

make test

make THREADS=1 clean all

TODO:
 - http://stxxl.sourceforge.net/ - https://github.com/stxxl/stxxl
 - https://www.codeproject.com/Articles/27799/Stree-A-fast-std-map-and-std-set-replacement
 - http://forums.codeguru.com/showthread.php?406108-A-faster-std-set
 - http://www.drdobbs.com/space-efficient-sets-and-maps/184401668
 - https://ideone.com/F0V42m