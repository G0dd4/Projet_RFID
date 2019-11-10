CC=gcc
EXEC = interface

CFLAGS   = -Wunused -Wall -fPIC -I. -c -O3 -D REENTRANT
CFLAGS  += -DGTK_DISABLE_DEPRECATED=1 -DGDK_DISABLE_DEPRECATED
CFLAGS  += -DGDK_PIXBUF_DISABLE_DEPRECATED -DG_DISABLE_DEPRECATED
CFLAGS  += -DGTK_MULTIHEAD_SAFE=1 -DGTK_MULTIDEVICE_SAFE=1
CFLAGS  += `pkg-config gtk+-3.0 --cflags`
CFLAGS  += `pkg-config --cflags --libs gtk+-2.0`
CFLAGS  += -g 
CFLAGS	+= `pkg-config mysqlclient --cflags`


LDFLAGS  = `pkg-config gtk+-3.0 --libs`
LDFLAGS += `pkg-config mysqlclient --libs`



all: $(EXEC)


$(EXEC): ajout.o main.o supprimer.o modifier.o bdd.o
	$(CC) ajout.o main.o supprimer.o modifier.o bdd.o -o $(EXEC) $(LDFLAGS)
	
	
modifier.o: SRC/modifier.c SRC/modifier.h SRC/window.h
	$(CC) -o modifier.o -c SRC/modifier.c $(CFLAGS)
	
supprimer.o: SRC/supprimer.c SRC/supprimer.h SRC/window.h
	$(CC) -o supprimer.o -c SRC/supprimer.c $(CFLAGS)
		
ajout.o: SRC/ajout.c SRC/ajout.h SRC/window.h
	$(CC) -o ajout.o -c SRC/ajout.c $(CFLAGS)
	
main.o: main.c SRC/window.h SRC/ajout.h SRC/modifier.h SRC/supprimer.h SRC/bdd.h
	$(CC) -o main.o -c main.c $(CFLAGS)

bdd.o: SRC/bdd.c SRC/bdd.h
	$(CC) -o bdd.o -c SRC/bdd.c $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf $(EXEC)
	rm -rf SRC/*.o
	echo [File removed]
	


