CC		=	gcc
CFLAGS	=	-Wall -O2 -g
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm
SRC		=	./src/
BIN		=	./bin/
INCL	=	./include/


$(BIN)itd: $(SRC)main.o $(SRC)image.o $(SRC)map.o $(SRC)node.o $(SRC)monster.o $(SRC)tower.o $(SRC)game.o $(SRC)sprite.o $(SRC)display.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: $(SRC)main.c $(INCL)image.h $(INCL)map.h $(INCL)node.h $(INCL)monster.h $(INCL)tower.h $(INCL)game.h $(INCL)sprite.h $(INCL)display.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

clean:
	rm -rf $(SRC)*.o