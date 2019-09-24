# Makefile
TARGET = multi_service_server
WARNING = -Wshadow --pedantic
ERROR = -Wall -Wvla #-Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

SRCS =	multi_service_server.astpier.c
OBJS = 	$(SRCS:%.c=%.o)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) -c $*.c

test: $(TARGET)
	./$(TARGET) 2091 3091

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
