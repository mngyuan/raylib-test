CC=gcc
LDFLAGS=`pkg-config --libs --cflags raylib`

#src = $(wildcard *.c)
#obj = $(src:.c=.o)

#testproj: $(obj)
	#$(CC) -o $@ $^ $(LDFLAGS)

#.PHONY: clean
#clean:
	#rm -f $(obj) testproj
texture: texture.c
	$(CC) -o texture texture.c $(LDFLAGS)
