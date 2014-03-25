# Wick MakeFile. 
# Targets: all (default, release), release, debug, and clean.

# SETTINGS
CC         = g++
LD         = ld
CFLAGS     =
DEBUGFLAGS = -g

# You probably won't need to change anything beyond this point.
SOURCES       = $(wildcard src/*.cpp)
OBJECTS       = $(addprefix obj/release/,$(notdir $(SOURCES:.cpp=.o)))
DOBJECTS      = $(addprefix obj/debug/,$(notdir $(SOURCES:.cpp=.o)))
INCLUDEPATHS  = -I include/ -I deps/include/
COPTIONS      = -std=c++11

all: release
	
release: $(OBJECTS)
	ar -r bin/release/libwick.a obj/release/*.o deps/lib/*.o

obj/release/%.o: src/%.cpp
	mkdir -p bin/release/
	mkdir -p obj/release/
	$(CC) $(CFLAGS) $(COPTIONS) -c $< -o $@ $(INCLUDEPATHS)

debug: $(DOBJECTS)
	ar -r bin/debug/libwick.a obj/debug/*.o deps/lib/*.o

obj/debug/%.o: src/%.cpp
	mkdir -p bin/debug/
	mkdir -p obj/debug/
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(COPTIONS) -c $< -o $@ $(INCLUDEPATHS)

clean:
	rm -f -r obj/release/*
	rm -f -r obj/debug/*
	rm -f -r bin/release/*
	rm -f -r bin/debug/*
	