TARGETS := $(patsubst %.R,%.tex,$(shell ls | grep R))

.PHONY: all clean

all: $(TARGETS)

%.tex: %.R
	Rscript $< 1> /dev/null 2> /dev/null

clean:
	rm *.tex
