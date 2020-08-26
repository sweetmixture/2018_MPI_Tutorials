MCC=mpicc -std=c99 -fdiagnostics-color=always

a.out: src.o
	$(MCC) -o $@ $^ -lm

src.o: src.c
	$(MCC) -o $@ -c $^


clean:
	rm -f *.o a.out
