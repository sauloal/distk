//http://stackoverflow.com/questions/2394479/fastest-way-to-read-every-30th-byte-of-large-binary-file
//dd if=/dev/urandom of=rand1.data bs=64M count=16

#include <stdio.h>
#include <stdlib.h>

const long long size = 1024LL*1024*MEGS;
const int step = 32;

int main() {
    FILE *in = fopen("rand1.data", "rb");
    int total = 0;
    #if SEEK
        long long i = 0;
        char buf[1];
        while (i < size) {
            int f = fread(buf, 1, 1, in);
            total += (unsigned char) buf[0];
            fseek(in, step - 1, SEEK_CUR);
            i += step;
        }
    #endif
    #ifdef BUFSZ
        long long i = 0;
        char buf[BUFSZ];
        while (i < size) {
            int f = fread(buf, BUFSZ, 1, in);
            i += BUFSZ;
            for (int j = 0; j < BUFSZ; j += step)
                total += (unsigned char) buf[j];
        }
    #endif
    printf("%d\n", total);
}
