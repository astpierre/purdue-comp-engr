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

short: $(TARGET)
	./client dtunes.ecn.purdue.edu 80 /ece463/lab1/path_short.txt > out_short.txt
	diff -i -w out_short.txt tests/short.txt

long: $(TARGET)
	./client dtunes.ecn.purdue.edu 80 /ece463/lab1/path_very_long.txt > out_long.txt
	diff -i -w out_long.txt tests/long.txt


clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt