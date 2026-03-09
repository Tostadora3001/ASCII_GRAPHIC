CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lm  # Add the math library here

#Libreary compilation
Integrity.o: Integrity.c Integrity.h struct_graphic.h
	$(CC) $(CFLAGS) -c Integrity.c -o Integrity.o

vector3D.o: vector3D.c vector3D.h struct_vector3D.h Integrity.o
	$(CC) $(CFLAGS) -c vector3D.c -o vector3D.o

Graphic.o: Graphic.c Graphic.h struct_graphic.h Integrity.o
	$(CC) $(CFLAGS) -c Graphic.c -o Graphic.o

clean:
	rm -f *.o test