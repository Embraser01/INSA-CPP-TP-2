CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=-lm

SRCS=main.cpp Route.cpp
OBJS=$(subst .cpp,.o,$(SRCS))


.PHONY: clean

all: out

out: $(OBJS)
	$(CXX) $(LDFLAGS) -o out $(OBJS) -L $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend