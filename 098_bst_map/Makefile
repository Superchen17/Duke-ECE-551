CPPFLAGS= -std=c++03

testmap: testmap.o
	g++ $(CPPFLAGS) -o $@ $<
testmap.o: testmap.cpp
	g++ $(CPPFLAGS) -c -o $@ $<
testmap.o: bstmap.h
.PHONY: clean
clean:
	rm -rf *.o *~ testmap
