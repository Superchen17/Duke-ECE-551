CPPFLAGS= -std=c++03

testset: testset.o
	g++ $(CPPFLAGS) -o $@ $<
testset.o: testset.cpp
	g++ $(CPPFLAGS) -c -o $@ $<
testset.o: bstset.h
.PHONY: clean
clean:
	rm -rf *.o *~ testset
