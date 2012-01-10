CXXFLAGS = -O3 -ffast-math -fomit-frame-pointer
TARGETS = miller-rabin.o test-pi

all: $(TARGETS)

check: test-pi
	time nice -9 ./test-pi

test-pi: miller-rabin.o

clean:
	rm -f $(TARGETS)
