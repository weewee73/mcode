CC = gcc
CFLAGS = -g

sources := $(wildcard *.c)
objects := $(patsubst %.c, %.o, $(sources))

all: calc

%.d: %.c
	set -e; rm -f $@;\
	$(CC) -MM $(CFLAGS) $< > $@.$$$$;\
	sed 's,\($*\).o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$

sinclude $(sources:.c=.d)

calc: $(objects)
	$(CC) $(CFLAGS) -o calc $(objects)

.PHONY: clean
clean:
	rm calc $(objects)
