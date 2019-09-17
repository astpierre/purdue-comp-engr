# Makefile
TARGET = httpserver
WARNING = -Wshadow --pedantic
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

SRCS =	httpserver_fork.astpier.c
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
