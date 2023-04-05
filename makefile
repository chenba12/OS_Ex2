all: cmp copy
cmp: cmp.c
	gcc cmp.c -o cmp
copy: copy.c
	gcc copy.c -o copy
clean:
	rm -f *.o cmp copy