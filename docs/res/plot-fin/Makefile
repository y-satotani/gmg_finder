TARGETS := $(patsubst %.R,%.pdf,$(shell ls | grep R))

.PHONY: all clean

all: $(TARGETS)

%.pdf: %.R
	Rscript $< 1> /dev/null 2> /dev/null

clean:
	rm *.pdf
