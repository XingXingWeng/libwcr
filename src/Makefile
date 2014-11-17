OBJ	= tbutime.o tbustr.o tbuconfig.o tbunet.o tbuconv.o tbulog.o
AR	= ar
INCLUDE = ../include
OBJPATH = ../obj
RANLIB	= ranlib
CFLAGS	= -Wall -c -g
CC	= gcc
ARCH	= -m32
LIBPATH = ../lib
EXEC1	= libtbu.so
EXEC2	= libtbu.a


#$(CC) $(ARCH) -Wall -shared -fPIC $(OBJ) -o$(LIBPATH)/$(EXEC1) 
main:$(OBJ)
	rm -f $(LIBPATH)/$(EXEC2) 
	$(AR) rc $(LIBPATH)/$(EXEC2) $(OBJ)
	$(RANLIB) $(LIBPATH)/$(EXEC2)
tbutime.o:tbutime.c $(INCLUDE)/tbutime.h $(INCLUDE)/tbupub.h
	$(CC) $(ARCH) $(CFLAGS) tbutime.c -I $(INCLUDE)
tbustr.o:tbustr.c $(INCLUDE)/tbustr.h $(INCLUDE)/tbupub.h
	$(CC) $(ARCH) $(CFLAGS) tbustr.c -I $(INCLUDE)
tbuconfig.o:tbuconfig.c $(INCLUDE)/tbuconfig.h $(INCLUDE)/tbupub.h
	$(CC) $(ARCH) $(CFLAGS) tbuconfig.c -I $(INCLUDE)
tbunet.o:tbunet.c $(INCLUDE)/tbunet.h $(INCLUDE)/tbupub.h
	$(CC) $(ARCH) $(CFLAGS) tbunet.c -I $(INCLUDE)
tbuconv.o:tbuconv.c $(INCLUDE)/tbuconv.h $(INCLUDE)/tbupub.h
	$(CC) $(ARCH) $(CFLAGS) tbuconv.c -I $(INCLUDE)
tbulog.o:tbulog.c $(INCLUDE)/tbulog.h $(INCLUDE)/tbupub.h
	$(CC) $(ARCH) $(CFLAGS) tbulog.c -I $(INCLUDE)


.PHONY:clean
clean:
	rm -f $(LIBPATH)/$(EXEC1) $(LIBPATH)/$(EXEC2) $(OBJ)
