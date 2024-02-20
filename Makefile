CXXFLAGS = -fPIC -ldl

libunrandom.so: unrandom.o
	$(CXX) $(CXXFLAGS) $^ -shared -o $@

do-test: test libunrandom.so
	LD_PRELOAD=$$(pwd)/libunrandom.so ./test
.PHONY: do-test

clean:
	rm -vf test test.o *.o *.so
.PHONY: clean

test: test.o

# implicit rules used for .o files.
