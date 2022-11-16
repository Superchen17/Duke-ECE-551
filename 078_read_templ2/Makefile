code: code.o
	g++ -o $@ $<
code.o: code.cpp
	g++ -c -o $@ $<
.PHONY: clean
clean:
	rm -rf *.o *~ code
