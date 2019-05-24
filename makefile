CC		=	gcc
CFLAGS	=	-Wall -O2 -g
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm
SRC		=	./src/
OBJ		=	./obj/
BIN		=	./bin/
INCL	=	./include/


$(BIN)itd: $(OBJ)main.o $(OBJ)image.o $(OBJ)map.o $(OBJ)node.o $(OBJ)monster.o $(OBJ)tower.o $(OBJ)game.o $(OBJ)sprite.o $(OBJ)display.o $(OBJ)installation.o $(OBJ)common.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ)main.o: $(SRC)main.c $(INCL)image.h $(INCL)map.h $(INCL)node.h $(INCL)monster.h $(INCL)tower.h $(INCL)game.h $(INCL)sprite.h $(INCL)display.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(OBJ)image.o: $(SRC)image.c $(INCL)image.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(OBJ)map.o: $(SRC)map.c $(INCL)map.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(OBJ)node.o: $(SRC)node.c $(INCL)node.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(OBJ)monster.o: $(SRC)monster.c $(INCL)monster.h $(INCL)tower.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(OBJ)tower.o: $(SRC)tower.c $(INCL)tower.h $(INCL)geometry.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(OBJ)installation.o: $(SRC)installation.c $(INCL)installation.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(OBJ)game.o: $(SRC)game.c $(INCL)game.h $(INCL)monster.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(OBJ)sprite.o: $(SRC)sprite.c $(INCL)sprite.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(OBJ)display.o: $(SRC)display.c $(INCL)display.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(OBJ)common.o: $(SRC)common.c $(INCL)common.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

clean:
	rm -rf $(OBJ)*.o