MCC=mpicc -std=c99 -fdiagnostics-color=always

a.out: 2d_struct_subarray.o
	$(MCC) -o $@ $^

2d_struct_subarray.o: 2d_struct_subarray.c
	$(MCC) -o $@ -c $^ 

clean:
	rm -f *.o a.out
