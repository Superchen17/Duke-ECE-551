code: code.o
	g++ -o $@ $<
code.o: code.cpp code.h
	g++ -c -o $@ code.cpp
.PHONY: clean
clean:
	rm -rf *.o *~ code
