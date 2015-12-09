#
# Author: Simon Howden
# Date: December 2015
# Terminal Tracker
#
#

# use c compiler
CC = gcc

# ncurses library
LDFLAGS=-lncurses

# c files
SRCS = ./main/main.c ./main/second.c
OBJS = $(SRCS:.c=.o)

# executable
MAIN = test


#GENERIC
all:	$(MAIN)
	@echo This compile has completed

#$(MAIN): $(OBJS) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
$(MAIN): $(OBJS) 
	$(CC) $(LDFLAGS) $(SRCS) -o $(MAIN)
clean: 
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $^

#DO NOT DELETE THIS LINE
