MCC=mpicc -std=c99 -fdiagnostics-color=always

a.out: 2d_struct.o
	$(MCC) -o $@ $^

2d_struct.o: 2d_struct.c
	$(MCC) -o $@ -c $^ 

clean:
	rm -f *.o a.out
