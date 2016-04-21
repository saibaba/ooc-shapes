CFLAGS=-Wall -g
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
all: $(OBJS)
	cc -o main $^ $(CFLAGS)

clean:
	rm -f *.o
