CCFLAGS = -std=gnu99 -finline-functions
CC = gcc
OBJS = bfc.c

.PHONY: run
run: bfc.out
	./bfc.out

bfc.out: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@



.PHONY: clean
clean:
	-rm *.o
	-rm *.out