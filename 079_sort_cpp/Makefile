sortLines: sortLines.o
	g++ -o $@ $<
sortLines.o: sortLines.cpp
	g++ -c -o $@ $<
.PHONY: clean
clean:
	rm -rf *.o *~ sortLines
