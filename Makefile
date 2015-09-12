CC=gcc
OUT=run

all: lodepng.o
	$(CC) -O2 -o $(OUT) \
	lodepng.o \
	main.c -lglfw -lGL -lGLU

lodepng.o:
	$(CC) -c ./deps/lodepng/lodepng.c

clean:
	rm -f *.o $(OUT)
