MCC = mpicc -std=c99 -fdiagnostics-color=always
LPATH = -L/home/uccawkj/gsl/lib
HPATH = -I/home/uccawkj/gsl/include
LINK = -lgsl -lgslcblas -lm

1_std.out: 1_std.o
	$(MCC) -o $@ $^ $(LINK)

1_std.o: 1_std.c
	$(MCC) -o $@ -c $^


clean: 
	rm -f *.out *.o
