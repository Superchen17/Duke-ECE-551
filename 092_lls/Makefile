count: count.o
	g++ -o $@ $<
count.o: count.cpp
	g++ -c -o $@ $<
ll: ll.o
	g++ -o $@ $<
ll.o: test-lls.cpp
	g++ -c -o $@ $<
.PHONY: clean
clean:
	rm -rf *.o *~ ll count
count.o: ll.h
ll.o: ll.h
