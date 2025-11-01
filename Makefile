quad: main.o io.o maths.o
	$(CC) $(CFLAGS) main.o io.o maths.o -o quad

main.o: main.c io.h maths.h
	$(CC) $(CFLAGS) -c main.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

maths.o: maths.c maths.h
	$(CC) $(CFLAGS) -c maths.c

clean:
	rm -f *.o quad
