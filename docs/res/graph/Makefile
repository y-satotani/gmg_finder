.PHONY: all clean

SVG := $(patsubst %.elist,%.svg,$(shell ls | egrep "\.elist$$"))
PDF := $(patsubst %.elist,%.pdf,$(shell ls | egrep "\.elist$$"))
PNG := $(patsubst %.elist,%.png,$(shell ls | egrep "\.elist$$"))

all: $(SVG) $(PDF) $(PNG)

n12-d3-example.svg: n12-d3-example.elist
	./elist2svg.py -i $< -o $@
n14-d3-nogmg.svg: n14-d3-nogmg.elist
	./elist2svg.py -i $< -o $@
n24-d3-cycle.svg: n24-d3-cycle.elist
	./elist2svg.py -i $< -o $@

%.svg: %.elist
	./elist2svg.py -i $< -o $@ --solid-dash

%.pdf: %.svg
	inkscape -z -f $< -A $@

%.png: %.svg
	inkscape -z -f $< -e $@ -d 300 -b "#ffffff00"

clean:
	rm -f *.svg *.pdf *.png
