CC := g++
IDIR := /usr/include/igraph $(shell pwd)
LDIR := /usr/lib/x86_64-linux-gnu/
LIBS := -lm -ligraph
CFLAGS := -std=c++11 -Ofast -Wall $(addprefix -I,$(IDIR)) $(addprefix -L,$(LDIR))\

LPAR := (
OBJ := $(patsubst %.cpp,%.o,$(shell\
	find . -name "*.cpp" |\
	xargs -I{} sh -c "echo -n '{} ' ; grep 'main$(LPAR)' {} | wc -l" |\
	awk '{ if($$NF == 0) print $$1 }')\
)
EXEDIR := bin
EXE := $(patsubst %.cpp,%.out,$(shell\
	find . -name "*.cpp" |\
	xargs -I{} sh -c "echo -n '{} ' ; grep 'main$(LPAR)' {} | wc -l" |\
	awk '{ if($$NF > 0) print $$1 }')\
)

.PHONY: objects executables all install clean

all: executables

executables: $(OBJ) $(EXE)
objects: $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

%.out: %.cpp
	$(CC) $(CFLAGS) -o $@ $< $(OBJ) $(LIBS)

install:
	mkdir -p $(EXEDIR)
	cp $(EXE) $(EXEDIR)

clean:
	find . -regextype posix-egrep -regex ".*\.(o|out)$$" | xargs rm -f
	rm -rf bin
