# Makefile
TARGET = hw20
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_MAIN -DTEST_READHEADER -DTEST_DECODE -DTEST_MERGELIST -DDO_NOT_MODIFY

SRCS = main.c decode.c list.c tree.c utility.c
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testall: test1 test2 test3 test4 test5 test6 test7 test8 testmemory

testadd: $(TARGET)
	test0
	test1
	test2
	test3
	test4
	test5
	test6
	test7
	test8
	testmemory

testmemory:	$(TARGET)
	$(VALGRIND) ./hw20 input/input1.txt output/output1.txt
test0: $(TARGET)
		./hw20 input/input1.bin output.txt
test1: $(TARGET)
	./hw20 input/input1.bin output/output1.txt
	diff -i -w expected/expected1.txt output/output1.txt
test2: $(TARGET)
	./hw20 input/input2.bin output/output2.txt
	diff -i -w expected/expected2.txt output/output2.txt
test3: $(TARGET)
	./hw20 input/input3.bin output/output3.txt
	diff -i -w expected/expected3.txt output/output3.txt
test4: $(TARGET)
	./hw20 input/input4.bin output/output4.txt
	diff -i -w expected/expected4.txt output/output4.txt
test5: $(TARGET)
	./hw20 input/input5.bin output/output5.txt
	diff -i -w expected/expected5.txt output/output5.txt
test6: $(TARGET)
	./hw20 input/input6.bin output/output6.txt
	diff -i -w expected/expected6.txt output/output6.txt
test7: $(TARGET)
	./hw20 input/input7.bin output/output7.txt
	diff -i -w expected/expected7.txt output/output7.txt
test8: $(TARGET)
	./hw20 input/input8.bin output/output8.txt
	diff -i -w expected/expected8.txt output/output8.txt

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
