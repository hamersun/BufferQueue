CC := g++
AR := ar
CFLAGS := -Wall -g -std=c++11 -fPIC
#LDFLAGS = -shared
INCLUDES := -I./

#LIBS :=

# define the C source files
SRCS := \
    MediaBuffer.cpp \
    VideoBuffer.cpp \
    BufferItem.cpp \
    BufferQueue.cpp

OBJDIR = obj
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

MODULEDIR = lib
MODULE := $(MODULEDIR)/libBufferQueue.a

TEST := test
#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean $(TEST)

all: $(MODULE) $(TEST)

$(MODULE): $(OBJS)
	@mkdir -p $(MODULEDIR)
	$(AR) rcs $@ $^

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: %.cpp
	@echo $<
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

$(TEST):
	$(MAKE) -C $(TEST)

clean:
	$(RM) -r $(OBJDIR)
	$(RM) *.o *~ $(MODULE)
	$(RM) -r $(MODULEDIR)
	$(MAKE) -C $(TEST) clean
