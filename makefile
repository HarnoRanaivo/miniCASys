CC = gcc
CFLAGS = -Wall -g -pedantic -std=gnu99
IFLAGS = -Iinclude

OPATH = obj/
BPATH = bin/

vpath %.c src/
vpath %.h include/
vpath %.o obj/

main : main.o matrix.o operations.o resol.o decompo.o | bin
	$(CC) $(CFLAGS) -o $(BPATH)main $(OPATH)main.o $(OPATH)matrix.o $(OPATH)operations.o $(OPATH)resol.o $(OPATH)decompo.o

memoire.o : memoire.c memoire.h matrix.h
resol.o : resol.c resol.h matrix.h operations.h
decompo.o : decompo.c decompo.h matrix.h operations.h
matrix.o : matrix.c matrix.h
operations.o : operations.c operations.h matrix.h
main.o : main.c matrix.h operations.h resol.h decompo.h

%.o : %.c | obj
	$(CC) $(CFLAGS) -o $(OPATH)$@ -c $< $(IFLAGS)

obj :
	mkdir obj

bin :
	mkdir bin

clean :
	rm obj/* bin/*

cleanall : clean
	rm -r lib/* doc/*

archive :
	tar -f L2S4-ALA-TP2_razanajato-harenome.tar.gz -cvz src/*.c include/*.h makefile
