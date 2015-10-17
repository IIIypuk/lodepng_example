CC=gcc
LDFLAGS= -lglfw -lGL
OUT=run

all: lodepng.o
	$(CC) -O2 -o $(OUT) \
	main.c lodepng.o $(LDFLAGS)

lodepng.o:
	$(CC) -c ./deps/lodepng/lodepng.c

clean:
	rm -f *.o $(OUT)
