# Makefile
TARGET = pa2
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

SRCS = pa2.c sequence.c shell_array.c shell_list.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) -c $*.c

testall: testarray testlist

testarray: test15a test1000a memchecka

testlist: test15l test1000l memcheckl

memchecka:	$(TARGET)
	$(VALGRIND) ./pa2 -a pa2_examples/15.b mout.b

memcheckl:	$(TARGET)
	$(VALGRIND) ./pa2 -l pa2_examples/15.b mout.b

run: $(TARGET)
	./pa2 -l pa2_examples/15.b 15lout.b
	diff pa2_examples/15sl.b 15lout.b

test15a: $(TARGET)
	./pa2 -a pa2_examples/15.b 15aout.b
	diff pa2_examples/15sa.b 15aout.b

test15l: $(TARGET)
	./pa2 -l pa2_examples/15.b 15lout.b
	diff pa2_examples/15sl.b 15lout.b

test1000a: $(TARGET)
	./pa2 -a pa2_examples/1000.b 1000aout.b
	diff pa2_examples/1000sa.b 1000aout.b

test1000l: $(TARGET)
	./pa2 -l pa2_examples/1000.b 1000lout.b
	diff pa2_examples/1000sl.b 1000lout.b

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
	rm -f *out.b
