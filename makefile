CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=-ldl

#used to remove the need for export LD_LIBRARY_PATH=.
RPATH=-Wl,-rpath=./

all: cmp copy libcodecA.so libcodecB.so encode decode stshell

cmp: cmp.c
	$(CC) cmp.c -o cmp
copy: copy.c
	$(CC) copy.c -o copy

libcodecA.so: codecA.c
	$(CC) -c -fPIC $< $(CFLAGS) -o codecA.o
	$(CC) -shared -o $@ codecA.o

libcodecB.so: codecB.c
	$(CC) -c -fPIC $< $(CFLAGS) -o codecB.o
	$(CC) -shared -o $@ codecB.o

encode: encode.c
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS) $(RPATH)

decode: decode.c
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS) $(RPATH)

stshell: stshell.c
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

clean:
	rm -f *.o cmp copy libcodecA.so libcodecB.so codecA.o codecB.o encode decode stshell