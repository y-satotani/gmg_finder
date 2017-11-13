.PHONY: all clean

all: $(patsubst %.R,%.pdf,$(shell ls | egrep "\.R$$"))

%.pdf: %.R
	Rscript $< 1> /dev/null 2> /dev/null

clean:
	rm *.pdf
