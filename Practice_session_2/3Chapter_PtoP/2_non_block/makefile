MCC = mpicc -std=c99 -fdiagnostics-color=always
LINK = -lgsl -lgslcblas -lm

a.out: 1_test.o
	$(MCC) -o $@	$^ $(LINK)

1_test.o: 1_test.c
	$(MCC) -o $@ -c $^


clean:
	rm -f *.out *.o
