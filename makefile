CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -m64
LDFLAGS=-g -m64
LDLIBS=-lm

SRCS=main.cpp Route.cpp
OBJS=$(subst .cpp,.o,$(SRCS))


.PHONY: clean

all: out

out: $(OBJS)
	$(CXX) $(LDFLAGS) -o out $(OBJS) -L $(LDLIBS)

#On utilise le preporcesseur de g++ pour generer les dependances
#l'option - MM genere une regle compatible avec make
#cette regle decrit les dependances du fichier source
#et ignore les interfaces qui sont dans les entetes du systeme
depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
