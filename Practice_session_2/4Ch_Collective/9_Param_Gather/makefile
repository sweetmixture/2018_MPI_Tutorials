MCC = mpicc
BLAS = -lgsl -lgslcblas -lm

a.out: src.o
	$(MCC) -o $@	$^	$(BLAS)

src.o: src.c
	$(MCC) -o $@ -c $^

clean:
	rm -f *.out *.o
	rm -f *~
