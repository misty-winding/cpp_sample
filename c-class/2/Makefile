PROGNAME := test

SRCS := main.cpp \
        graph.cpp

CXX := g++
CPPFLAGS := -I./
DEFS :=
LDFLAGS :=
LIBS :=
CXXFLAGS := -W -Wall -O0 -g

OUTDIR := build

PROG := $(OUTDIR)/$(PROGNAME)
OBJS := $(SRCS:%.cpp=$(OUTDIR)/%.o)
DEPS := $(SRCS:%.cpp=$(OUTDIR)/%.d)


.PHONY: clean


all: $(PROG)

-include $(DEPS)


$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)


$(OUTDIR)/%.o:%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(DEFS) -o $@ -c -MMD -MP -MF $(@:%.o=%.d) $<

clean:
	rm -rf $(OUTDIR)
