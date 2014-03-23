PROGNAME := test

SRCS := main.cpp \
        FreeListAllocator.cpp \
        ProxyAllocator.cpp \
        ArenaAllocator.cpp

CXX := g++
CPPFLAGS := -I./ -I../../poco/Foundation/include
DEFS :=
LDFLAGS := -static -L../../poco/lib/Linux/i686
LIBS := PocoFoundation
CXXFLAGS := -W -Wall -O0 -g

OUTDIR := build

PROG := $(OUTDIR)/$(PROGNAME)
OBJS := $(SRCS:%.cpp=$(OUTDIR)/%.o)
DEPS := $(SRCS:%.cpp=$(OUTDIR)/%.d)


.PHONY: clean


all: $(PROG)

-include $(DEPS)


$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ -l $(LIBS)


$(OUTDIR)/%.o:%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(DEFS) -o $@ -c -MMD -MP -MF $(@:%.o=%.d) $<

clean:
	rm -rf $(OUTDIR)
