MCC = mpicc -std=c99 -fdiagnostics-color=always

a.out: src.o
	$(MCC) -o $@	$^

src.o: src.c
	$(MCC) -o $@ -c $^

clean:
	rm -f *.out *.o
