MCC = mpicc -std=c99 -fdiagnostics-color=always
LBALS = -lgsl -lgslcblas -lm

a.out: src.o
	$(MCC) -o $@	$^ $(LBLAS)

src.o: src.c
	$(MCC) -o $@ -c $^

clean:
	rm -f *.out *.o
