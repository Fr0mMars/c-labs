# Makefile for regoins_code project

binary: shownameregion.o libregion.a netclient.o 
	gcc -o shownameregion shownameregion.o -L. -lregion
	gcc -o netclient netclient.o
	rm *.o

netclient.o: netclient.c
	gcc -c netclient.c

shownameregion.o: shownameregion.c
	gcc -c shownameregion.c

libregion.a: readfile.o findreg.o
	ar cr -o libregion.a readfile.o findreg.o

findreg.o: findreg.c
	gcc -c findreg.c

readfile.o: readfile.c
	gcc -c readfile.c

clean:
	rm -f *.o *.a shownameregion netclient
