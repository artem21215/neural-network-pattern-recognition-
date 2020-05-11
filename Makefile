CC=g++
CFLAGS=-c -Wall -MP -MMD -g
TESTFLAGS=-I thirdparty src -c
EXECUTABLE=bin/Network.out
SOURSES=src/main.cpp src/input.cpp src/network.cpp src/learn.cpp
OBJECTSS=$(SOURSES:.cpp=.out)
OBJECTS=$(patsubst src/%,build/src/%,$(OBJECTSS))
TESTEXECUTABLE=bin/Test.out
TESTSOURSES=test/main.cpp
TESTOBJECTSS=$(TESTSOURSES:.cpp=.out)
TESTOBJECTS=$(patsubst test/%,build/test/%,$(TESTOBJECTSS))

all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
build/src/%.out: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@
.PHONY: clean test
clean:
	rm -rf build/src/*
	rm -rf build/test/*
	rm -rf bin/*.out
test: $(TESTSOURSES) $(TESTEXECUTABLE)
$(TESTEXECUTABLE): $(TESTOBJECTS)
	$(CC) $(TESTOBJECTS) -o $@
build/test/%.out: test/%.cpp
	$(CC) $(TESTFLAGS) $< -o $@
