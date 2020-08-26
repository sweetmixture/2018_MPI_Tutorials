MCC = mpicc -std=c99 -fdiagnostics-color=always
LBLAS = -lgsl -lgslcblas -lm

a.out: src.o
	$(MCC) -o $@	$^ $(LBLAS)

src.o: src.c
	$(MCC) -o $@ -c $^

clean:
	rm -f *.o *.out
