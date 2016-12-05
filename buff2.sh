set -xeu

gcc -std=c99 buff2.c -obuff2 -O3 -DBUFSZ=32*1024 -DMEGS=20   && time ./buff2
gcc -std=c99 buff2.c -obuff2 -O3 -DBUFSZ=32      -DMEGS=20   && time ./buff2
gcc -std=c99 buff2.c -obuff2 -O3 -DBUFSZ=32*1024 -DMEGS=20   && time ./buff2
gcc -std=c99 buff2.c -obuff2 -O3 -DBUFSZ=32      -DMEGS=20   && time ./buff2
gcc -std=c99 buff2.c -obuff2 -O3 -DSEEK          -DMEGS=20   && time ./buff2

gcc -std=c99 buff2.c -obuff2 -O3 -DBUFSZ=32*1024 -DMEGS=1000 && time ./buff2
gcc -std=c99 buff2.c -obuff2 -O3 -DBUFSZ=32      -DMEGS=1000 && time ./buff2
gcc -std=c99 buff2.c -obuff2 -O3 -DBUFSZ=32*1024 -DMEGS=1000 && time ./buff2
gcc -std=c99 buff2.c -obuff2 -O3 -DBUFSZ=32      -DMEGS=1000 && time ./buff2
gcc -std=c99 buff2.c -obuff2 -O3 -DBUFSZ=32*1024 -DMEGS=1000 && time ./buff2
