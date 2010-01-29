CC=g++
CFLAGS=-c -Wall
GLUTFLAGS=-framework GLUT -framework OpenGL
COCOAFLAGS=-framework Cocoa
SOURCES=main.cpp GameFramework.cpp Shape.cpp Random.h Vector2D.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=circles

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(GLUTFLAGS) $(COCOAFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
