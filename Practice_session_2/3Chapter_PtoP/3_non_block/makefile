MCC = mpicc -std=c99 -fdiagnostics-color=always
LINK = -lgsl -lgslcblas -lm

a.out: 1_Irecv_first.o
	$(MCC) -o $@	$^ $(LINK)

1_Irecv_first.o: 1_Irecv_first.c
	$(MCC) -o $@ -c $^



clean:
	rm -f *.o *.out
