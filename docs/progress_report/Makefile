
.PHONY: all clean
SRC := $(patsubst %.R,%.pdf,$(shell ls | egrep "\.Rmd$$"))
TGT := $(SRC:%.Rmd=%.pdf) $(SRC:%.Rmd=%.pdf)

all: $(TGT)

%.md: %.Rmd
	Rscript -e "library(rmarkdown); rmarkdown::render('$<', 'md_document')"

%.pdf: %.Rmd
	Rscript -e "library(rmarkdown); rmarkdown::render('$<', 'pdf_document')"

clean:
	rm *.pdf *.md

