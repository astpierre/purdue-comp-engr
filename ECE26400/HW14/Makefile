# Makefile
TARGET = hw14
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DLINKEDLIST -DTEST_MAIN -DTEST_CREATENODE -DTEST_LINKEDLISTCREATE -DTEST_SPLIT -DTEST_MERGE -DTEST_SORT

SRCS =  hw14.c main.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testall: test1 test2 testmemory

testadd: $(TARGET)
	test1
	test2
	testmemory

testmemory:	$(TARGET)
	$(VALGRIND) ./hw14 inputs/test1.txt > outputs/output1.txt

test1: $(TARGET)
	./hw14 inputs/test1.txt > outputs/output1.txt
	diff expected/expected1.txt outputs/output1.txt 
	
test2: $(TARGET)
	./hw14 inputs/test2.txt > outputs/output2.txt
	diff expected/expected2.txt outputs/output2.txt 

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
