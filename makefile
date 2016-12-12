ifdef VERBOSE
	Q =
	E = @true
else
	Q = @
	E = @echo
endif

CXXFILES := $(shell find src -mindepth 1 -maxdepth 4 -name "*.cpp")

OBJFILES := $(CXXFILES:src/%.cpp=%)
DEPFILES := $(CXXFILES:src/%.cpp=%)
OFILES := $(OBJFILES:%=obj/%.o)

BINFILE = app.out

LDFLAGS =


CXXFLAGS =  -Wall -pedantic --std=c++11
ifdef DEBUG
	CXXFLAGS := $(CXXFLAGS) -DMAP -g
endif

DEPDIR = deps
all: $(BINFILE)
ifeq ($(MAKECMDGOALS),)
-include Makefile.dep
endif
ifneq ($(filter-out clean, $(MAKECMDGOALS)),)
-include Makefile.dep
endif

CXX = g++


-include Makefile.local

.PHONY: clean all depend
.SUFFIXES:
obj/%.o: src/%.cpp
	$(E) C++-compiling $<
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -o $@ -c $< $(CXXFLAGS)

Makefile.dep: $(CXXFILES)
	$(E) Depend
	$(Q)for i in $(^); do $(CXX) $(CXXFLAGS) -MM "$${i}" -MT obj/`basename $${i%.*}`.o; done > $@


$(BINFILE): $(OFILES)
	$(E) Linking $@
	$(Q)$(CXX) -o $@ $(OFILES) $(LDFLAGS)
clean:
	$(E) Removing files
	$(Q)rm -f $(BINFILE) obj/* Makefile.dep