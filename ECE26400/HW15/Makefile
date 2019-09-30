# Makefile
TARGET = hw15
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DLINKEDLIST -DTEST_MAIN -DTEST_CREATENODE -DTEST_LINKEDLISTCREATE -DTEST_REMOVED 
SRCS =  hw15.c main.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testall: test1 test2 test3 test4 testmemory

testadd: $(TARGET)
	test1
	test2
	test3
	test4
	testmemory

testmemory:	$(TARGET)
	$(VALGRIND) ./hw15 inputs/test1.txt > outputs/output1.txt

test1: $(TARGET)
	./hw15 inputs/test1.txt > outputs/output1.txt
	diff expected/expected1.txt outputs/output1.txt 
	
test2: $(TARGET)
	./hw15 inputs/test2.txt > outputs/output2.txt
	diff expected/expected2.txt outputs/output2.txt 

test3: $(TARGET)
	./hw15 inputs/test3.txt > outputs/output3.txt
	diff expected/expected3.txt outputs/output3.txt

test4: $(TARGET)
	./hw15 inputs/test4.txt > outputs/output4.txt
	diff expected/expected4.txt outputs/output4.txt 

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
