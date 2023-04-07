all: cmp copy encode decode
cmp: cmp.c
	gcc cmp.c -o cmp
copy: copy.c
	gcc copy.c -o copy
encode: encode.c
	gcc encode.c -o encode
decode: decode.c
	gcc decode.c -o decode
clean:
	rm -f *.o cmp copy encode decode