CXXFLAGS = -O3 -ffast-math -fomit-frame-pointer
TARGETS = miller-rabin

run: $(TARGETS)
	time nice -9 ./miller-rabin

clean:
	rm -f $(TARGETS)
