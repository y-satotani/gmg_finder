.PHONY: all clean

all: $(patsubst %.svg,%.pdf,$(shell ls | egrep "\.svg$$"))

%.pdf: %.svg
	inkscape -z -f $< -A $@ --export-latex

clean:
	rm *.pdf *.pdf_tex
