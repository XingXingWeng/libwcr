OBJ	= main.o
ARGS	= -m32 -Wall -c -g
CC	= gcc
INCLUDE = -I ../include
LIBPATH = -L ../lib -ltbu
EXT	= c
EXE	= main


main:$(OBJ)
	$(CC) -m32 -Wall $(OBJ) $(LIBPATH) -o $(EXE)
main.o:main.$(EXT)
	$(CC) $(ARGS) main.$(EXT) $(INCLUDE) $(LIBPATH)

.PHONY:clean
clean:
	rm -f $(EXE) $(OBJ)
