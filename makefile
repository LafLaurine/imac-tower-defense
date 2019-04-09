CC		=	gcc
CFLAGS	=	-Wall -O2 -g
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm
SRC		=	./src/
BIN		=	./bin/
INCL	=	./include/


$(BIN)itd: $(SRC)main.o $(SRC)image.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: $(SRC)main.c $(INCL)image.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

clean:
	rm -rf $(SRC)*.o