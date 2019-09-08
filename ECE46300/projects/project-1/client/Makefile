# Makefile
TARGET = httpclient
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

SRCS =	httpclient.astpier.c
OBJS = 	$(SRCS:%.c=%.o)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) -c $*.c

short: $(TARGET)
	./httpclient dtunes.ecn.purdue.edu 80 /ece463/lab1/path_short.txt

long: $(TARGET)
	./httpclient dtunes.ecn.purdue.edu 80 /ece463/lab1/path_very_long.txt


clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt