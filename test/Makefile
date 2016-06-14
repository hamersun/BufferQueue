CC := g++
AR := ar
CFLAGS = -Wall -g -std=c++11 -fPIC
#LDFLAGS = -shared
INCLUDES := -I./ -I../

LIBS := -L../lib -lBufferQueue -lpthread

# define the C source files
SRCS := \
    test.cpp

OBJDIR = obj
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

MODULEDIR = out
MODULE := $(MODULEDIR)/BufferQueueTest

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: $(MODULE)

$(MODULE): $(OBJS)
	@mkdir -p $(MODULEDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o $(MODULE) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) -r $(OBJDIR)
	$(RM) *.o *~ $(MODULE)
	$(RM) -r $(MODULEDIR)
