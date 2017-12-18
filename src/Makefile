MAKE := make
.PHONY: all, install, clean, uninstall

all:
	$(MAKE) -C gmgf all
	$(MAKE) -C experiment all
	$(MAKE) -C test all

install:
	mkdir -p bin
	cp experiment/*.out test/*.out bin

clean:
	$(MAKE) -C gmgf clean
	$(MAKE) -C experiment clean
	$(MAKE) -C test clean

uninstall:
	rm -rf bin
