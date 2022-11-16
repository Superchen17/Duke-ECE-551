CPPFLAGS= -std=c++11
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa-step1: cyoa-step1.o page.o
	g++ $(CPPFLAGS) -o $@ cyoa-step1.o page.o
cyoa-step2: cyoa-step2.o page.o story.o
	g++ $(CPPFLAGS) -o $@ cyoa-step2.o page.o story.o
cyoa-step3: cyoa-step3.o page.o story.o
	g++ $(CPPFLAGS) -o $@ cyoa-step3.o page.o story.o
cyoa-step4: cyoa-step4.o page.o story.o
	g++ $(CPPFLAGS) -o $@ cyoa-step4.o page.o story.o
%.o: %.c
	g++ $(CPPFLAGS) -c -o $@ $<
.PHONY: clean
clean:
	rm -rf *.o *~ cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4

cyoa-step1.o: page.h story.h
cyoa-step2.o: page.h story.h
cyoa-step3.o: page.h story.h
cyoa-step4.o: page.h story.h
page.o: page.h
story.o: story.h
