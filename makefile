CC = gcc
CFLAGS = -Wall -g -pedantic -std=gnu99
IFLAGS = -Iinclude

OPATH = obj/
BPATH = bin/

vpath %.c src/
vpath %.h include/
vpath %.o obj/

minicas : main.o matrix.o operations.o resol.o memoire.o prompt.o parseur.o decompo.o | bin
	$(CC) $(CFLAGS) -o $(BPATH)minicas $(OPATH)main.o $(OPATH)matrix.o $(OPATH)operations.o $(OPATH)resol.o $(OPATH)memoire.o $(OPATH)prompt.o $(OPATH)parseur.o $(OPATH)decompo.o

parseur.o : parseur.c parseur.h base.h memoire.h
prompt.o : prompt.c prompt.h base.h matrix.h memoire.h parseur.h operations.h resol.h
memoire.o : memoire.c memoire.h base.h matrix.h
resol.o : resol.c resol.h matrix.h operations.h
decompo.o : decompo.c decompo.h matrix.h operations.h resol.h
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
	rm -f obj/* bin/*

cleanall : clean
	rm -rf lib/* doc/*

archive :
	tar -f L2S4-ALA-TP2_razanajato-harenome.tar.gz -cvz src/*.c include/*.h makefile
