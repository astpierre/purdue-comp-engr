WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFLAGS = -DTEST_MERGE -DTEST_MERGESORT -DTEST_MERGESSORT

SRCS = main.c
OBJS = $(SRCS:%.c=%.o)

hw07: $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o hw07

testmemory: $(TARGET)
	$(VAL) ./hw07 Input/Test1 output1.txt
	$(VAL) ./hw07 Input/Test2 output2.txt
	$(VAL) ./hw07 Input/Test3 output3.txt

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testall: test1 test2 test3 testmemory

testadd: hw07
	test1
	test2
	test3
	testmemory

test1: hw07
	./hw07 Input/Test1 output1.txt
	diff -i -w output1.txt Expected/Expected1

test2: hw07
	./hw07 Input/Test2 output2.txt
	diff -i -w output2.txt Expected/Expected2

test3: hw07
	./hw07 Input/Test3 output3.txt
	diff -i -w output3.txt Expected/Expected3

clean: #remove all machine generated files
	rm -f hw07 *.o output?
	rm -f *.txt
