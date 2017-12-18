CC := g++
IDIR := /usr/include/igraph
LDIR := /usr/lib/x86_64-linux-gnu/
LIBS := -lm -ligraph
CFLAGS := -fpic -g -std=c++11 -Ofast -Wall \
          $(addprefix -I,$(IDIR)) $(addprefix -L,$(LDIR))

OBJ := $(patsubst %.cpp,%.o,$(shell ls | egrep ".\cpp$$"))

.PHONY: all clean

all: libgmgf.so

libgmgf.so: $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

clean:
	rm -f *.o *.so
