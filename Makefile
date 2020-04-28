CC=g++
CFLAGS=-c -Wall -MP -MMD
EXECUTABLE=bin/Network.out
SOURSES=src/main.cpp src/input.cpp src/network.cpp src/learn.cpp
OBJECTSS=$(SOURSES:.cpp=.out)
OBJECTS=$(patsubst src/%,build/%,$(OBJECTSS))

all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
build/%.out: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@
.PHONY: clean
clean:
	rm -rf build/*.out build/*.d
