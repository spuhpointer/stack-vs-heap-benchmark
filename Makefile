alloct: stack.c
	gcc stack.c -O1 -oalloct -l nstd -l pthread -l rt -l dl

.PHONY: clean
clean:
	rm alloct
