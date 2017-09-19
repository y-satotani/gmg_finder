CC := g++
IDIR := /usr/include/igraph $(shell pwd)
LDIR := /usr/lib/x86_64-linux-gnu/
LIBS := igraph m
CFLAGS := -Ofast -Wall\
	$(addprefix -I,$(IDIR))\
	$(addprefix -L,$(LDIR))\
	$(addprefix -l,$(LIBS))

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

.PHONY: objects executables all clean
.PRECIOUS: $(OBJ)

all: executables

executables: $(OBJ) $(EXEDIR) $(EXE)
objects: $(OBJ)

$(EXEDIR):
	mkdir -p $(EXEDIR)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

%.out: %.cpp
	$(CC) $(CFLAGS) -o $(addprefix $(join $(EXEDIR),/),$(notdir $@)) $< $(OBJ)

clean:
	find . -regextype posix-egrep -regex ".*\.(o|out)$$" | xargs rm -f
	rm -rf bin
