OBJ	= wcrtime.o wcrstr.o wcrconfig.o wcrnet.o wcrconv.o wcrlog.o
AR	= ar
INCLUDE = ../include
OBJPATH = ../obj
RANLIB	= ranlib
CFLAGS	= -Wall -c -g
CC	= gcc
ARCH	= 
LIBPATH = ../lib
EXEC1	= libwcr.so
EXEC2	= libwcr.a


#$(CC) $(ARCH) -Wall -shared -fPIC $(OBJ) -o$(LIBPATH)/$(EXEC1) 
main:$(OBJ)
	rm -f $(LIBPATH)/$(EXEC1) 
	$(AR) rc $(LIBPATH)/$(EXEC1) $(OBJ)
	$(RANLIB) $(LIBPATH)/$(EXEC1)
	rm -f $(LIBPATH)/$(EXEC2) 
	$(AR) rc $(LIBPATH)/$(EXEC2) $(OBJ)
	$(RANLIB) $(LIBPATH)/$(EXEC2)
wcrtime.o:wcrtime.c $(INCLUDE)/wcrtime.h $(INCLUDE)/wcrpub.h
	$(CC) $(ARCH) $(CFLAGS) wcrtime.c -I $(INCLUDE)
wcrstr.o:wcrstr.c $(INCLUDE)/wcrstr.h $(INCLUDE)/wcrpub.h
	$(CC) $(ARCH) $(CFLAGS) wcrstr.c -I $(INCLUDE)
wcrconfig.o:wcrconfig.c $(INCLUDE)/wcrconfig.h $(INCLUDE)/wcrpub.h
	$(CC) $(ARCH) $(CFLAGS) wcrconfig.c -I $(INCLUDE)
wcrnet.o:wcrnet.c $(INCLUDE)/wcrnet.h $(INCLUDE)/wcrpub.h
	$(CC) $(ARCH) $(CFLAGS) wcrnet.c -I $(INCLUDE)
wcrconv.o:wcrconv.c $(INCLUDE)/wcrconv.h $(INCLUDE)/wcrpub.h
	$(CC) $(ARCH) $(CFLAGS) wcrconv.c -I $(INCLUDE)
wcrlog.o:wcrlog.c $(INCLUDE)/wcrlog.h $(INCLUDE)/wcrpub.h
	$(CC) $(ARCH) $(CFLAGS) wcrlog.c -I $(INCLUDE)


.PHONY:clean
clean:
	rm -f $(LIBPATH)/$(EXEC1) $(LIBPATH)/$(EXEC2) $(OBJ)
