CPPFLAGS= -std=c++03
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRCS))

test-bsearch: $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS)
%.o: %.cpp
	g++ $(CPPFLAGS) -c -o $@ $<
.PHONY: clean
clean:
	rm -rf *.o *~ test-bsearch

test-bsearch.o: function.h
search.o: function.h
