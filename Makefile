CC=g++
CFLAGS=-c -Wall -Werror -MP -MMD -g
TESTFLAGS=-I src -I thirdparty -c -Wall
EXECUTABLE=bin/Network.out
SOURSES=src/main.cpp src/input.cpp src/network.cpp src/learn.cpp
OBJECTSS=$(SOURSES:.cpp=.out)
OBJECTS=$(patsubst src/%,build/src/%,$(OBJECTSS))
TESTEXECUTABLE=bin/Test.out
PREPROCESS=thirdparty/ctest.h
TESTSOURSESS=$(patsubst thirdparty/%,test/%,$(PREPROCESS))
TESTSOURSES=$(TESTSOURSESS:.h=.cpp)
TESTOBJECTSS=$(TESTSOURSES:.cpp=.out)
TESTOBJECTS=$(patsubst test/%,build/test/%,$(TESTOBJECTSS))
BUILDED=build/src/network.out build/src/learn.out build/src/input.out
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
$(TESTSOURSES): $(PREPROCESS)
	cxxtestgen --error-printer -o $@ $<
$(TESTEXECUTABLE): $(TESTOBJECTS)
	$(CC)  $(TESTOBJECTS) $(BUILDED) -o $@
build/test/%.out: test/%.cpp
	$(CC) $(TESTFLAGS) $< -o $@
