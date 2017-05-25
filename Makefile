CC=gcc
CFLAGS=-Wall -g

BINS=leakcount sctracer memory_shim.so

all: $(BINS)

leakcount:  leakcount.c
	$(CC) $(CFLAGS) -o leakcount leakcount.c
	
sctracer:	sctracer.c
	$(CC) $(CFLAGS) -o sctracer sctracer.c
   
memory_shim.so:  memory_shim.c
	$(CC) $(CFLAGS) -fPIC -shared -o memory_shim.so memory_shim.c -ldl

clean:
	rm $(BINS)
