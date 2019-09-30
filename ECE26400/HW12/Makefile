# Makefile
TARGET = hw12
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DLINKEDLIST -DTEST_MAIN -DTEST_CREATENODE -DTEST_LINKEDLISTCREATE -DTEST_JOSEPHUS

SRCS =  hw12.c main.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testall: test1 test2 test3 test4 test5 test6 testmemory

testadd: $(TARGET)
	test1
	test2
	test3
	test4
	test5
	test6
	testmemory

testmemory:	$(TARGET)
	$(VALGRIND) ./hw12 10 3 1 > testing/output1.txt

test1: $(TARGET)
	./hw12 10 3 1 > testing/output1.txt
	diff testing/expected1.txt testing/output1.txt 
	
test2: $(TARGET)
	./hw12 10 4 2 > testing/output2.txt
	diff testing/expected2.txt testing/output2.txt 

test3: $(TARGET)
	./hw12 8 5 3 > testing/output3.txt
	diff testing/expected3.txt testing/output3.txt 

test4: $(TARGET)
	./hw12 8 9 1 > testing/output4.txt
	diff testing/expected4.txt testing/output4.txt 

test5: $(TARGET)
	./hw12 41 3 1 > testing/output5.txt
	diff testing/expected5.txt testing/output5.txt 

test6: $(TARGET)
	./hw12 100 3 20 > testing/output6.txt
	diff testing/expected6.txt testing/output6.txt 

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
