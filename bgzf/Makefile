LIBS=bgzip.o
LIBS+=bgzf.o
LIBS+=kfunc.o
LIBS+=knetfile.o
LIBS+=kstring.o
LIBS+=errmod.o
LIBS+=faidx.o
LIBS+=hfile.o
LIBS+=hfile_net.o
LIBS+=hts.o
LIBS+=md5.o
LIBS+=multipart.o
LIBS+=probaln.o
LIBS+=realn.o
LIBS+=regidx.o
LIBS+=sam.o
LIBS+=synced_bcf_reader.o
LIBS+=tbx.o
LIBS+=textutils.o
LIBS+=thread_pool.o
LIBS+=vcf.o
LIBS+=vcf_sweep.o
LIBS+=vcfutils.o
LIBS+=cram/cram_codecs.o
LIBS+=cram/cram_decode.o
LIBS+=cram/cram_encode.o
LIBS+=cram/cram_external.o
LIBS+=cram/cram_index.o
LIBS+=cram/cram_io.o
LIBS+=cram/cram_samtools.o
LIBS+=cram/cram_stats.o
LIBS+=cram/files.o
LIBS+=cram/mFILE.o
LIBS+=cram/open_trace_file.o
LIBS+=cram/pooled_alloc.o
LIBS+=cram/rANS_static.o
LIBS+=cram/sam_header.o
LIBS+=cram/string_alloc.o
LIBS+=cram/vlen.o
LIBS+=cram/zfio.o

all: bgzip test_bgzf

%.o: %.c
	gcc -g -O2 -I.  -c -o $@ $<

version.h:
	@echo '#define HTS_VERSION "1.3.2-220-g84a89da"' > version.h

print:
	@echo $(LIBS)

libhts.a: version.h $(LIBS)
	ar -rc libhts.a $^
	ranlib libhts.a

bgzip: bgzip.o libhts.a
	gcc -pthread   -o $@ $^ -lz

test_bgzf: test_bgzf.o libhts.a
	gcc -pthread   -o $@ $^ -lz

clean:
	rm *.o *.a cram/*.o htslib/*.o bgzip test_bgzf || true

#
#bgzip: pooled_alloc.o bgzip.o bgzf.o
#	gcc -I. -L. -pthread -o bgzip pooled_alloc.o bgzip.o bgzf.o -lz