MAKE := make
.PHONY: all, clean

all:
	$(MAKE) -C figure all
	$(MAKE) -C table all

clean:
	rm -f $$(find . | egrep "pdf(_tex)?")
