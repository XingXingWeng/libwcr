OBJ	= main.o
ARGS	= -m64 -Wall -c -g
CC	= gcc
INCLUDE = -I ../include
LIBPATH = -L ../lib -lwcr
EXT	= c
EXE	= main


main:$(OBJ)
	$(CC) -m64 -Wall $(OBJ) $(LIBPATH) -o $(EXE)
main.o:main.$(EXT)
	$(CC) $(ARGS) main.$(EXT) $(INCLUDE) $(LIBPATH)

.PHONY:clean
clean:
	rm -f $(EXE) $(OBJ)
