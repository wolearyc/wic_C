# wic MakeFile. 
# Targets: all (default, release), release, debug, and clean.

# SETTINGS
CC         = gcc
LD         = ld
CFLAGS     =
DEBUGFLAGS = -g

# You probably won't need to change anything beyond this point.
SOURCES       = $(wildcard src/*.c)
OBJECTS       = $(addprefix obj/release/,$(notdir $(SOURCES:.c=.o)))
DOBJECTS      = $(addprefix obj/debug/,$(notdir $(SOURCES:.c=.o)))
INCLUDEPATHS  = -I include/ -I deps/include/
COPTIONS      =

all: release
	
release: $(OBJECTS)
	ar -r bin/release/libwic.a obj/release/*.o deps/lib/*.o

obj/release/%.o: src/%.c
	mkdir -p bin/release/
	mkdir -p obj/release/
	$(CC) $(CFLAGS) $(COPTIONS) -c $< -o $@ $(INCLUDEPATHS)

debug: $(DOBJECTS)
	ar -r bin/debug/libwic.a obj/debug/*.o deps/lib/*.o

obj/debug/%.o: src/%.c
	mkdir -p bin/debug/
	mkdir -p obj/debug/
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(COPTIONS) -c $< -o $@ $(INCLUDEPATHS)

clean:
	rm -f -r obj/release/*
	rm -f -r obj/debug/*
	rm -f -r bin/release/*
	rm -f -r bin/debug/*
	