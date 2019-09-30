# Makefile
TARGET = hw16
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_MAIN -DTEST_FREETREE -DTEST_SEARCH -DTEST_SUBTREE -DTEST_CONTAINED -DPRINT_FUN
SRCS =  binarytree.c hw16.c main.c
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
	$(VALGRIND) ./hw16 inputs/tree1/test1.txt inputs/tree2/test1.txt > outputs/output1.txt

test1: $(TARGET)
	./hw16 inputs/tree1/test1.txt inputs/tree2/test1.txt > outputs/output1.txt
	diff -i -w expected/expected1.txt outputs/output1.txt 
	
test2: $(TARGET)
	./hw16 inputs/tree1/test2.txt inputs/tree2/test2.txt > outputs/output2.txt
	diff -i -w expected/expected2.txt outputs/output2.txt 

test3: $(TARGET)
	./hw16 inputs/tree1/test3.txt inputs/tree2/test3.txt > outputs/output3.txt
	diff -i -w expected/expected3.txt outputs/output3.txt 

test4: $(TARGET)
	./hw16 inputs/tree1/test4.txt inputs/tree2/test4.txt > outputs/output4.txt
	diff -i -w expected/expected4.txt outputs/output4.txt 

test5: $(TARGET)
	./hw16 inputs/tree1/test5.txt inputs/tree2/test5.txt > outputs/output5.txt
	diff -i -w expected/expected5.txt outputs/output5.txt 

test6: $(TARGET)
	./hw16 inputs/tree1/test6.txt inputs/tree2/test6.txt > outputs/output6.txt
	diff -i -w expected/expected6.txt outputs/output6.txt

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
