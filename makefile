CC		=	gcc
CFLAGS	=	-Wall
SRC		=	./src/
BIN		=	./bin/
INCL	=	./include/


$(BIN)itd: $(SRC)main.o $(SRC)image.o $(SRC)map.o
		$(CC) -o $@ $^

main.o: $(SRC)main.c $(INCL)image.h $(INCL)map.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(SRC)*.o