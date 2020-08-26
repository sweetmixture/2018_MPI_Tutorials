CC = mpicc -std=c99 -fdiagnostics-color=always
LINK = -lgsl -lgslcblas -lm

a.out: test.o
	$(CC) -o $@ $^ $(LINK)

test.o: test.c
	$(CC) -o $@ -c $^

clean:
	rm -f *.o *.out
