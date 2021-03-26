CC = g++ -c
CFLAGS = -Wall -std=c++14
OBJECTS = PTree.o ptree
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SFML = /usr/local/SFML-2.5.1/

app: $(OBJECTS)
	$(CC) $(CFLAGS)c $(OBJECTS)
PTree.o:
	$(CC) $(CFLAGS) -c -I$(SFML)include PTree.cpp -o PTree.o
	g++ PTree.o -o ptree -L$(SFML)/lib $(LIBS)
clean:
	rm $(OBJECTS)
