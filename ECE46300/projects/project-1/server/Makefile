# Makefile
TARGET = httpserver
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

SRCS =	httpserver.astpier.c
OBJS = 	$(SRCS:%.c=%.o)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) -c $*.c

test: $(TARGET)
	./httpserver 2091

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt