CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lm  # Add the math library here

# The final link step MUST include $(LIBS) at the end
test: test.o Graphic.o vector3D.o
	$(CC) $(CFLAGS) test.o Graphic.o vector3D.o -o test $(LIBS)

# Reglas para cada módulo
test.o: test.c Graphic.h
	$(CC) $(CFLAGS) -c test.c -o test.o

Graphic.o: Graphic.c Graphic.h vector3D.h
	$(CC) $(CFLAGS) -c Graphic.c -o Graphic.o

vector3D.o: vector3D.c vector3D.h
	$(CC) $(CFLAGS) -c vector3D.c -o vector3D.o

clean:
	rm -f *.o test