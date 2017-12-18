CC := g++
IDIR := /usr/include/igraph ../
LDIR := /usr/lib/x86_64-linux-gnu/ ../gmgf
LIBS := -lm -ligraph -lgmgf
CFLAGS := -g -std=c++11 -Ofast -Wall -Wl,-R../gmgf \
          $(addprefix -I,$(IDIR)) $(addprefix -L,$(LDIR))

EXE := $(patsubst %.cpp,%.out,$(shell ls | egrep ".\cpp$$"))

.PHONY: all clean

all: $(EXE)

%.out: %.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f *.out
