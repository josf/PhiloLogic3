# $Id: Makefile.in,v 2.11 2004/05/28 19:22:08 o Exp $
CC= gcc
PH_CFLAGS = -g -I..
# CFLAGS= "-O3 $(PH_CFLAGS)"
CFLAGS= -O3 $(PH_CFLAGS)
all: libindex.a 

libindex.a: hitdef.o hitcmp_cooc.o hitcmp_phrase.o hitcmp_proxy.o hitout.o hitman.o hitcrp.o hitunpack.o method.o plugin.o
	ar ru $@ hitdef.o hitcmp_cooc.o hitcmp_phrase.o hitcmp_proxy.o hitout.o hitman.o hitcrp.o hitunpack.o method.o plugin.o
	ranlib $@

hitdef.o: 	hitdef.c hitcon.h hitcmp.h hitdef.h hitman.h hitout.h
#	$(CC)    -c -o hitdef.o hitdef.c

hitcmp_cooc.o: 	hitcmp_cooc.c hitcon.h hitcmp.h hitdef.h hitman.h hitout.h
#	$(CC)    -c -o hitcmp_cooc.o hitcmp_cooc.c

hitcmp_phrase.o: 	hitcmp_phrase.c hitcon.h hitcmp.h hitdef.h hitman.h hitout.h

hitcmp_proxy.o: 	hitcmp_proxy.c hitcon.h hitcmp.h hitdef.h hitman.h hitout.h

hitout.o: 	hitout.c hitcon.h hitout.h hitdef.h hitman.h hitcmp.h
#	$(CC)    -c -o hitout.o hitout.c

hitman.o: 	hitman.c hitcon.h hitman.h hitdef.h hitcmp.h
#	$(CC)    -c -o hitman.o hitman.c

hitcrp.o: 	hitcrp.c hitcon.h hitdef.h hitcmp.h
#	$(CC)    -c -o hitcrp.o hitcrp.c

clean:
	rm -f *.o *~ *.a core







