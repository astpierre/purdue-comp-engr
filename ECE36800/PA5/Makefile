# Makefile
TARGET = pa5
WARNING =  -Wshadow --pedantic -Wall
ERROR = -Wvla
GCC = gcc -std=c99 -O3 $(WARNING) $(ERROR)

SRCS = pa5.c sorting.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) -c $*.c

run: $(TARGET)
	./pa5 -q input/1000.b output/1000.txt

runq: $(TARGET)
	./pa5 -q input/1k.b output/1k.b

runm: $(TARGET)
	./pa5 -m input/t1.b output/t1.b

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *out
	rm -f output/*.b
