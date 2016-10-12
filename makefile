organizer: main.o functions.o softlink.o
	gcc main.o functions.o softlink.o -o organizer

main.o:
	gcc -c main.c

functions.o:
	gcc -c functions.c

softlink.o:
	gcc -c softlink.c

clean:
	rm -f *.o core