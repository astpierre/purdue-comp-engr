# Makefile
TARGET = client
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

SRCS =	client.c
OBJS = 	$(SRCS:%.c=%.o)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) -c $*.c

run: $(TARGET)
	./client dtunes.ecn.purdue.edu 80 /ece463/lab1/path_short.txt

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt